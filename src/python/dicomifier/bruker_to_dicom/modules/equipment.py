#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

from . import cached

GeneralEquipment = [ # PS 3.3, C.7.5.1
    ("ORIGIN", "Manufacturer", 2, None),
    ("VisuInstitution", "InstitutionName", 3, None),
    ("VisuStation", "StationName", 3, None),
    (
        None, "SoftwareVersions", 3, 
        cached("__SoftwareVersions")(
            lambda d,g,i: d.get("VisuCreator", [])+d.get("VisuCreatorVersion", []))),
    ("VisuSystemOrderNumber", "DeviceSerialNumber", 3, None),
]

EnhancedGeneralEquipment = [ # PS 3.3, C.7.5.2
    ("ORIGIN", "Manufacturer", 1, None),
    ("VisuStation", "ManufacturerModelName", 1, None),
    # WARNING : the device number seems to be missing in Paravision 5.1 it was
    # consequently changed into type 2
    ("VisuSystemOrderNumber", "DeviceSerialNumber", 2, None),
    (
        None, "SoftwareVersions", 1,
        cached("__SoftwareVersions")(
            lambda d,g,i: d.get("VisuCreator", [])+d.get("VisuCreatorVersion", []))),
]
