import unittest

import numpy

import dicomifier
import odil

class TestOdilGetter(unittest.TestCase):

    def test_getter_binary(self):
        data_set = odil.DataSet()
        pixel_data = [bin(42)]
        data_set.add("PixelData", pixel_data, odil.VR.OB)
        val = dicomifier.dicom_to_nifti.odil_getter._getter(data_set, odil.registry.PixelData)
        self.assertEqual((bin(42),), val)

    def test_getter_data_set(self):
        data_set = odil.DataSet()
        planePositionSeq = odil.DataSet()
        position = [0.0, 0.0, 1.0]
        planePositionSeq.add("ImagePositionPatient", position)
        data_set.add("PlanePositionSequence", [planePositionSeq])
        val = dicomifier.dicom_to_nifti.odil_getter._getter(data_set, odil.registry.PlanePositionSequence)
        self.assertEqual((planePositionSeq,) , val) 

    def test_getter_int(self):
        data_set = odil.DataSet()
        data_set.add("NumberOfFrames", [42])
        val = dicomifier.dicom_to_nifti.odil_getter._getter(data_set, odil.registry.NumberOfFrames)
        self.assertEqual((42,), val)

    def test_getter_real(self):
        data_set = odil.DataSet()
        data_set.add("PatientWeight", [60.5])
        val = dicomifier.dicom_to_nifti.odil_getter._getter(data_set, odil.registry.PatientWeight)
        self.assertEqual((60.5,), val)

    def test_getter_string(self):
        data_set = odil.DataSet()
        data_set.add("PatientName", ["Duck^Donald"])
        val = dicomifier.dicom_to_nifti.odil_getter._getter(data_set, odil.registry.PatientName)
        self.assertEqual(("Duck^Donald",), val)

    def test_default_getter(self):
        #the function should return None when element is not found
        data_set = odil.DataSet()
        val = dicomifier.dicom_to_nifti.odil_getter._default_getter(data_set, odil.registry.PatientName)
        self.assertEqual(None, val)

    def test_check_frame_idx_out_of_bounds(self):
        data_set = odil.DataSet()
        first_frame = odil.DataSet()
        per_frame = [first_frame]
        data_set.add("PerFrameFunctionalGroupsSequence", per_frame)
        data_set.add("NumberOfFrames", [1])
        frame_idx = 1
        numberOfFrames = data_set.as_int("NumberOfFrames")[0]
        with self.assertRaises(Exception) as context:
            val = list(dicomifier.dicom_to_nifti.odil_getter.check_frame_index(data_set, 1))
        self.assertTrue("Frame index out of bound ({}/{})".format(frame_idx, numberOfFrames) in context.exception)

    def test_get_position_single_frame(self):
        data_set = odil.DataSet()
        planePositionSeq = odil.DataSet()
        position = [0.0, 0.0, 1.0]
        planePositionSeq.add("ImagePositionPatient", position)
        data_set.add("PlanePositionSequence", [planePositionSeq])
        val = dicomifier.dicom_to_nifti.odil_getter._get_position(data_set, 0)
        self.assertEqual(None, val)

    def test_get_position(self):
        data_set = odil.DataSet()
        first_frame = odil.DataSet()
        planePositionSeq = odil.DataSet()
        position = [0.0, 0.0, 1.0]
        planePositionSeq.add("ImagePositionPatient", position)
        first_frame.add("PlanePositionSequence", [planePositionSeq])
        per_frame = [first_frame]
        data_set.add("PerFrameFunctionalGroupsSequence", per_frame)
        data_set.add("NumberOfFrames", [1])
        val = list(dicomifier.dicom_to_nifti.odil_getter._get_position(data_set, 0))
        self.assertEqual([0.0, 0.0, 1.0], val)

    def test_get_spacing_no_spacing(self):
        data_set = odil.DataSet()
        val = dicomifier.dicom_to_nifti.odil_getter._get_spacing(data_set, 0)
        self.assertEqual(None, val)

    def test_get_spacing_top_level(self):
        data_set = odil.DataSet()
        spacing = [0.2, 0.2]
        data_set.add("PixelSpacing", spacing)
        val = list(dicomifier.dicom_to_nifti.odil_getter._get_spacing(data_set, None))
        self.assertEqual([0.2, 0.2], val)

    def test_get_spacing_with_index(self):
        data_set = odil.DataSet()
        first_frame = odil.DataSet()
        pixelMeasuresSeq = odil.DataSet()
        spacing = [0.2, 0.2]
        pixelMeasuresSeq.add("PixelSpacing", spacing)
        first_frame.add("PixelMeasuresSequence", [pixelMeasuresSeq])
        per_frame = [first_frame]
        data_set.add("PerFrameFunctionalGroupsSequence", per_frame)
        data_set.add("NumberOfFrames", [1])
        val = list(dicomifier.dicom_to_nifti.odil_getter._get_spacing(data_set, 0))
        self.assertEqual([0.2, 0.2], val)

    def test_get_in_stack_position_index_none(self):
        data_set = odil.DataSet()
        dimension_index_seq = odil.DataSet()
        data_set.add("DimensionIndexSequence", [dimension_index_seq])
        idx = dicomifier.dicom_to_nifti.odil_getter.get_in_stack_position_index(data_set)
        self.assertEqual(idx, None)
        data_set_empty = odil.DataSet()
        idx = dicomifier.dicom_to_nifti.odil_getter.get_in_stack_position_index(data_set_empty)
        self.assertEqual(idx, None)

    def test_get_in_stack_position_index(self):
        data_set = odil.DataSet()
        stack_id_seq = odil.DataSet()
        stack_id_seq.add("DimensionOrganizationUID", ["1.3.6.1.4.1.5962.1.6.5012.1.0.1166546115.14677"])
        stack_id_seq.add("DimensionIndexPointer", ["00209056"])
        stack_id_seq.add("FunctionalGroupPointer", ["00209111"])
        in_stack_seq = odil.DataSet()
        in_stack_seq.add("DimensionOrganizationUID", ["1.3.6.1.4.1.5962.1.6.5012.1.0.1166546115.14677"])
        in_stack_seq.add("DimensionIndexPointer", ["00209057"])
        in_stack_seq.add("FunctionalGroupPointer", ["00209111"])
        data_set.add("DimensionIndexSequence", [stack_id_seq, in_stack_seq])
        idx = dicomifier.dicom_to_nifti.odil_getter.get_in_stack_position_index(data_set)
        self.assertEqual(idx, 1)

    def test_get_dimension_index_seq_no_in_stack_pos(self):
        data_set = odil.DataSet()
        stack_id_seq = odil.DataSet()
        stack_id_seq.add("DimensionOrganizationUID", ["1.3.6.1.4.1.5962.1.6.5012.1.0.1166546115.14677"])
        stack_id_seq.add("DimensionIndexPointer", ["00209056"])
        stack_id_seq.add("FunctionalGroupPointer", ["00209111"])
        data_set.add("DimensionIndexSequence", [stack_id_seq])
        first_frame = odil.DataSet()
        first_frame.add("DimensionIndexValues", [1]) #Study ID
        data_set.add("FrameContentSequence", [first_frame])
        idx = dicomifier.dicom_to_nifti.odil_getter.get_in_stack_position_index(data_set)
        with self.assertRaises(Exception) as context:
            val = list(dicomifier.dicom_to_nifti.odil_getter.get_dimension_index_seq(first_frame, "DimensionIndexValues", idx))
        self.assertTrue("Dimension Index Values found in Frame content but there is no InStackPosition" in context.exception)

    def test_get_dimension_index_seq(self):
        data_set = odil.DataSet()
        stack_id_seq = odil.DataSet()
        stack_id_seq.add("DimensionOrganizationUID", ["1.3.6.1.4.1.5962.1.6.5012.1.0.1166546115.14677"])
        stack_id_seq.add("DimensionIndexPointer", ["00209056"])
        stack_id_seq.add("FunctionalGroupPointer", ["00209111"])
        in_stack_seq = odil.DataSet()
        in_stack_seq.add("DimensionOrganizationUID", ["1.3.6.1.4.1.5962.1.6.5012.1.0.1166546115.14677"])
        in_stack_seq.add("DimensionIndexPointer", ["00209057"])
        in_stack_seq.add("FunctionalGroupPointer", ["00209111"])
        data_set.add("DimensionIndexSequence", [stack_id_seq, in_stack_seq])
        frame_content_seq = odil.DataSet()
        frame_content_seq.add("DimensionIndexValues", [3,10]) # StackID , In Stack Pos
        idx = dicomifier.dicom_to_nifti.odil_getter.get_in_stack_position_index(data_set)
        val = list(dicomifier.dicom_to_nifti.odil_getter.get_dimension_index_seq(frame_content_seq, "DimensionIndexValues", idx))
        self.assertEqual(val, [3])

    def test_diffusion_getter_none(self):
        data_set = odil.DataSet()
        val = dicomifier.dicom_to_nifti.odil_getter._diffusion_getter(data_set, odil.registry.MRDiffusionSequence)
        self.assertEqual(val, None)

    def test_diffusion_getter_directionality_iso_none(self):
        data_set = odil.DataSet()
        mr_diff_seq = odil.DataSet()
        mr_diff_seq.add("DiffusionBValue", [1000.])
        mr_diff_seq.add("DiffusionDirectionality", ["ISOTROPIC"])
        data_set.add("MRDiffusionSequence", [mr_diff_seq])
        val = dicomifier.dicom_to_nifti.odil_getter._diffusion_getter(data_set, odil.registry.MRDiffusionSequence)
        self.assertEqual(val, None)

    def test_diffusion_getter(self):
        data_set = odil.DataSet()
        mr_diff_seq = odil.DataSet()
        mr_diff_seq.add("DiffusionBValue", [1000.])
        mr_diff_seq.add("DiffusionDirectionality", ["BMATRIX"])
        diff_grad_seq = odil.DataSet()
        diff_grad_seq.add("DiffusionGradientOrientation", [-0.5, 0.8, -0.2])
        mr_diff_seq.add("DiffusionGradientDirectionSequence", [diff_grad_seq])
        diff_matrix_seq = odil.DataSet()
        diff_matrix_seq.add("DiffusionBValueXX", [380.])
        diff_matrix_seq.add("DiffusionBValueXY", [-636.])
        diff_matrix_seq.add("DiffusionBValueXZ", [147.])
        diff_matrix_seq.add("DiffusionBValueYY", [1064.])
        diff_matrix_seq.add("DiffusionBValueYZ", [-247.])
        diff_matrix_seq.add("DiffusionBValueZZ", [57.])
        mr_diff_seq.add("DiffusionBMatrixSequence", [diff_matrix_seq])
        data_set.add("MRDiffusionSequence", [mr_diff_seq])
        val = dicomifier.dicom_to_nifti.odil_getter._diffusion_getter(data_set, odil.registry.MRDiffusionSequence)
        self.assertEqual(val, ((1000.,) ,(380., -636., 147., 1064., -247., 57.)))

if __name__ == "__main__":
    unittest.main()