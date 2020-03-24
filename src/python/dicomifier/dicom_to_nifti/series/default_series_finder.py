import odil

class DefaultSeriesFinder(object):
    def __init__(self):
        self.series_instance_uid = None
    
    def __call__(self, data_set):
        self.series_instance_uid = None
        if odil.registry.SeriesInstanceUID in data_set:
            value = data_set.as_string(odil.registry.SeriesInstanceUID)
            if len(value) == 0:
                raise Exception(
                    "Invalid DICOM data set: SeriesInstanceUID is empty")
            elif len(value) > 1:
                raise Exception(
                    "Invalid DICOM data set: "
                    "multiple values of SeriesInstanceUID")
            else:
                self.series_instance_uid = value[0]
        return self.series_instance_uid
    
    def __eq__(self, other):
        return self.series_instance_uid == other.series_instance_uid
    
    def __hash__(self):
        return hash(self.series_instance_uid)
