#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

import odil

from .series_finder import SeriesFinder

class SiemensXAClassic2DSeriesFinder(SeriesFinder):
    """ Siemens MRI scanners with version XA have an export option which causes
        multi-volume series (e.g. fMRI or diffusion) to be exported as separate
        series with differente Series Instance UIDs, but with the same Series
        Number.
    """
    
    def __init__(self):
        SeriesFinder.__init__(self)
    
    def __call__(self, data_set):
        self.series_instance_uid = None
        
        software = data_set.get(odil.registry.SoftwareVersions, [b""])[0]
        is_mfsplit = data_set.get(odil.registry.ImageType, [b""])[0]
        
        if software.startswith(b"syngo MR XA") and is_mfsplit:
            for item in data_set[odil.registry.RelatedSeriesSequence]:
                # Look for Alternate SOP Class instance
                # http://dicom.nema.org/medical/dicom/current/output/chtml/part16/chapter_D.html#DCM_121326
                purpose = item[odil.registry.PurposeOfReferenceCodeSequence][0]
                designator = purpose[odil.registry.CodingSchemeDesignator][0]
                code_value = purpose[odil.registry.CodeValue][0]
                if (designator, code_value) == (b"DCM", b"121326"):
                    self.series_instance_uid = item[odil.registry.SeriesInstanceUID][0]
                    break
        
        return self.series_instance_uid
