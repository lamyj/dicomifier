import base64
import unittest

import numpy
import odil

import dicomifier

class TestImage(unittest.TestCase):
    def test_get_linear_pixel_data(self):
        buffer = numpy.linspace(1, 11, 10, dtype=numpy.uint16)
        data_set = odil.DataSet(
            odil.registry.ImplicitVRLittleEndian,
            HighBit=[15], BitsAllocated=[16], BitsStored=[15],
            PixelData=[odil.Value.BinaryItem(buffer.tobytes())])
        numpy.testing.assert_almost_equal(
            dicomifier.dicom_to_nifti.image.get_linear_pixel_data(data_set),
            buffer)

    def test_get_shaped_pixel_data(self):
        data_set = odil.DataSet(
            Rows=[5], Columns=[2], SamplesPerPixel=[1], BitsStored=[16])
        buffer = numpy.linspace(1, 11, 10, dtype=numpy.uint16)
        numpy.testing.assert_almost_equal(
            dicomifier.dicom_to_nifti.image.get_shaped_pixel_data(
                data_set, None, buffer),
            buffer.reshape(5,2))

    def test_get_origin(self):
        data_set = odil.DataSet(ImagePositionPatient=[1,2,3])
        self.assertSequenceEqual(
            dicomifier.dicom_to_nifti.image.get_origin([(data_set, None)]),
            [1,2,3])

        data_set = odil.DataSet(
            SharedFunctionalGroupsSequence=[odil.DataSet()],
            PerFrameFunctionalGroupsSequence=[
                odil.DataSet(
                    PlanePositionSequence=[
                        odil.DataSet(ImagePositionPatient=[0,0,1])]),
                odil.DataSet(
                    PlanePositionSequence=[
                        odil.DataSet(ImagePositionPatient=[0,0,2])])
            ])
        self.assertSequenceEqual(
            dicomifier.dicom_to_nifti.image.get_origin([(data_set, 1)]),
            [0, 0, 2])

    def test_get_orientation(self):
        data_set = odil.DataSet(ImageOrientationPatient=[1, 0, 0, 0, 1, 0])
        numpy.testing.assert_almost_equal(
            dicomifier.dicom_to_nifti.image.get_orientation([(data_set, None)]),
            numpy.identity(3))

        data_set = odil.DataSet(
            SharedFunctionalGroupsSequence=[odil.DataSet()],
            PerFrameFunctionalGroupsSequence=[
                odil.DataSet(
                    PlaneOrientationSequence=[
                        odil.DataSet(ImageOrientationPatient=[1,0,0,0,0,1])]),
                odil.DataSet(
                    PlaneOrientationSequence=[
                        odil.DataSet(ImageOrientationPatient=[1,0,0,0,1,0])])
            ]
        )
        numpy.testing.assert_almost_equal(
            dicomifier.dicom_to_nifti.image.get_orientation([(data_set, 1)]),
            numpy.identity(3))

    def test_get_spacing_default_thickness(self):
        data_set = odil.DataSet(PixelSpacing=[1, 2])
        numpy.testing.assert_almost_equal(
            dicomifier.dicom_to_nifti.image.get_spacing([(data_set, None)]),
            [1,2,1])

    def test_get_spacing_spacing_between_slices(self):
        data_set = odil.DataSet(PixelSpacing=[1, 2], SpacingBetweenSlices=[3])
        numpy.testing.assert_almost_equal(
            dicomifier.dicom_to_nifti.image.get_spacing([(data_set, None)]),
            [1,2,3])

    def test_get_spacing_slice_thickness(self):
        data_set = odil.DataSet(PixelSpacing=[1, 2], SliceThickness=[3])
        numpy.testing.assert_almost_equal(
            dicomifier.dicom_to_nifti.image.get_spacing([(data_set, None)]),
            [1,2,3])

    def test_get_spacing_two_frames(self):
        data_set_1 = odil.DataSet(
            PixelSpacing=[1, 2],
            ImageOrientationPatient=[1,0,0,0,1,0],
            ImagePositionPatient=[1,2,3])
        data_set_2 = odil.DataSet(
            PixelSpacing=[1, 2],
            ImageOrientationPatient=[1,0,0,0,1,0],
            ImagePositionPatient=[1,2,0])
        numpy.testing.assert_almost_equal(
            dicomifier.dicom_to_nifti.image.get_spacing(
                [(data_set_1, None), (data_set_2, None)]),
            [1,2,3])

    def test_get_geometry(self):
        data_set = odil.DataSet()
        geometry = dicomifier.dicom_to_nifti.image.get_geometry(
            [(data_set, None)])
        origin, spacing, orientation = geometry
        numpy.testing.assert_almost_equal(origin, [0,0,0])
        numpy.testing.assert_almost_equal(spacing, [1,1,1])
        numpy.testing.assert_almost_equal(orientation, numpy.identity(3))

if __name__ == "__main__":
    unittest.main()
