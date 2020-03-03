import unittest

import numpy

import dicomifier
import odil

from dicomifier.dicom_to_nifti.convert import *

class TestConvert(unittest.TestCase):
    def test_get_stacks_echo_time(self):
        # Test single frame dataSets
        ds = [odil.DataSet() for x in range(3)]
        ds[0].add("SOPClassUID", [odil.registry.MRImageStorage])
        ds[0].add("EchoTime", [25.])
        ds[0].add("PatientName", ["Pacino^Al"])
        ds[1].add("SOPClassUID", [odil.registry.MRImageStorage])
        ds[1].add("EchoTime", [20.])
        ds[2].add("SOPClassUID", [odil.registry.MRImageStorage])
        ds[2].add("EchoTime", [25.])
        stacks = get_stacks(ds)
        echoTime_tag = str(odil.Tag("EchoTime"))
        wanted_stacks = { 
            (((None, None, echoTime_tag), (25.,)), ) : [(ds[0], None), (ds[2], None)],
            (((None, None, echoTime_tag), (20.,)), ) : [(ds[1], None)]
        }
        self.assertEqual(wanted_stacks, stacks)

    def test_get_stacks_inversion_times(self):
        # Test multiFrame dataSet
        ds = odil.DataSet()
        shared = odil.DataSet()
        per_frame = []
        first_frame = odil.DataSet()
        mr_modifier_seq = odil.DataSet()
        mr_modifier_seq.add("InversionTimes", [300.])
        first_frame.add("MRModifierSequence", [mr_modifier_seq])
        per_frame.append(first_frame)
        second_frame = odil.DataSet()
        mr_modifier_seq.add("InversionTimes", [1000.])
        second_frame.add("MRModifierSequence", [mr_modifier_seq])
        per_frame.append(second_frame)
        third_frame = odil.DataSet()
        mr_modifier_seq.add("InversionTimes", [300.])
        third_frame.add("MRModifierSequence", [mr_modifier_seq])
        per_frame.append(third_frame)
        ds.add("SOPClassUID", [odil.registry.EnhancedMRImageStorage])
        ds.add("PerFrameFunctionalGroupsSequence", per_frame)
        ds.add("SharedFunctionalGroupsSequence", [shared])
        ds.add("NumberOfFrames", [len(per_frame)])
        stacks = get_stacks([ds])
        inversionTimes_tag = str(odil.Tag("InversionTimes"))
        mr_modifier_seq_tag = str(odil.Tag("MRModifierSequence"))
        per_frame_tag = str(odil.Tag("PerFrameFunctionalGroupsSequence"))
        wanted_stacks = {
            (((per_frame_tag, mr_modifier_seq_tag, inversionTimes_tag), (300., )), ) : [(ds, 0), (ds, 2)],
            (((per_frame_tag, mr_modifier_seq_tag, inversionTimes_tag), (1000., )), ) : [(ds, 1)],
        }
        self.assertEqual(wanted_stacks, stacks)

    def test_get_stacks_orientation(self):
        # Test with multi_frame dataSets (one dataSet will have the orientation stored in the
        # shared and the second in the per_frame)
        # This example is only here to show the importance of the tag location (per_frame or shared)
        ds = odil.DataSet()
        ds.add("SOPClassUID", [odil.registry.EnhancedMRImageStorage])
        shared = odil.DataSet()
        plane_ori_seq = odil.DataSet()
        plane_ori_seq.add("ImageOrientationPatient", [1.0, 0.0, 0.0, 0.0, 1.0, 0.0])
        shared.add("PlaneOrientationSequence", [plane_ori_seq])
        per_frame = [odil.DataSet(), odil.DataSet()] # two frames both empty
        ds.add("SharedFunctionalGroupsSequence", [shared])
        ds.add("PerFrameFunctionalGroupsSequence", per_frame)
        ds.add("NumberOfFrames", [len(per_frame)])

        ds2 = odil.DataSet()
        ds2.add("SOPClassUID", [odil.registry.EnhancedMRImageStorage])
        ds2.add("SharedFunctionalGroupsSequence", [odil.DataSet()])
        per_frame = []
        first_frame = odil.DataSet()
        plane_ori_seq = odil.DataSet()
        plane_ori_seq.add("ImageOrientationPatient", [1.0, 0.0, 0.0, 0.0, 1.0, 0.0])
        first_frame.add("PlaneOrientationSequence", [plane_ori_seq])
        per_frame.append(first_frame)
        second_frame = odil.DataSet()
        plane_ori_seq.add("ImageOrientationPatient", [1.0, 0.0, 0.0, 0.0, -1.0, 0.0])
        second_frame.add("PlaneOrientationSequence", [plane_ori_seq])
        per_frame.append(second_frame)
        ds2.add("PerFrameFunctionalGroupsSequence", per_frame)
        ds2.add("NumberOfFrames", [len(per_frame)])
        
        stacks = get_stacks([ds, ds2])
        imageOrientationTag = str(odil.Tag("ImageOrientationPatient"))
        plane_ori_seq_tag = str(odil.Tag("PlaneOrientationSequence"))
        per_frame_tag = str(odil.Tag("PerFrameFunctionalGroupsSequence"))
        shared_tag = str(odil.Tag("SharedFunctionalGroupsSequence"))
        wanted_stacks = {
            (
                ((shared_tag, plane_ori_seq_tag, imageOrientationTag),
                (1.0, 0.0, 0.0, 0.0, 1.0, 0.0)),
            ) : [(ds, 0), (ds, 1) ],
            (
                ((per_frame_tag, plane_ori_seq_tag, imageOrientationTag),
                (1.0, 0.0, 0.0, 0.0, 1.0, 0.0)),
            ) : [(ds2, 0) ],
            (
                ((per_frame_tag, plane_ori_seq_tag, imageOrientationTag),
                (1.0, 0.0, 0.0, 0.0, -1.0, 0.0)),
            ) : [(ds2, 1) ],
        }
        self.assertEqual(stacks, wanted_stacks)

    def test_sort_position_no_position(self):
        ds = odil.DataSet()
        shared = odil.DataSet()
        plane_ori_seq = odil.DataSet()
        plane_ori_seq.add("ImageOrientationPatient", [1.0, 0.0, 0.0, 0.0, 1.0, 0.0])
        shared.add("PlaneOrientationSequence", [plane_ori_seq])
        ds.add("SharedFunctionalGroupsSequence", [shared])
        per_frame = [odil.DataSet(), odil.DataSet()]
        ds.add("PerFrameFunctionalGroupsSequence", per_frame)
        ds.add("NumberOfFrames", [len(per_frame)])
        data_sets_frame_index = [(ds, 0), (ds, 1)]
        sort_return = sort_position(data_sets_frame_index, [1.0, 0.0, 0.0, 0.0, 1.0, 0.0])
        self.assertFalse(sort_return)


    def test_sort_position(self):
        ds = odil.DataSet()
        shared = odil.DataSet()
        plane_ori_seq = odil.DataSet()
        plane_ori_seq.add("ImageOrientationPatient", [1.0, 0.0, 0.0, 0.0, 1.0, 0.0])
        shared.add("PlaneOrientationSequence", [plane_ori_seq])
        ds.add("SharedFunctionalGroupsSequence", [shared])
        per_frame = []
        first_frame = odil.DataSet()
        plane_position_seq = odil.DataSet()
        plane_position_seq.add("ImagePositionPatient", [1., 1., -1.])
        first_frame.add("PlanePositionSequence", [plane_position_seq])
        per_frame.append(first_frame)
        second_frame = odil.DataSet()
        plane_position_seq.add("ImagePositionPatient", [1., 1., -2.])
        second_frame.add("PlanePositionSequence", [plane_position_seq])
        per_frame.append(second_frame)
        ds.add("PerFrameFunctionalGroupsSequence", per_frame)
        ds.add("NumberOfFrames", [len(per_frame)])

        data_sets_frame_index = [(ds, 0), (ds, 1)]
        wanted_order = [(ds, 1), (ds, 0)]
        sort_return = sort_position(data_sets_frame_index, [1.0, 0.0, 0.0, 0.0, 1.0, 0.0])
        self.assertTrue(sort_return)
        self.assertEqual(data_sets_frame_index, wanted_order)

    def test_sort_in_stack_position(self):
        ds = odil.DataSet()
        stack_id_seq = odil.DataSet()
        stack_id_seq.add("DimensionOrganizationUID", ["1.3.6.1.4.1.5962.1.6.5012.1.0.1166546115.14677"])
        stack_id_seq.add("DimensionIndexPointer", ["00209056"])
        stack_id_seq.add("FunctionalGroupPointer", ["00209111"])
        in_stack_seq = odil.DataSet()
        in_stack_seq.add("DimensionOrganizationUID", ["1.3.6.1.4.1.5962.1.6.5012.1.0.1166546115.14677"])
        in_stack_seq.add("DimensionIndexPointer", ["00209057"])
        in_stack_seq.add("FunctionalGroupPointer", ["00209111"])
        ds.add("DimensionIndexSequence", [stack_id_seq, in_stack_seq])
        shared = odil.DataSet()
        ds.add("SharedFunctionalGroupsSequence", [shared])
        per_frame = []
        first_frame = odil.DataSet()
        frame_content_seq = odil.DataSet()
        frame_content_seq.add("DimensionIndexValues", [10, 5]) # StackID , In Stack Pos
        first_frame.add("FrameContentSequence", [frame_content_seq])
        per_frame.append(first_frame)
        second_frame = odil.DataSet()
        frame_content_seq.add("DimensionIndexValues", [10, 4])
        second_frame.add("FrameContentSequence", [frame_content_seq])
        per_frame.append(second_frame)
        third_frame = odil.DataSet()
        frame_content_seq.add("DimensionIndexValues", [10, 6])
        third_frame.add("FrameContentSequence", [frame_content_seq])
        per_frame.append(third_frame)
        ds.add("PerFrameFunctionalGroupsSequence", per_frame)
        ds.add("NumberOfFrames", [len(per_frame)])
        data_sets_frame_index = [(ds, 0), (ds, 1), (ds, 2)]
        wanted_order = [(ds, 1), (ds, 0), (ds, 2)]
        per_frame_tag = str(odil.Tag("PerFrameFunctionalGroupsSequence"))
        frame_content_seq_tag =  str(odil.Tag("FrameContentSequence"))
        dimension_index_values_tag = str(odil.Tag("DimensionIndexValues"))
        #input = key with value = (10,) element of DimensionIndexValue without inStackPosition
        key = (
            (per_frame_tag, frame_content_seq_tag, dimension_index_values_tag),
            (10,)
        )
        sort((key,), data_sets_frame_index)
        print data_sets_frame_index
        self.assertEqual(wanted_order, data_sets_frame_index)

if __name__ == "__main__":
    unittest.main()