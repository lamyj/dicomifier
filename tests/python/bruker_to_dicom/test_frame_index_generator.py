import unittest

import numpy

import dicomifier

class TestFrameIndexGenerator(unittest.TestCase):

    def setUp(self):
        bruker_data_set = {
            "VisuFGOrderDesc" : [
                [5, "name_1", "", 0, 2],
                [13, "name_2", "", 2, 1],
                [7, "name_3", "", 3, 1]],
            "VisuGroupDepVals" : [
                ["field_1", 0] ,
                ["field_2", 0],
                ["field_3", 0],
                ["field_4", 0]]
        }
        self.fg = dicomifier.bruker_to_dicom.FrameIndexGenerator(bruker_data_set)

    def tearDown(self):
        self.fg = None

    def test_constructor(self): # Also testing the _get_frame_groups function
        self.assertEqual(
            self.fg.frame_groups, [
                [7, "name_3", ["field_4"]],
                [13, "name_2", ["field_3"]],
                [5, "name_1", ["field_1", "field_2"]]])

    def test_get_linear_index(self):
        self.assertEqual(self.fg.get_linear_index([1, 2, 3]), 78)

    def test_get_frames_count(self):
        self.assertEqual(self.fg.frames_count, 455)

    def test_get_dependent_fields(self):
        self.assertEqual(
            set(self.fg.dependent_fields),
            set(["field_1", "field_2", "field_3", "field_4"]))

if __name__ == "__main__":
    unittest.main()
