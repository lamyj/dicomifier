#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

FrameOfReference = [
    ("VisuUid", "FrameOfReferenceUID", 1, None, None),
    (None, "PositionReferenceIndicator", 2, lambda d,g,i: None, None),
]
