#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

import os
import odil

from ... import logger

class FlatDICOMWriter:
    """ Write DICOM files in a common directory.
    """
    
    def __init__(self, root, iso_9660, transfer_syntax):
        self.root = str(root)
        self.iso_9660 = iso_9660
        self.transfer_syntax = transfer_syntax
        self.files = []

    def __call__(self, data_set):
        if not os.path.isdir(self.root):
            os.makedirs(self.root)

        if self.iso_9660:
            filename = "{:08d}.dcm".format(1+len(self.files))
        else:
            filename = data_set[odil.registry.SOPInstanceUID][0].decode()

        destination = os.path.join(self.root, filename)
        if data_set.get_transfer_syntax():
            logger.info("Overriding requested transfer syntax")
            transfer_syntax = data_set.get_transfer_syntax()
        else:
            transfer_syntax = self.transfer_syntax
        odil.Writer.write_file(
            data_set, destination, odil.DataSet(), transfer_syntax)
        self.files.append(destination)
