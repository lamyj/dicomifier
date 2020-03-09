import unittest

import numpy

import dicomifier

class TestFrameIndexGenerator(unittest.TestCase):

    def setUp(self):
        bruker_data_set = {
            "VisuFGOrderDesc" : [
                [5, "FG_SLICE", "", 0, 2], [13, "FG_SLICE", "", 2, 1]],
            "VisuGroupDepVals" : [
                ["VisuCoreOrientation", 0] , 
                ["VisuCorePosition", 0], 
                ["VisuAcqEchoTime", 0]]
        }
        self.fg = dicomifier.bruker_to_dicom.FrameIndexGenerator(bruker_data_set)

    def tearDown(self):
        self.fg = None

    def test_constructor(self): # Also testing the _get_frame_groups function
        self.assertEqual(
            self.fg.frame_groups, [ 
                [13, "FG_SLICE", ["VisuAcqEchoTime"]], 
                [5,"FG_SLICE",["VisuCoreOrientation", "VisuCorePosition"]]])

    def test_get_linear_index(self):
        self.assertEqual(self.fg.get_linear_index([1,2]), 7)

    def test_get_frames_count(self):
        self.assertEqual(self.fg._get_frames_count(), 65)

    def test_get_dependent_fields(self):
        depedent_fields = set()
        for df in self.fg.dependent_fields:
            depedent_fields.add(df)
        self.assertEqual(
            depedent_fields, 
            set(["VisuCoreOrientation", "VisuCorePosition", "VisuAcqEchoTime"]))

if __name__ == "__main__":
    unittest.main()
