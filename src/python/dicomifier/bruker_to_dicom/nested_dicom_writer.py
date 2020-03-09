import os
import re
import odil

class NestedDICOMWriter(object):
    def __init__(self, root, iso_9660, transfer_syntax):
        self.root = root
        self.iso_9660 = iso_9660
        self.transfer_syntax = transfer_syntax
        self.files = []
        self._counts = {}

    def __call__(self, data_set):
        directory = os.path.join(self.root, self.get_series_directory(data_set))
        if not os.path.isdir(directory):
            os.makedirs(directory)

        if self.iso_9660:
            filename = "IM{:06d}".format(1+self._counts.setdefault(directory, 0))
        else:
            filename = data_set.as_string("SOPInstanceUID")[0].decode()

        destination = os.path.join(directory, filename)
        with odil.open(destination, "wb") as fd:
            odil.Writer.write_file(
                data_set, fd, odil.DataSet(), self.transfer_syntax)
        self.files.append(destination)
        self._counts[directory] += 1

    def get_series_directory(self, data_set):
        """ Return the directory associated with the patient, study and series
            of the DICOM data set.
        """

        def has_element(tag, getter):
            return tag in data_set and getter(tag)

        def decode(value):
            return odil.as_unicode(
                value,
                data_set.as_string("SpecificCharacterSet")
                if "SpecificCharacterSet" in data_set else odil.Value.Strings())

        # Patient directory: <PatientName> or <PatientID>.
        patient_directory = None
        if has_element("PatientName", data_set.as_string):
            patient_directory = decode(data_set.as_string("PatientName")[0])
        else:
            patient_directory = decode(data_set.as_string("PatientID")[0])

        # Study directory: <StudyID>_<StudyDescription>, both parts are
        # optional. If both tags are missing or empty, raise an exception
        study_directory = []
        if has_element("StudyID", data_set.as_string):
            study_directory.append(decode(data_set.as_string("StudyID")[0]))
        if has_element("StudyDescription", data_set.as_string):
            study_directory.append(
                decode(data_set.as_string("StudyDescription")[0]))

        if not study_directory:
            raise Exception("Study ID and Study Description are both missing")

        study_directory = "_".join(study_directory)

        # Study directory: <SeriesNumber>_<SeriesDescription>, both parts are
        # optional. If both tags are missing or empty, raise an exception
        series_directory = []
        if has_element("SeriesNumber", data_set.as_int):
            series_number = data_set.as_int("SeriesNumber")[0]
            if series_number > 2**16:
                # Bruker ID based on experiment number and reconstruction number
                # is not readable: separate the two values
                series_directory.append(str(divmod(series_number, 2**16)[0]))
            else:
                series_directory.append(str(series_number))
        if not self.iso_9660:
            if has_element("SeriesDescription", data_set.as_string):
                series_directory.append(
                    decode(data_set.as_string("SeriesDescription")[0]))

        if not series_directory:
            raise Exception("Series Number and Series Description are both missing")

        series_directory = "_".join(series_directory)

        if self.iso_9660:
            patient_directory = self.to_iso_9660(patient_directory)
            study_directory = self.to_iso_9660(study_directory)
            series_directory = self.to_iso_9660(series_directory)

        return os.path.join(patient_directory, study_directory, series_directory)

    def to_iso_9660(self, value):
        """Return an ISO-9660 compatible version of input string."""
        value = value[:8].upper()
        value = re.sub(r"[^A-Z0-9_]", "_", value)
        return value
