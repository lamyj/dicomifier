import unittest

import numpy

import dicomifier
import odil

class TestImage(unittest.TestCase):

    # For the get_geometry function, we assume that it cannot be possible to have multiple
    # orientations in the data_set frames (as the division was done before any call to get_geometry)

    # No need to create a setUp function here
    default_origin = numpy.zeros((3,)).tolist()
    default_spacing = numpy.ones((3,)).tolist()
    default_direction = numpy.identity(3)

    def test_get_geometry_default(self):
        data_set = odil.DataSet()
        # Case 1 : simple data Set => return default
        val = dicomifier.dicom_to_nifti.image.get_geometry([(data_set, 0)])
        self.assertEqual(val[0], self.default_origin)
        self.assertEqual(val[1], self.default_spacing)
        numpy.testing.assert_array_equal(val[2], self.default_direction)

    def test_get_geometry_no_orientation(self):
        data_set = odil.DataSet()
        shared = odil.DataSet()
        per_frame = []
        first_frame = odil.DataSet()
        plane_position_seq = odil.DataSet()
        plane_position_seq.add("ImagePositionPatient", [-20., -14., -4.5])
        first_frame.add("PlanePositionSequence", [plane_position_seq])
        per_frame.append(first_frame)
        data_set.add("SharedFunctionalGroupsSequence", [shared])
        data_set.add("PerFrameFunctionalGroupsSequence", per_frame)
        val = dicomifier.dicom_to_nifti.image.get_geometry([(data_set, 0)])
        self.assertEqual(list(val[0]), [-20., -14., -4.5])
        self.assertEqual(val[1], self.default_spacing)
        numpy.testing.assert_array_equal(val[2], self.default_direction)

    def test_get_geometry_different_spacing(self):
        data_set = odil.DataSet()
        shared = odil.DataSet()
        plane_orientation_seq = odil.DataSet()
        plane_orientation_seq.add("ImageOrientationPatient", [1.0, 0.0, 0.0, 0.0, 1.0, 0.0])
        shared.add("PlaneOrientationSequence", [plane_orientation_seq])
        
        per_frame = []
        
        first_frame = odil.DataSet()
        plane_position_seq = odil.DataSet()
        plane_position_seq.add("ImagePositionPatient", [-20., -14., -4.5])
        first_frame.add("PlanePositionSequence", [plane_position_seq])
        pixel_measures_sequence = odil.DataSet()
        pixel_measures_sequence.add("PixelSpacing", [0.2, 0.2])
        first_frame.add("PixelMeasuresSequence",  [pixel_measures_sequence])
        per_frame.append(first_frame)
        
        second_frame = odil.DataSet()
        plane_position_seq = odil.DataSet()
        plane_position_seq.add("ImagePositionPatient", [-20., -14., -4.])
        second_frame.add("PlanePositionSequence", [plane_position_seq])
        pixel_measures_sequence = odil.DataSet()
        pixel_measures_sequence.add("PixelSpacing", [0.2, 0.3])
        second_frame.add("PixelMeasuresSequence",  [pixel_measures_sequence])
        per_frame.append(second_frame)
        
        data_set.add("SharedFunctionalGroupsSequence", [shared])
        data_set.add("PerFrameFunctionalGroupsSequence", per_frame)
        data_set.add("NumberOfFrames", [len(per_frame)])
        
        val = dicomifier.dicom_to_nifti.image.get_geometry([(data_set, 0), (data_set, 1)])
        # Here we have two frames with different spacings, so we should only keep the first spacing 
        self.assertEqual(list(val[0]), [-20., -14., -4.5])
        self.assertEqual(val[1], [0.2, 0.2, 0.5])
        direction = numpy.identity(3)
        numpy.testing.assert_array_equal(val[2], direction)

    def test_get_geometry_missing_spacing(self):
        data_set = odil.DataSet()
        shared = odil.DataSet()
        plane_orientation_seq = odil.DataSet()
        plane_orientation_seq.add("ImageOrientationPatient", [1.0, 0.0, 0.0, 0.0, 1.0, 0.0])
        shared.add("PlaneOrientationSequence", [plane_orientation_seq])
        
        per_frame = []
        
        first_frame = odil.DataSet()
        plane_position_seq = odil.DataSet()
        plane_position_seq.add("ImagePositionPatient", [-20., -14., -4.5])
        first_frame.add("PlanePositionSequence", [plane_position_seq])
        per_frame.append(first_frame)
        
        second_frame = odil.DataSet()
        plane_position_seq = odil.DataSet()
        plane_position_seq.add("ImagePositionPatient", [-20., -14., -4.])
        second_frame.add("PlanePositionSequence", [plane_position_seq])
        per_frame.append(second_frame)
        
        data_set.add("SharedFunctionalGroupsSequence",[shared])
        data_set.add("PerFrameFunctionalGroupsSequence",per_frame)
        data_set.add("NumberOfFrames", [len(per_frame)])
        val = dicomifier.dicom_to_nifti.image.get_geometry([(data_set, 0), (data_set, 1)])
        # Here we have no spacing, so we will return the default one
        self.assertEqual(list(val[0]), [-20., -14., -4.5])
        self.assertEqual(val[1], self.default_spacing)
        direction = numpy.identity(3)
        numpy.testing.assert_array_equal(val[2], direction)

    def test_get_geometry_one_frame_with_spacing(self):
        data_set = odil.DataSet()
        data_set.add("ImageOrientationPatient", [1.0, 0.0, 0.0, 0.0, 1.0, 0.0])
        data_set.add("ImagePositionPatient", [-20., -14., -4.5])
        data_set.add("PixelSpacing", [0.2, 0.2])
        val = dicomifier.dicom_to_nifti.image.get_geometry([(data_set, None)])
        self.assertEqual(list(val[0]), [-20., -14., -4.5])
        self.assertEqual(val[1], [0.2, 0.2, 1.0])
        direction = numpy.identity(3)
        numpy.testing.assert_array_equal(val[2], direction)

    def test_get_geometry_same_positions_found(self):
        data_set = odil.DataSet()
        shared = odil.DataSet()
        pixel_measures_sequence = odil.DataSet()
        pixel_measures_sequence.add("PixelSpacing", [0.2, 0.2])
        shared.add("PixelMeasuresSequence", [pixel_measures_sequence])
        plane_orientation_seq = odil.DataSet()
        plane_orientation_seq.add("ImageOrientationPatient", [1.0, 0.0, 0.0, 0.0, 1.0, 0.0])
        shared.add("PlaneOrientationSequence", [plane_orientation_seq])
        per_frame = []
        first_frame = odil.DataSet()
        plane_position_seq = odil.DataSet()
        plane_position_seq.add("ImagePositionPatient", [-20., -14., -4.5])
        first_frame.add("PlanePositionSequence", [plane_position_seq])
        per_frame.append(first_frame)
        second_frame = odil.DataSet()
        plane_position_seq.add("ImagePositionPatient", [-20., -14., -4.5])
        second_frame.add("PlanePositionSequence", [plane_position_seq])
        per_frame.append(second_frame)
        data_set.add("SharedFunctionalGroupsSequence", [shared])
        data_set.add("PerFrameFunctionalGroupsSequence", per_frame)
        data_set.add("NumberOfFrames", [len(per_frame)])
        val = dicomifier.dicom_to_nifti.image.get_geometry([(data_set, 0), (data_set, 1)])
        # Here we have two frames with different spacings, so we should only keep the first spacing
        self.assertEqual(list(val[0]), [-20., -14., -4.5])
        self.assertEqual(val[1], [0.2, 0.2, 1.0])
        direction = numpy.identity(3)
        numpy.testing.assert_array_equal(val[2], direction)

    def test_get_geometry_multi_normal(self):
        data_set = odil.DataSet()
        shared = odil.DataSet()
        pixel_measures_sequence = odil.DataSet()
        pixel_measures_sequence.add("PixelSpacing", [0.2, 0.4])
        shared.add("PixelMeasuresSequence", [pixel_measures_sequence])
        plane_orientation_seq = odil.DataSet()
        plane_orientation_seq.add("ImageOrientationPatient", [1.0, 0.0, 0.0, 0.0, 1.0, 0.0])
        shared.add("PlaneOrientationSequence", [plane_orientation_seq])
        
        per_frame = []
        
        first_frame = odil.DataSet()
        plane_position_seq = odil.DataSet()
        plane_position_seq.add("ImagePositionPatient", [-20., -14., -4.5])
        first_frame.add("PlanePositionSequence", [plane_position_seq])
        per_frame.append(first_frame)
        
        second_frame = odil.DataSet()
        plane_position_seq = odil.DataSet()
        plane_position_seq.add("ImagePositionPatient", [-20., -14., -4.])
        second_frame.add("PlanePositionSequence", [plane_position_seq])
        per_frame.append(second_frame)
        
        data_set.add("SharedFunctionalGroupsSequence", [shared])
        data_set.add("PerFrameFunctionalGroupsSequence", per_frame)
        data_set.add("NumberOfFrames", [len(per_frame)])
        val = dicomifier.dicom_to_nifti.image.get_geometry([(data_set, 0), (data_set, 1)])
        self.assertEqual(list(val[0]), [-20., -14., -4.5])
        self.assertEqual(val[1], [0.2, 0.4, 0.5])
        direction = numpy.identity(3)
        numpy.testing.assert_array_equal(val[2], direction)

    def test_get_geometry_single_normal(self):
        data_set = odil.DataSet()
        data_set.add("ImageOrientationPatient", [1.0, 0.0, 0.0, 0.0, 1.0, 0.0])
        data_set.add("ImagePositionPatient", [-20., -14., -4.5])
        data_set.add("PixelSpacing", [0.2, 0.2])
        val = dicomifier.dicom_to_nifti.image.get_geometry([(data_set, None)])
        data_set_2 = odil.DataSet()
        data_set_2.add("ImageOrientationPatient", [1.0, 0.0, 0.0, 0.0, 1.0, 0.0])
        data_set_2.add("ImagePositionPatient", [-20., -14., -4.])
        data_set_2.add("PixelSpacing", [0.2, 0.2])
        val = dicomifier.dicom_to_nifti.image.get_geometry([(data_set, None), (data_set_2, None)])
        self.assertEqual(list(val[0]), [-20., -14., -4.5])
        self.assertEqual(val[1], [0.2, 0.2, 0.5])
        direction = numpy.identity(3)
        numpy.testing.assert_array_equal(val[2], direction)

if __name__ == "__main__":
    unittest.main()
