import os
import re
import odil

class FlatDICOMWriter(object):
    def __init__(self, root, iso_9660, transfer_syntax):
        self.root = root
        self.iso_9660 = iso_9660
        self.transfer_syntax = transfer_syntax
        self.files = []

    def __call__(self, data_set):
        if not os.path.isdir(self.root):
            os.makedirs(self.root)

        if self.iso_9660:
            filename = "{:08d}.dcm".format(1+len(os.listdir(self.root)))
        else:
            filename = data_set.as_string("SOPInstanceUID")[0].decode()

        destination = os.path.join(self.root, filename)
        with odil.open(destination, "wb") as fd:
            odil.Writer.write_file(
                data_set, fd, odil.DataSet(), self.transfer_syntax)
        self.files.append(destination)
