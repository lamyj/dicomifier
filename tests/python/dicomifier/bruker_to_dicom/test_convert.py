import unittest

import numpy

import dicomifier
import odil

class TestConvert(unittest.TestCase):
    #The only function we can test is the to_iso_9660() one,
    #the others require real data_sets, and frame_iterator..
    def test_to_iso_9660(self):
        self.assertEqual(dicomifier.bruker_to_dicom.convert.to_iso_9660("filenametoolong"), "FILENAME")
        self.assertEqual(dicomifier.bruker_to_dicom.convert.to_iso_9660("Subj1&2"), "SUBJ1_2")

    def test_convert_element_getter_none(self):
        bruker_data_set = {"VisuSubjectName" : ["Mouse^Mickey"]}
        dicom_data_set = odil.DataSet()
        generator = dicomifier.bruker_to_dicom.FrameIndexGenerator(bruker_data_set)
        frame_index = [0]
        vr_finder_object = odil.VRFinder()
        vr_finder_function = lambda tag: vr_finder_object(tag, odil.DataSet(), odil.registry.ImplicitVRLittleEndian)

        val = dicomifier.bruker_to_dicom.convert.convert_element(
            bruker_data_set, dicom_data_set,
            "VisuSubjectName", "PatientName", 1,
            None, None,
            frame_index, generator, vr_finder_function
        )

        # Check first the returned value of the convert_element function
        self.assertEqual(val, ["Mouse^Mickey"])
        # Check then the content of the dicom_data_set (should contain the correct value...)
        dicom_val = list(dicom_data_set.as_string("PatientName"))
        self.assertEqual(["Mouse^Mickey"], dicom_val)

    def test_convert_element_getter(self):
        bruker_data_set = {}
        dicom_data_set = odil.DataSet()
        generator = dicomifier.bruker_to_dicom.FrameIndexGenerator(bruker_data_set)
        frame_index = [0]
        vr_finder_object = odil.VRFinder()
        vr_finder_function = lambda tag: vr_finder_object(tag, odil.DataSet(), odil.registry.ImplicitVRLittleEndian)

        val = dicomifier.bruker_to_dicom.convert.convert_element(
            bruker_data_set, dicom_data_set,
            None, "PixelPresentation", 1,
            lambda d,g,i : ["MONOCHROME"], None,
            frame_index, generator, vr_finder_function
        )

        self.assertEqual(val, ["MONOCHROME"])
        dicom_val = list(dicom_data_set.as_string("PixelPresentation"))
        self.assertEqual(["MONOCHROME"], dicom_val)

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
        vr_finder_function = lambda tag: vr_finder_object(tag, odil.DataSet(), odil.registry.ImplicitVRLittleEndian)

        val = dicomifier.bruker_to_dicom.convert.convert_element(
            bruker_data_set, dicom_data_set,
            "VisuAcqEchoTime", "EchoTime", 1,
            None, None,
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
        vr_finder_function = lambda tag: vr_finder_object(tag, odil.DataSet(), odil.registry.ImplicitVRLittleEndian)

        with self.assertRaises(Exception) as context:
            val = dicomifier.bruker_to_dicom.convert.convert_element(
                bruker_data_set, dicom_data_set,
                "VisuSubjectName", "PatientName", 1,
                None, None,
                frame_index, generator, vr_finder_function
            )

        self.assertTrue("PatientName must be present" in context.exception)

    def test_convert_element_setter_dict(self):
        bruker_data_set = { "VisuSubjectSex" : ["MALE"]}
        dicom_data_set = odil.DataSet()
        generator = dicomifier.bruker_to_dicom.FrameIndexGenerator(bruker_data_set)
        frame_index = [0]
        vr_finder_object = odil.VRFinder()
        vr_finder_function = lambda tag: vr_finder_object(tag, odil.DataSet(), odil.registry.ImplicitVRLittleEndian)
        val = dicomifier.bruker_to_dicom.convert.convert_element(
            bruker_data_set, dicom_data_set,
            "VisuSubjectSex", "PatientSex", 1,
            None,
            {
                "MALE": "M", "FEMALE": "F", "UNDEFINED": "O", "UNKNOWN": "O",
                None: None
            },
            frame_index, generator, vr_finder_function
        )
        self.assertEqual(val, ["M"])
        dicom_val = list(dicom_data_set.as_string("PatientSex"))
        self.assertEqual(["M"], dicom_val)

    def test_convert_element_setter_function(self):
        bruker_data_set = {
            # Here we make a simple example with only one frame => only one position
            "VisuCorePosition" : [-20., -20., -2.]
        }
        dicom_data_set = odil.DataSet()
        generator = dicomifier.bruker_to_dicom.FrameIndexGenerator(bruker_data_set)
        frame_index = [0]
        vr_finder_object = odil.VRFinder()
        vr_finder_function = lambda tag: vr_finder_object(tag, odil.DataSet(), odil.registry.ImplicitVRLittleEndian)

        val = dicomifier.bruker_to_dicom.convert.convert_element(
            bruker_data_set, dicom_data_set,
            "VisuCorePosition", "ImagePositionPatient", 1,
            lambda d,g,i: numpy.reshape(d["VisuCorePosition"], (-1, 3)),
            lambda x: x[0].tolist(),
            frame_index, generator, vr_finder_function
        )
        self.assertEqual(val, [-20., -20., -2.])
        dicom_val = list(dicom_data_set.as_real("ImagePositionPatient"))
        self.assertEqual([-20., -20., -2.], dicom_val)

if __name__ == "__main__":
    unittest.main()