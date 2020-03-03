import unittest

import numpy

from dicomifier.bruker_to_dicom.enhanced_mr_image_storage import regroup_shared_data
import dicomifier
import odil

class TestEnhancedMrImageStorage(unittest.TestCase):

    def test_regroup_shared_data(self):
        data_set = odil.DataSet()
        data_set.add("NumberOfFrames", [2])

        shared = odil.DataSet()
        orientation = [1.0, 0.0, 0.0, 0.0, 1.0, 0.0]

        firstFrame = odil.DataSet()
        firstPositionSequence = odil.DataSet()
        firstPositionSequence.add("ImagePositionPatient", [0.0, 0.0, 1.0])
        firstOrientationSequence = odil.DataSet()
        firstOrientationSequence.add("ImageOrientationPatient", orientation)
        firstFrame.add("PlanePositionSequence", [firstPositionSequence])
        firstFrame.add("PlaneOrientationSequence", [firstOrientationSequence])

        secondFrame = odil.DataSet()
        secondPositionSequence = odil.DataSet()
        secondPositionSequence.add("ImagePositionPatient", [0.0, 0.0, 2.0])
        secondOrientationSequence = odil.DataSet()
        secondOrientationSequence.add("ImageOrientationPatient", orientation)
        secondFrame.add("PlanePositionSequence", [secondPositionSequence])
        secondFrame.add("PlaneOrientationSequence", [secondOrientationSequence])

        data_set.add("PerFrameFunctionalGroupsSequence", [firstFrame, secondFrame])
        data_set.add("SharedFunctionalGroupsSequence",[shared])

        fg = [
            dicomifier.bruker_to_dicom.frame_groups.PlanePosition,
            dicomifier.bruker_to_dicom.frame_groups.PlaneOrientation
        ]
        regroup_shared_data(data_set, fg)
        for frame_idx in range (2):
            currentFrame = data_set.as_data_set("PerFrameFunctionalGroupsSequence")[frame_idx]
            self.assertFalse(currentFrame.has("PlaneOrientationSequence"))
            self.assertTrue(currentFrame.has("PlanePositionSequence"))
        shared = data_set.as_data_set("SharedFunctionalGroupsSequence")[0]
        self.assertTrue(shared.has("PlaneOrientationSequence"))
        sharedOrientationSeq = shared.as_data_set("PlaneOrientationSequence")[0]
        self.assertEqual(list(sharedOrientationSeq.as_real("ImageOrientationPatient")), orientation)

if __name__ == "__main__":
    unittest.main()