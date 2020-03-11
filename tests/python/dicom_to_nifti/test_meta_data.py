import base64
import unittest

import numpy

import dicomifier
import odil

class TestMetaData(unittest.TestCase):

    def test_get_tag_name(self):
        patient_name_tag = odil.Tag("PatientName")
        tag_name = dicomifier.dicom_to_nifti.meta_data.get_tag_name(patient_name_tag)
        self.assertEqual("PatientName", tag_name)

    def test_convert_element_none(self):
        ds = odil.DataSet()
        ds.add("PatientName", [])
        elem = ds["PatientName"]
        res = dicomifier.dicom_to_nifti.meta_data.convert_element(elem, [])
        self.assertEqual(res, None)

    def test_convert_element_int(self):
        ds = odil.DataSet()
        ds.add("InstanceNumber", [10])
        elem = ds["InstanceNumber"]
        res = dicomifier.dicom_to_nifti.meta_data.convert_element(elem, [])
        self.assertEqual(res, [10])

    def test_convert_element_real(self):
        ds = odil.DataSet()
        ds.add("PatientWeight", [92.3])
        elem = ds["PatientWeight"]
        res = dicomifier.dicom_to_nifti.meta_data.convert_element(elem, [])
        self.assertEqual(res, [92.3])

    def test_convert_element_string_without_charset(self):
        # Note : \x03\x91 corresponds to greek's Aplha Capital letter
        ds = odil.DataSet()
        ds.add("PatientName", [b"\x03\x91"])
        elem = ds["PatientName"]
        res = dicomifier.dicom_to_nifti.meta_data.convert_element(
            elem, ["ISO_IR 126"])
        self.assertEqual(res, [{u"Alphabetic" : u"\x03\x91"}])
        
    def test_convert_element_binary(self):
        ds = odil.DataSet()
        pixel_data = [odil.Value.BinaryItem(b"\01\x02\x03\x04")]
        ds.add("PixelData", pixel_data, odil.VR.OB)
        elem = ds["PixelData"]
        res = dicomifier.dicom_to_nifti.meta_data.convert_element(elem, [])
        self.assertEqual(res, [base64.b64encode(b"\01\x02\x03\x04").decode()])

    def test_convert_element_data_set(self):
        ds = odil.DataSet()
        shared = odil.DataSet()
        plane_orientation_seq = odil.DataSet()
        plane_orientation_seq.add("ImageOrientationPatient", [1., 0., 0., 0., 1., 0.])
        shared.add("PlaneOrientationSequence", [plane_orientation_seq])
        ds.add("SharedFunctionalGroupsSequence", [shared])
        elem = ds["SharedFunctionalGroupsSequence"]
        res = dicomifier.dicom_to_nifti.meta_data.convert_element(elem, [])
        wanted_res = {
            "PlaneOrientationSequence" : [
                {"ImageOrientationPatient" : [1., 0., 0., 0., 1., 0.]}
            ]
        }
        self.assertEqual(res, [wanted_res])

    def test_cleanup(self):
        meta_data = {}
        meta_data["InstanceNumber"] = 1
        dicomifier.dicom_to_nifti.meta_data.cleanup(meta_data)
        self.assertEqual(meta_data, {})

    def test_meta_data(self):
        ds = odil.DataSet()
        shared = odil.DataSet()
        plane_orientation_seq = odil.DataSet()
        plane_orientation_seq.add("ImageOrientationPatient", [1., 0., 0., 0., 1., 0.])
        shared.add("PlaneOrientationSequence", [plane_orientation_seq])
        mr_echo_seq = odil.DataSet()
        mr_echo_seq.add("EffectiveEchoTime", [25.])
        shared.add("MREchoSequence", [mr_echo_seq])
        ds.add("SharedFunctionalGroupsSequence", [shared])
        
        per_frame = []
        
        first_frame = odil.DataSet()
        frame_content_seq = odil.DataSet()
        frame_content_seq.add("FrameAcquisitionNumber", [12])
        first_frame.add("FrameContentSequence", [frame_content_seq])
        plane_pos_seq = odil.DataSet()
        plane_pos_seq.add("ImagePositionPatient", [10., -10., 0.])
        first_frame.add("PlanePositionSequence", [plane_pos_seq])
        per_frame.append(first_frame)
        
        second_frame = odil.DataSet()
        frame_content_seq = odil.DataSet()
        frame_content_seq.add("FrameAcquisitionNumber", [23])
        second_frame.add("FrameContentSequence", [frame_content_seq])
        plane_pos_seq = odil.DataSet()
        plane_pos_seq.add("ImagePositionPatient", [10., -10., 1.])
        second_frame.add("PlanePositionSequence", [plane_pos_seq])
        per_frame.append(second_frame)
        
        ds.add("PerFrameFunctionalGroupsSequence", per_frame)
        ds.add("NumberOfFrames", [len(per_frame)])
        ds.add("SOPInstanceUID", ["1.2.826.0.1.3680043.9.5560.999599"])
        data_sets_frame_index = [(ds, 0), (ds, 1)]
        cache = {}
        meta_data = dicomifier.dicom_to_nifti.meta_data.get_meta_data(data_sets_frame_index, cache)
        wanted_meta_data = {
            "EffectiveEchoTime" : [25.],
            "NumberOfFrames" : [2],
            "FrameAcquisitionNumber" : [
                [
                    12
                ],
                [
                    23
                ]
            ]
        }
        self.assertEqual(wanted_meta_data, meta_data._dictionary)

if __name__ == "__main__":
    unittest.main()
