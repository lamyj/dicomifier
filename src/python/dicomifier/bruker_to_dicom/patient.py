#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

Patient= [ # http://dicom.nema.org/medical/dicom/current/output/chtml/part03/sect_C.7.html#sect_C.7.1.1
    ("VisuSubjectName", "PatientName", 2, None, None),
    ("VisuSubjectName", "PatientID", 2, None, None),
    ("VisuSubjectBirthDate", "PatientBirthDate", 2, None, None),
    (
        "VisuSubjectSex", "PatientSex", 2, None, 
        {
            "MALE": "M", "FEMALE": "F", "UNDEFINED": "O", "UNKNOWN": "O", 
            None: None 
        }
    ),
    ("VisuSubjectComment", "PatientComments", 3, None, None),
    (None, "PatientBreedDescription", 2, lambda d,g,i: None, None),
    (None, "PatientBreedCodeSequence", 2, lambda d,g,i: None, None),
    (None, "BreedRegistrationSequence", 2, lambda d,g,i: None, None),
    (None, "ResponsiblePerson", 2, lambda d,g,i: None, None),
    (None, "ResponsibleOrganization", 2, lambda d,g,i: None, None) 
]
