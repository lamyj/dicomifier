import json
import logging
import math
import re
import os

import dateutil
import odil

from .. import bruker

vr_converters = {
    "DA": lambda x: dateutil.parser.parse(x.replace(",", ".")).strftime("%Y%m%d"),
    "DS": lambda x: float(x),
    "FD": lambda x: float(x),
    "FL": lambda x: float(x),
    "IS": lambda x: int(x),
    "PN": lambda x: {"Alphabetic": x},
    "TM": lambda x: dateutil.parser.parse(x.replace(",", ".")).strftime("%H%M%S"),
}

def convert_reconstruction(
        source, series, reconstruction, iod_converter, transfer_syntax,
        destination, directory=None):
    
    if directory is None:
        logging.info("Loading Bruker directory {}".format(source))
        directory = dicomifier.bruker.Directory()
        directory.load(source)
    
    logging.info("Converting {}:{}".format(series, reconstruction))
    
    bruker_binary = directory.get_dataset(
        "{}{:04d}".format(series, int(reconstruction)))
    bruker_json = json.loads(bruker.as_json(bruker_binary))
    logging.info("Found {}:{} - {} ({})".format(
        series, reconstruction, 
        bruker_json.get("VisuAcquisitionProtocol", ["(none)"])[0],
        bruker_json.get("RECO_mode", ["none"])[0]
    ))

    try:
        dicom_jsons = iod_converter(bruker_json, transfer_syntax)
    except Exception as e:
        logging.error(
            "Could not convert {}:{} - {}".format(
                series, reconstruction, e))
        logging.debug("Stack trace", exc_info=True)

    logging.info(
        "Writing {} dataset{}".format(
            len(dicom_jsons), "s" if len(dicom_jsons)>1 else ""))
    files = []
    for index, dicom_json in enumerate(dicom_jsons):
        dicom_binary = odil.from_json(json.dumps(dicom_json))
        
        image_file_width = 1+int(math.log10(len(dicom_jsons)))
        
        study_instance_uid = dicom_binary.as_string(odil.registry.StudyInstanceUID)[0]
        
        study_description = (
            dicom_binary.as_string(odil.registry.StudyDescription)[0]
            if dicom_binary.has(odil.registry.StudyDescription) 
                and not dicom_binary.empty(odil.registry.StudyDescription)
            else "")
        study_description = re.sub(
            r"[^A-Z0-9_]", "_", study_description.upper())
        
        series_description = (
            dicom_binary.as_string(odil.registry.SeriesDescription)[0]
            if dicom_binary.has(odil.registry.SeriesDescription) 
                and not dicom_binary.empty(odil.registry.SeriesDescription)
            else "")
        series_description = re.sub(
            r"[^A-Z0-9_]", "_", series_description.upper())
            
        destination_file = os.path.join(
            destination, 
            "{}{}".format(
                series, 
                "_{}".format(study_description) if study_description else "")[:8],
            "{}{}".format(
                reconstruction, 
                "_{}".format(series_description) if series_description else "")[:8],
            ("{{:0{}d}}".format(image_file_width)).format(index)
        )
        if not os.path.isdir(os.path.dirname(destination_file)):
            os.makedirs(os.path.dirname(destination_file))
        odil.write(
            dicom_binary, destination_file, 
            transfer_syntax=transfer_syntax)
        files.append(destination_file)
    
    return files

def convert_element(
        bruker_data_set, dicom_data_set, 
        bruker_name, dicom_name, type_, getter, setter,
        frame_index, generator, vr_finder):
    value = None
    if getter is not None:
        if isinstance(getter, basestring):
            value = getter
        else:
            value = getter(bruker_data_set, generator, frame_index)
    else:
        value = bruker_data_set.get(bruker_name)

    if bruker_name in generator.dependent_fields:
        group_index = [
            index for index, x in enumerate(generator.frame_groups) 
            if bruker_name in x[2]][0]
        value = [ value[frame_index[group_index]] ]

    tag = getattr(odil.registry, dicom_name)
    vr = str(vr_finder(tag))

    if value is None:
        if type_ == 1:
            raise Exception("{} must be present".format(dicom_name))
        elif type_ == 2:
            dicom_data_set[str(tag)] = {"vr": vr}
        elif type_ == 3:
            # May be absent
            pass
    else:
        dicom_data_set[str(tag)] = {"vr": vr}
        if isinstance(setter, dict):
            value = [setter[x] for x in value]
        elif setter is not None:
            value = setter(value)
        
        vr_converter = vr_converters.get(vr)
        if vr_converter is not None:
            value = [vr_converter(x) for x in value]
        
        if vr in ["OB", "OD", "OF", "OL", "OW"]:
            dicom_data_set[str(tag)]["InlineBinary"] = value[0]
        else:
            dicom_data_set[str(tag)]["Value"] = value
    
    return value
