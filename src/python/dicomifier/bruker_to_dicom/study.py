#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

GeneralStudy = [ # http://dicom.nema.org/medical/dicom/current/output/chtml/part03/sect_C.7.2.html#sect_C.7.2.1
    ("VisuStudyUid", "StudyInstanceUID", 1, None, None),
    ("VisuStudyDate", "StudyDate", 2, None, None),
    ("VisuStudyDate", "StudyTime", 2, None, None),
    ("VisuStudyReferringPhysician", "ReferringPhysicianName", 2, None, None),
    ("VisuStudyNumber", "StudyID", 2, None, None),
    (None, "AccessionNumber", 2, lambda d,g,i: None, None),
    ("VisuStudyId", "StudyDescription", 3, None, None),
]

PatientStudy = [ # http://dicom.nema.org/medical/dicom/current/output/chtml/part03/sect_C.7.2.2.html
    ("VisuSubjectWeight", "PatientWeight", 3, None, None),
    (None, "PatientSexNeutered", 2, lambda d,g,i: None, None),
]
