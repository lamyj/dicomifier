#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

import json
import os
import re
import unicodedata

import nibabel
import numpy
import odil

from .. import logger, MetaData

def get_files(paths):
    """ Return the DICOM files found in the paths. Each path can be a single 
        file, a directory (scanned recursively), or a DICOMDIR file.
    """
    
    dicom_files = set()
    for entry in paths:
        entry = os.path.abspath(str(entry))

        if os.path.isdir(entry):
            for dirpath, dirnames, filenames in os.walk(entry):
                for filename in filenames:
                    if filename.upper() == "DICOMDIR":
                        dicom_files.update(
                            get_dicomdir_files(os.path.join(dirpath, filename)))
                    else:
                        dicom_files.add(os.path.join(dirpath, filename))
        elif os.path.basename(entry).upper() == "DICOMDIR":
            dicom_files.update(get_dicomdir_files(entry))
        else:
            dicom_files.add(entry)
    
    # Make sure we do not have the same file saved under multiple names
    sop_instance_uids = {}
    for dicom_file in dicom_files:
        try:
            # Read only the header
            header, _ = odil.Reader.read_file(
                dicom_file, halt_condition=lambda x: x.group > 0x0004)
        except odil.Exception as e:
            logger.info("Could not read {}: {}".format(dicom_file, e))
            continue
        sop_instance_uids.setdefault(
                header[odil.registry.MediaStorageSOPInstanceUID][0], 
                []
            ).append(dicom_file)
    if any(len(x) > 1 for x in sop_instance_uids.values()):
        logger.warning(
            "Multiple files with the same SOP instance UID")
    return [x[0] for x in sop_instance_uids.values()]

def get_dicomdir_files(path):
    """ Return the list of files indexed in a DICOMDIR file.
    """
    
    dicom_files = []
    dicomdir = odil.Reader.read_file(path)[1]
    for record in dicomdir[odil.registry.DirectoryRecordSequence]:
        if record[odil.registry.DirectoryRecordType][0] == b"IMAGE":
            dicom_files.append(
                os.path.join(
                    os.path.dirname(path),
                    *[x.decode() for x in record[odil.registry.ReferencedFileID]]))

    return dicom_files

def write_nifti(nifti_data, destination, zip, series_directory=None):
    """ Write the NIfTI image and meta-data in the given destination.
    
        :param nifti_data: Pair of NIfTI image and meta-data
        :param destination: Destination directory
        :param zip: whether to zip the NIfTI files
        :param series_directory: if provided, override the automated 
            series-based output directory name
    """
    
    nifti_files = []
    # Write one nii+json per stack
    for index, (image, meta_data) in enumerate(nifti_data):
        destination_directory = os.path.join(
            str(destination), 
            get_series_directory(meta_data, series_directory))
        
        if not os.path.isdir(destination_directory):
            os.makedirs(destination_directory)

        destination_root = os.path.join(destination_directory, str(1 + index))

        suffix = ".nii"
        if zip:
            suffix += ".gz"
        nifti_file = destination_root + suffix
        nibabel.save(image, nifti_file)
        nifti_files.append(nifti_file)
        
        json.dump(
            meta_data, open(destination_root + ".json", "w"),
            cls=MetaData.JSONEncoder)
    
    return nifti_files

def get_series_directory(meta_data, layout=None):
    """ Return the directory associated with the patient, study and series of
        the NIfTI meta-data.
        
        :param layout: template for the directory name. Values between braces
            are replaced by the value of the corresponding meta-data item. A set
            of pipe-separated items can be specified in the braces, in which
            case the first item present in the meta-data will be used. If no
            corresponding item is found in the meta-data, the empty string will
            be used.
    """
    
    if layout:
        layout = re.split(r"\{([^}]+)\}", layout)
        for index in range(1, len(layout), 2):
            selector = layout[index]
            value = ""
            for item in selector.split("|"):
                if item in meta_data:
                    if item == "SeriesNumber":
                        value = str(get_series_number(meta_data))
                    else:
                        value = meta_data[item][0]
                    break
            
            if isinstance(value, dict) and "Alphabetic" in value:
                value = value["Alphabetic"]
            layout[index] = str(value)
        
        path = "".join(layout)
    else:
        def get_first_item(item):
            while isinstance(item, list):
                item = item[0]
            return item
        
        # Patient directory: <PatientName> or <PatientID> or <StudyInstanceUID>.
        patient_directory = None
        if "PatientName" in meta_data and meta_data["PatientName"]:
            patient_directory = get_first_item(
                meta_data["PatientName"])["Alphabetic"]
        elif "PatientID" in meta_data and meta_data["PatientID"]:
            patient_directory = meta_data["PatientID"][0]
        elif "StudyInstanceUID" in meta_data and meta_data["StudyInstanceUID"]:
            patient_directory = meta_data["StudyInstanceUID"][0]
        else:
            raise Exception("Cannot determine patient directory")

        # Study directory: <StudyID>_<StudyDescription>, both parts are
        # optional. If both tags are missing or empty, raise an exception
        study_directory = []
        if "StudyID" in meta_data and meta_data["StudyID"]:
            study_directory.append(
                numpy.ravel([x for x in meta_data["StudyID"] if x])[0])
        if "StudyDescription" in meta_data and meta_data["StudyDescription"]:
            study_directory.append(
                numpy.ravel([x for x in meta_data["StudyDescription"] if x])[0])

        if not study_directory:
            if "StudyInstanceUID" in meta_data and meta_data["StudyInstanceUID"]:
                study_directory = [meta_data["StudyInstanceUID"][0]]
            else:
                raise Exception("Cannot determine study directory")

        study_directory = "_".join(study_directory).replace(os.path.sep, "_")

        # Study directory: <SeriesNumber>_<SeriesDescription>, both parts are
        # optional. If both tags are missing or empty, raise an exception
        series_directory = []
        if "SeriesNumber" in meta_data and meta_data["SeriesNumber"]:
            series_directory.append(str(get_series_number(meta_data)))
        if "SeriesDescription" in meta_data and meta_data["SeriesDescription"]:
            series_directory.append(
                numpy.ravel(
                    [x for x in meta_data["SeriesDescription"] if x])[0])
        elif "ProtocolName" in meta_data and meta_data["ProtocolName"]:
            series_directory.append(
                numpy.ravel([x for x in meta_data["ProtocolName"] if x])[0])

        if not series_directory:
            if "SeriesInstanceUID" in meta_data and meta_data["SeriesInstanceUID"]:
                series_directory = [meta_data["SeriesInstanceUID"][0]]
            else:
                raise Exception("Cannot determine series directory")

        series_directory = "_".join(series_directory).replace(os.path.sep, "_")
        
        path = os.path.join(patient_directory, study_directory, series_directory)
    
    path = "".join(
        c for c in unicodedata.normalize("NFD", path)
        if unicodedata.category(c) != "Mn")
    
    return path

def get_series_number(meta_data):
    """ Return a human readble series number for Bruker data, or the raw series
        number for non-Bruker data.
    """
    
    software = (meta_data.get("SoftwareVersions") or [""])[0]
    series_number = numpy.ravel(
            [x for x in meta_data["SeriesNumber"] if x is not None]
        )[0]
    if software == "ParaVision" and series_number > 2**16:
        # Bruker ID based on experiment number and reconstruction number
        # is not readable: separate the two values
        series_number = "_".join([str(x) for x in divmod(series_number, 2**16)])
    elif software.startswith("ParaVision") and series_number > 10000:
        # Same processing for Bruker-generated DICOM
        series_number = "_".join([str(x) for x in divmod(series_number, 10000)])
    return series_number
