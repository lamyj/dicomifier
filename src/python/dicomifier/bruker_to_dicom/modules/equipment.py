#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

import functools

GeneralEquipment = [ # PS 3.3, C.7.5.1
    ("ORIGIN", "Manufacturer", 2, None, None),
    ("VisuInstitution", "InstitutionName", 3, None, None),
    ("VisuStation", "StationName", 3, None, None),
    (
        None, "SoftwareVersions", 3, 
        lambda d,g,i: functools.reduce(
            lambda e1, e2: e1+e2,
            [d.get(name, []) for name in ["VisuCreator", "VisuCreatorVersion"]], 
            []
        ),
        None
    ),
    ("VisuSystemOrderNumber", "DeviceSerialNumber", 3, None, None),
]

EnhancedGeneralEquipment = [ # PS 3.3, C.7.5.2
    ("ORIGIN", "Manufacturer", 1, None, None),
    ("VisuStation", "ManufacturerModelName", 1, None, None),
    # WARNING : the device number seems to be missing in Paravision 5.1 it was
    # consequently changed into type 2
    ("VisuSystemOrderNumber", "DeviceSerialNumber", 2, None, None),
    (
        None, "SoftwareVersions", 1,
        lambda d,g,i: functools.reduce(
            lambda e1, e2: e1+e2,
            [d.get(name, []) for name in ["VisuCreator", "VisuCreatorVersion"]],
            []
        ),
        None
    ),
]
