#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

import os
import re
import odil

from ... import logger

class NestedDICOMWriter:
    """ Write DICOM files in a patient/study/series/reconstruction hierarchy.
    """
    
    def __init__(self, root, iso_9660, transfer_syntax):
        self.root = str(root)
        self.iso_9660 = iso_9660
        self.transfer_syntax = transfer_syntax
        self.files = []
        self._counts = {}

    def __call__(self, data_set):
        directory = os.path.join(self.root, self.get_series_directory(data_set))
        if not os.path.isdir(directory):
            os.makedirs(directory)

        self._counts.setdefault(directory, 0)
        if self.iso_9660:
            filename = "IM{:06d}".format(1+self._counts[directory])
        else:
            filename = data_set[odil.registry.SOPInstanceUID][0].decode()

        destination = os.path.join(directory, filename)
        if data_set.get_transfer_syntax():
            logger.info("Overriding requested transfer syntax")
            transfer_syntax = data_set.get_transfer_syntax()
        else:
            transfer_syntax = self.transfer_syntax
        odil.Writer.write_file(
            data_set, destination, odil.DataSet(), transfer_syntax)
        self.files.append(destination)
        self._counts[directory] += 1

    def get_series_directory(self, data_set):
        """ Return the directory associated with the patient, study and series
            of the DICOM data set.
        """

        specific_character_set = (
            data_set.as_string(odil.registry.SpecificCharacterSet)
            if odil.registry.SpecificCharacterSet in data_set
            else odil.Value.Strings())
        def decode(value):
            return odil.as_unicode(value, specific_character_set)

        # Patient directory: <PatientName> or <PatientID>.
        patient_directory = decode(
            data_set.get(
                odil.registry.PatientName, 
                data_set.get(odil.registry.PatientID))[0])

        # Study directory: <StudyID>_<StudyDescription>, both parts are
        # optional. If both tags are missing or empty, raise an exception
        study_directory = []
        study_id = data_set.get(odil.registry.StudyID)
        if study_id:
            study_directory.append(decode(study_id[0]))
        study_description = data_set.get(odil.registry.StudyDescription)
        if study_description:
            study_directory.append(decode(study_description[0]))

        if not study_directory:
            raise Exception("Study ID and Study Description are both missing")

        study_directory = "_".join(study_directory)

        # Study directory: <SeriesNumber>_<SeriesDescription>, both parts are
        # optional. If both tags are missing or empty, raise an exception
        series_directory = []
        reconstruction = None
        series_number = data_set.get(odil.registry.SeriesNumber)
        if series_number:
            series_number = series_number[0]
            if series_number > 2**16:
                # Bruker ID based on experiment number and reconstruction number
                # is not readable: separate the two values
                experiment, reconstruction = divmod(series_number, 2**16) 
                series_directory.append(str(experiment))
            else:
                series_directory.append(str(series_number))
        if not self.iso_9660:
            series_description = data_set.get(odil.registry.SeriesDescription)
            if series_description:
                series_directory.append(decode(series_description[0]))

        if not series_directory:
            raise Exception(
                "Series Number and Series Description are both missing")

        series_directory = "_".join(series_directory)

        if self.iso_9660:
            patient_directory = self.to_iso_9660(patient_directory)
            study_directory = self.to_iso_9660(study_directory)
            series_directory = self.to_iso_9660(series_directory)
        
        if reconstruction is not None:
            series_directory = os.path.join(
                series_directory, str(reconstruction))

        return os.path.join(patient_directory, study_directory, series_directory)

    def to_iso_9660(self, value):
        """Return an ISO-9660 compatible version of input string."""
        value = value[:8].upper()
        value = re.sub(r"[^A-Z0-9_]", "_", value)
        return value
