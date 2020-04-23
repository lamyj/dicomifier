import unittest

import numpy

import dicomifier
import odil

class TestConvert(unittest.TestCase):
    def test_convert_element_getter_none(self):
        bruker_data_set = {"VisuSubjectName" : [b"Mouse^Mickey"]}
        dicom_data_set = odil.DataSet()
        generator = dicomifier.bruker_to_dicom.FrameIndexGenerator(bruker_data_set)
        frame_index = [0]
        vr_finder_object = odil.VRFinder()
        vr_finder_function = lambda tag: vr_finder_object(
            tag, odil.DataSet(), odil.registry.ImplicitVRLittleEndian)

        val = dicomifier.bruker_to_dicom.convert.convert_element(
            bruker_data_set, dicom_data_set,
            "VisuSubjectName", "PatientName", 1, None,
            frame_index, generator, vr_finder_function
        )

        # Check first the returned value of the convert_element function
        self.assertEqual(val, [b"Mouse^Mickey"])
        # Check then the content of the dicom_data_set (should contain the correct value...)
        dicom_val = list(dicom_data_set.as_string("PatientName"))
        self.assertEqual([b"Mouse^Mickey"], dicom_val)

    def test_convert_element_getter(self):
        bruker_data_set = {}
        dicom_data_set = odil.DataSet()
        generator = dicomifier.bruker_to_dicom.FrameIndexGenerator(bruker_data_set)
        frame_index = [0]
        vr_finder_object = odil.VRFinder()
        vr_finder_function = lambda tag: vr_finder_object(
            tag, odil.DataSet(), odil.registry.ImplicitVRLittleEndian)

        val = dicomifier.bruker_to_dicom.convert.convert_element(
            bruker_data_set, dicom_data_set,
            None, "PixelPresentation", 1, lambda d,g,i : [b"MONOCHROME"], 
            frame_index, generator, vr_finder_function
        )

        self.assertEqual(val, [b"MONOCHROME"])
        dicom_val = list(dicom_data_set.as_string("PixelPresentation"))
        self.assertEqual([b"MONOCHROME"], dicom_val)

    def test_convert_element_getter_frame_index(self):
        bruker_data_set = {
            # Only two group, with each one a different Echo Time
            "VisuFGOrderDesc" : [[2, "FG_SLICE", "", 0, 1]],
            "VisuGroupDepVals" : [["VisuAcqEchoTime", 0]],
            "VisuAcqEchoTime" : [10., 20.]
        }
        dicom_data_set = odil.DataSet()
        generator = dicomifier.bruker_to_dicom.FrameIndexGenerator(bruker_data_set)
        frame_index = [1]
        vr_finder_object = odil.VRFinder()
        vr_finder_function = lambda tag: vr_finder_object(
            tag, odil.DataSet(), odil.registry.ImplicitVRLittleEndian)

        val = dicomifier.bruker_to_dicom.convert.convert_element(
            bruker_data_set, dicom_data_set,
            "VisuAcqEchoTime", "EchoTime", 1, None,
            frame_index, generator, vr_finder_function
        )

        self.assertEqual(val, [20.])
        dicom_val = list(dicom_data_set.as_real("EchoTime"))
        self.assertEqual([20.], dicom_val)

    def test_convert_element_required(self):
        bruker_data_set = {}
        dicom_data_set = odil.DataSet()
        generator = dicomifier.bruker_to_dicom.FrameIndexGenerator(bruker_data_set)
        frame_index = [0]
        vr_finder_object = odil.VRFinder()
        vr_finder_function = lambda tag: vr_finder_object(
            tag, odil.DataSet(), odil.registry.ImplicitVRLittleEndian)

        with self.assertRaises(Exception) as context:
            val = dicomifier.bruker_to_dicom.convert.convert_element(
                bruker_data_set, dicom_data_set,
                "VisuSubjectName", "PatientName", 1, None,
                frame_index, generator, vr_finder_function
            )

        self.assertTrue("PatientName must be present" in str(context.exception))

if __name__ == "__main__":
    unittest.main()
