import base64
import json
import unittest

import numpy
import odil

import dicomifier

class TestImage(unittest.TestCase):
    def test_get_linear_pixel_data(self):
        buffer = numpy.linspace(1, 11, 10, dtype=numpy.uint16)
        data_set = odil.from_json(json.dumps({
            str(odil.registry.HighBit): {"vr": "US", "Value": [15]},
            str(odil.registry.BitsAllocated): {"vr": "US", "Value": [16]},
            str(odil.registry.PixelData): {
                "vr": "OB", 
                "InlineBinary": base64.b64encode(buffer.tostring()).decode()}
        }))
        numpy.testing.assert_almost_equal(
            dicomifier.dicom_to_nifti.image.get_linear_pixel_data(data_set),
            buffer)
    
    def test_get_shaped_pixel_data(self):
        data_set = odil.from_json(json.dumps({
            str(odil.registry.Rows): {"vr": "US", "Value": [5]},
            str(odil.registry.Columns): {"vr": "US", "Value": [2]},
            str(odil.registry.SamplesPerPixel): {"vr": "US", "Value": [1]},
            str(odil.registry.BitsStored): {"vr": "US", "Value": [16]}
        }))
        buffer = numpy.linspace(1, 11, 10, dtype=numpy.uint16)
        numpy.testing.assert_almost_equal(
            dicomifier.dicom_to_nifti.image.get_shaped_pixel_data(
                data_set, None, buffer),
            buffer.reshape(5,2))
    
    def test_get_origin(self):
        data_set = odil.from_json(json.dumps({
            str(odil.registry.ImagePositionPatient): {"vr": "DS", "Value": [1,2,3]}
        }))
        self.assertSequenceEqual(
            dicomifier.dicom_to_nifti.image.get_origin([(data_set, None)]),
            [1,2,3])
        
        data_set = odil.from_json(json.dumps({
            str(odil.registry.SharedFunctionalGroupsSequence): {
                "vr": "SQ", "Value": [{}]
            },
            str(odil.registry.PerFrameFunctionalGroupsSequence): {
                "vr": "SQ", "Value": [{
                    str(odil.registry.PlanePositionSequence): {
                        "vr": "SQ", "Value": [{
                            str(odil.registry.ImagePositionPatient): {
                                "vr": "DS", "Value": [0,0,1]}
                        }]
                    }
                }, {
                    str(odil.registry.PlanePositionSequence): {
                        "vr": "SQ", "Value": [{
                            str(odil.registry.ImagePositionPatient): {
                                "vr": "DS", "Value": [0,0,2]}
                        }]
                    }
                }]
            }
        }))
        self.assertSequenceEqual(
            dicomifier.dicom_to_nifti.image.get_origin([(data_set, 1)]),
            [0, 0, 2])
    
    def test_get_orientation(self):
        data_set = odil.from_json(json.dumps({
            str(odil.registry.ImageOrientationPatient): {
                "vr": "DS", "Value": [1, 0, 0, 0, 1, 0]}
        }))
        numpy.testing.assert_almost_equal(
            dicomifier.dicom_to_nifti.image.get_orientation([(data_set, None)]),
            numpy.identity(3))
        
        data_set = odil.from_json(json.dumps({
            str(odil.registry.SharedFunctionalGroupsSequence): {
                "vr": "SQ", "Value": [{}]
            },
            str(odil.registry.PerFrameFunctionalGroupsSequence): {
                "vr": "SQ", "Value": [{
                    str(odil.registry.PlaneOrientationSequence): {
                        "vr": "SQ", "Value": [{
                            str(odil.registry.ImageOrientationPatient): {
                                "vr": "DS", "Value": [1,0,0,0,0,1]}
                        }]
                    }
                }, {
                    str(odil.registry.PlaneOrientationSequence): {
                        "vr": "SQ", "Value": [{
                            str(odil.registry.ImageOrientationPatient): {
                                "vr": "DS", "Value": [1,0,0,0,1,0]}
                        }]
                    }
                }]
            }
        }))
        numpy.testing.assert_almost_equal(
            dicomifier.dicom_to_nifti.image.get_orientation([(data_set, 1)]),
            numpy.identity(3))
    
    def test_get_spacing_default_thickness(self):
        data_set = odil.from_json(json.dumps({
            str(odil.registry.PixelSpacing): {
                "vr": "DS", "Value": [1, 2]}
        }))
        numpy.testing.assert_almost_equal(
            dicomifier.dicom_to_nifti.image.get_spacing([(data_set, None)]),
            [1,2,1])
    
    def test_get_spacing_spacing_between_slices(self):
        data_set = odil.from_json(json.dumps({
            str(odil.registry.PixelSpacing): {
                "vr": "DS", "Value": [1, 2]},
            str(odil.registry.SpacingBetweenSlices): {
                "vr": "DS", "Value": [3]}
        }))
        numpy.testing.assert_almost_equal(
            dicomifier.dicom_to_nifti.image.get_spacing([(data_set, None)]),
            [1,2,3])
    
    def test_get_spacing_slice_thickness(self):
        data_set = odil.from_json(json.dumps({
            str(odil.registry.PixelSpacing): {
                "vr": "DS", "Value": [1, 2]},
            str(odil.registry.SliceThickness): {
                "vr": "DS", "Value": [3]}
        }))
        numpy.testing.assert_almost_equal(
            dicomifier.dicom_to_nifti.image.get_spacing([(data_set, None)]),
            [1,2,3])
    
    def test_get_spacing_two_frames(self):
        data_set_1 = odil.from_json(json.dumps({
            str(odil.registry.PixelSpacing): {
                "vr": "DS", "Value": [1, 2]},
            str(odil.registry.ImageOrientationPatient): {
                "vr": "DS", "Value": [1,0,0,0,1,0]},
            str(odil.registry.ImagePositionPatient): {
                "vr": "DS", "Value": [1,2,3]}
        }))
        data_set_2 = odil.from_json(json.dumps({
            str(odil.registry.PixelSpacing): {
                "vr": "DS", "Value": [1, 2]},
            str(odil.registry.ImageOrientationPatient): {
                "vr": "DS", "Value": [1,0,0,0,1,0]},
            str(odil.registry.ImagePositionPatient): {
                "vr": "DS", "Value": [1,2,0]}
        }))
        numpy.testing.assert_almost_equal(
            dicomifier.dicom_to_nifti.image.get_spacing(
                [(data_set_1, None), (data_set_2, None)]),
            [1,2,3])
    
    def test_get_geometry(self):
        data_set = odil.from_json(json.dumps({}))
        geometry = dicomifier.dicom_to_nifti.image.get_geometry(
            [(data_set, None)])
        origin, spacing, orientation = geometry
        numpy.testing.assert_almost_equal(origin, [0,0,0])
        numpy.testing.assert_almost_equal(spacing, [1,1,1])
        numpy.testing.assert_almost_equal(orientation, numpy.identity(3))

if __name__ == "__main__":
    unittest.main()
