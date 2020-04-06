#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

from .flat_dicom_writer import FlatDICOMWriter
from .nested_dicom_writer import NestedDICOMWriter

import os
import odil

def create_dicomdir(
        paths, directory, patient_key, study_key, series_key, image_key):
    """ Create a DICOMDIR from all files found in paths.
        
        :param paths: list of DICOM files and directories storing DICOM files
        :param directory: destination directory of the DICOMDIR
        :param patient_key: patient-level keys to add to the DICOMDIR
        :param study_key: study-level keys to add to the DICOMDIR
        :param series_key: series-level keys to add to the DICOMDIR
        :param image_key: image-level keys to add to the DICOMDIR
    """
    
    files = []
    for path in paths:
        if os.path.isfile(path):
            files.append(os.path.abspath(path))
        elif os.path.isdir(path):
            for dirpath, _, filenames in os.walk(path):
                dirpath = os.path.abspath(dirpath)
                files.extend(os.path.join(dirpath, x) for x in filenames)

    directory = os.path.abspath(directory)
    if not all(x.startswith(directory) for x in files):
        raise Exception("All files must be under {}".format(directory))

    files = [x[len(directory)+1:] for x in files]

    keys = {}
    for level in ["patient", "study", "series", "image"]:
        for entry in locals()["{}_key".format(level)]:
            if ":" in entry:
                tag, type_ = entry.split(":")
            else:
                tag, type_ = entry, "3"
            tag = getattr(odil.registry, tag)
            type_ = int(type_)
            keys.setdefault(level.upper(), []).append((tag, type_))
    
    creator = odil.BasicDirectoryCreator(directory, files, keys)
    creator()
