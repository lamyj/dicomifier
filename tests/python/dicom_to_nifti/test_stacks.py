import json
import unittest

import numpy
import odil

import dicomifier

class TestStacks(unittest.TestCase):
    def test_single_frame_single_stack(self):
        # Same series, different echo time but not MR
        data_set_1 = odil.from_json(json.dumps({
            str(odil.registry.SOPClassUID): {
                "vr": "UI", "Value": [odil.registry.CTImageStorage.decode()]},
            str(odil.registry.EchoTime): {"vr": "DS", "Value": [10]},
            str(odil.registry.SeriesInstanceUID): 
                {"vr": "UI", "Value": ["1.2.3.4"]}
        }))
        data_set_2 = odil.from_json(json.dumps({
            str(odil.registry.SOPClassUID): {
                "vr": "UI", "Value": [odil.registry.CTImageStorage.decode()]},
            str(odil.registry.EchoTime): {"vr": "DS", "Value": [20]},
            str(odil.registry.SeriesInstanceUID): 
                {"vr": "UI", "Value": ["1.2.3.4"]}
        }))
        
        stacks = dicomifier.dicom_to_nifti.stacks.get_stacks(
            [data_set_1, data_set_2])
        self.assertDictEqual(
            stacks, {(): [(data_set_1, None), (data_set_2, None)]})
    
    def test_single_frame_two_stacks(self):
        # Same series, different echo time, MR
        data_set_1 = odil.from_json(json.dumps({
            str(odil.registry.SOPClassUID): {
                "vr": "UI", "Value": [odil.registry.MRImageStorage.decode()]},
            str(odil.registry.EchoTime): {"vr": "DS", "Value": [10]},
            str(odil.registry.SeriesInstanceUID): 
                {"vr": "UI", "Value": ["1.2.3.4"]}
        }))
        data_set_2 = odil.from_json(json.dumps({
            str(odil.registry.SOPClassUID): {
                "vr": "UI", "Value": [odil.registry.MRImageStorage.decode()]},
            str(odil.registry.EchoTime): {"vr": "DS", "Value": [20]},
            str(odil.registry.SeriesInstanceUID): 
                {"vr": "UI", "Value": ["1.2.3.4"]}
        }))
        
        stacks = dicomifier.dicom_to_nifti.stacks.get_stacks(
            [data_set_1, data_set_2])
        self.assertDictEqual(
            stacks, {
                (((None, None, odil.registry.EchoTime), (10.0,)),): [
                    (data_set_1, None)],
                (((None, None, odil.registry.EchoTime), (20.0,)),): [
                    (data_set_2, None)]
            })
    
    def test_multi_frame_single_stack(self):
        # Same series, different echo time but not MR
        data_set = odil.from_json(json.dumps({
            str(odil.registry.SOPClassUID): {
                "vr": "UI", "Value": [odil.registry.EnhancedCTImageStorage.decode()]},
            str(odil.registry.SharedFunctionalGroupsSequence): {
                "vr": "SQ", "Value": [{
                    str(odil.registry.MRImageFrameTypeSequence): { 
                        "vr": "SQ", "Value":[{
                            str(odil.registry.FrameType): {
                                "vr": "CS", "Value": ["ORIGINAL", "PRIMARY"]
                            }
                        }]
                    }
                }]
            },
            str(odil.registry.PerFrameFunctionalGroupsSequence): {
                "vr": "SQ", 
                "Value": [{
                    str(odil.registry.MREchoSequence): {
                        "vr": "SQ", "Value": [{
                            str(odil.registry.EffectiveEchoTime): {
                                "vr": "FD", "Value": [10]
                            }
                        }]
                    }
                }, {
                    str(odil.registry.MREchoSequence): {
                        "vr": "SQ", "Value": [{
                            str(odil.registry.EffectiveEchoTime): {
                                "vr": "FD", "Value": [20]
                            }
                        }]
                    }
                }]
            }
        }))
        
        stacks = dicomifier.dicom_to_nifti.stacks.get_stacks([data_set])
        self.assertDictEqual(stacks, {(): [(data_set, 0), (data_set, 1)]})
    
    def test_multi_frame_two_stacks(self):
        # Same series, different echo time but not MR
        data_set = odil.from_json(json.dumps({
            str(odil.registry.SOPClassUID): {
                "vr": "UI", "Value": [odil.registry.EnhancedMRImageStorage.decode()]},
            str(odil.registry.SharedFunctionalGroupsSequence): {
                "vr": "SQ", "Value": [{
                    str(odil.registry.MRImageFrameTypeSequence): { 
                        "vr": "SQ", "Value":[{
                            str(odil.registry.FrameType): {
                                "vr": "CS", "Value": ["ORIGINAL", "PRIMARY"]
                            }
                        }]
                    }
                }]
            },
            str(odil.registry.PerFrameFunctionalGroupsSequence): {
                "vr": "SQ", 
                "Value": [{
                    str(odil.registry.MREchoSequence): {
                        "vr": "SQ", "Value": [{
                            str(odil.registry.EffectiveEchoTime): {
                                "vr": "FD", "Value": [10]
                            }
                        }]
                    }
                }, {
                    str(odil.registry.MREchoSequence): {
                        "vr": "SQ", "Value": [{
                            str(odil.registry.EffectiveEchoTime): {
                                "vr": "FD", "Value": [20]
                            }
                        }]
                    }
                }]
            }
        }))
        
        stacks = dicomifier.dicom_to_nifti.stacks.get_stacks([data_set])
        selector = (
            odil.registry.PerFrameFunctionalGroupsSequence, 
            odil.registry.MREchoSequence, 
            odil.registry.EffectiveEchoTime)
        self.assertDictEqual(
            stacks, {
                ((selector, (10.0,)),): [(data_set, 0)], 
                ((selector, (20.0,)),): [(data_set, 1)], 
            }
        )
    
    def test_sort_index(self):
        data_set = odil.from_json(json.dumps({
            str(odil.registry.SOPClassUID): {
                "vr": "UI", "Value": [odil.registry.MRImageStorage.decode()]},
            str(odil.registry.DimensionIndexSequence): {
                "vr": "SQ", "Value": [{
                    str(odil.registry.DimensionIndexPointer): {
                        "vr": "AT", "Value": [str(odil.registry.StackID)]
                    }
                }, {
                    str(odil.registry.DimensionIndexPointer): {
                        "vr": "AT", "Value": [str(odil.registry.InStackPositionNumber)]
                    }
                }]
            },
            str(odil.registry.SharedFunctionalGroupsSequence): {
                "vr": "SQ", "Value": [{
                    str(odil.registry.PixelMeasuresSequence): { 
                        "vr": "SQ", "Value":[{
                            str(odil.registry.PixelSpacing): {
                                "vr": "DS", "Value": [1, 1]
                            }
                        }]
                    }
                }]
            },
            str(odil.registry.PerFrameFunctionalGroupsSequence): {
                "vr": "SQ", "Value": [{
                    str(odil.registry.FrameContentSequence): {
                        "vr": "SQ", "Value": [{
                            str(odil.registry.DimensionIndexValues): {
                                "vr": "UL", "Value": [1, 1]}
                        }]
                    }
                }, {
                    str(odil.registry.FrameContentSequence): {
                        "vr": "SQ", "Value": [{
                            str(odil.registry.DimensionIndexValues): {
                                "vr": "UL", "Value": [1, 3]}
                        }]
                    }
                },
                {
                    str(odil.registry.FrameContentSequence): {
                        "vr": "SQ", "Value": [{
                            str(odil.registry.DimensionIndexValues): {
                                "vr": "UL", "Value": [1, 2]}
                        }]
                    }
                }]
            }
        }))
        
        stacks = dicomifier.dicom_to_nifti.stacks.get_stacks([data_set])
        stack = next(iter(stacks.items()))
        dicomifier.dicom_to_nifti.stacks.sort(*stack)
        
        self.assertSequenceEqual(
            stack, (
                ((
                    (
                        odil.registry.PerFrameFunctionalGroupsSequence, 
                        odil.registry.FrameContentSequence, 
                        odil.registry.DimensionIndexValues), 
                    (1, )),),
                [(data_set, 0), (data_set, 2), (data_set, 1)]
            )
        )
    
    def test_sort_position(self):
        data_set_1 = odil.from_json(json.dumps({
            str(odil.registry.SOPClassUID): {
                "vr": "UI", "Value": [odil.registry.MRImageStorage.decode()]},
            str(odil.registry.SeriesInstanceUID): 
                {"vr": "UI", "Value": ["1.2.3.4"]},
            str(odil.registry.ImagePositionPatient): {
                "vr": "DS", "Value": [0,0,2]},
            str(odil.registry.ImageOrientationPatient): {
                "vr": "DS", "Value": [1,0,0,0,1,0]},
        }))
        data_set_2 = odil.from_json(json.dumps({
            str(odil.registry.SOPClassUID): {
                "vr": "UI", "Value": [odil.registry.MRImageStorage.decode()]},
            str(odil.registry.SeriesInstanceUID): 
                {"vr": "UI", "Value": ["1.2.3.4"]},
            str(odil.registry.ImagePositionPatient): {
                "vr": "DS", "Value": [0,0,1]},
            str(odil.registry.ImageOrientationPatient): {
                "vr": "DS", "Value": [1,0,0,0,1,0]},
        }))
        
        stacks = dicomifier.dicom_to_nifti.stacks.get_stacks(
            [data_set_1, data_set_2])
        stack = next(iter(stacks.items()))
        dicomifier.dicom_to_nifti.stacks.sort(*stack)
        
        self.assertSequenceEqual(
            stack, [
                (((None, None, odil.registry.ImageOrientationPatient), (1,0,0,0,1,0)),),
                [(data_set_2, None), (data_set_1, None)]
            ]
        )

    def test_get_frame_position(self):
        data_set = odil.from_json(json.dumps({
            str(odil.registry.ImagePositionPatient): {
                "vr": "DS", "Value": [0,0,1]},
        }))
        
        self.assertSequenceEqual(
            dicomifier.dicom_to_nifti.stacks.get_frame_position(data_set, None),
            [0, 0, 1])
        
        data_set = odil.from_json(json.dumps({
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
            dicomifier.dicom_to_nifti.stacks.get_frame_position(data_set, 1),
            [0, 0, 2])
    
    def test_get_in_stack_position_index(self):
        data_set = odil.from_json(json.dumps({
            str(odil.registry.DimensionIndexSequence): {
                "vr": "SQ", "Value": [{
                    str(odil.registry.DimensionIndexPointer): {
                        "vr": "AT", "Value": [str(odil.registry.StackID)]
                    }
                }, {
                    str(odil.registry.DimensionIndexPointer): {
                        "vr": "AT", "Value": [str(odil.registry.InStackPositionNumber)]
                    }
                }]
            }
        }))
        
        self.assertEqual(
            dicomifier.dicom_to_nifti.stacks.get_in_stack_position_index(data_set),
            1)
    
    def test_orientation_getter(self):
        data_set_1 = odil.from_json(json.dumps({
            str(odil.registry.ImageOrientationPatient): {
                "vr": "DS", "Value": [1, 0, 0, 0, 1, 0]},
        }))
        data_set_2 = odil.from_json(json.dumps({
            str(odil.registry.ImageOrientationPatient): {
                "vr": "DS", "Value": [1, 0, 0, 0, 1, 0.02]},
        }))
        data_set_3 = odil.from_json(json.dumps({
            str(odil.registry.ImageOrientationPatient): {
                "vr": "DS", "Value": [1, 0, 0, 0, 0, 1]},
        }))

        getter = dicomifier.dicom_to_nifti.stacks.OrientationGetter()
        getter(data_set_1, odil.registry.ImageOrientationPatient)
        getter(data_set_2, odil.registry.ImageOrientationPatient)
        orientations = getter.orientations
        self.assertSequenceEqual(
            list(orientations.keys()), [(0, 0, 1)])
        
        getter = dicomifier.dicom_to_nifti.stacks.OrientationGetter()
        getter(data_set_1, odil.registry.ImageOrientationPatient)
        getter(data_set_3, odil.registry.ImageOrientationPatient)
        orientations = getter.orientations
        self.assertSequenceEqual(
            list(orientations.keys()), [(0, 0, 1), (0, -1, 0)])
        
if __name__ == "__main__":
    unittest.main()
