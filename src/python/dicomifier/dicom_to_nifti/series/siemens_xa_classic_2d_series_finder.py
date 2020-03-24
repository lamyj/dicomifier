import odil

class SiemensXAClassic2DSeriesFinder(object):
    """ Siemens MRI scanners with version XA have an export option which causes
        multi-volume series (e.g. fMRI or diffusion) to be exported as separate
        series with differente Series Instance UIDs, but with the same Series
        Number.
    """
    
    def __init__(self):
        self.series_instance_uid = None
    
    def __call__(self, data_set):
        self.series_instance_uid = None
        
        data = [None, None]
        if data_set.has(odil.registry.SoftwareVersions):
            value = data_set.as_string(odil.registry.SoftwareVersions)
            if value:
                data[0] = value[0]
        if data_set.has(odil.registry.ImageType):
            value = data_set.as_string(odil.registry.ImageType)
            data[1] = (value[-1] == b"MFSPLIT")
        
        if data[0].startswith(b"syngo MR XA") and data[1]:
            for item in data_set.as_data_set(odil.registry.RelatedSeriesSequence):
                # Look for Alternate SOP Class instance
                # http://dicom.nema.org/medical/dicom/current/output/chtml/part16/chapter_D.html#DCM_121326
                purpose = item.as_data_set(
                    odil.registry.PurposeOfReferenceCodeSequence)[0]
                designator = purpose.as_string(
                    odil.registry.CodingSchemeDesignator)[0]
                code_value = purpose.as_string(
                    odil.registry.CodeValue)[0]
                if (designator, code_value) == (b"DCM", b"121326"):
                    self.series_instance_uid = item.as_string(
                        odil.registry.SeriesInstanceUID)[0]
                    break
        
        return self.series_instance_uid
    
    def __eq__(self, other):
        return self.series_instance_uid == other.series_instance_uid
    
    def __hash__(self):
        return hash(self.series_instance_uid)
