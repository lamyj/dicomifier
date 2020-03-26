import base64
import json
import unittest

import numpy

import dicomifier
import odil

class TestMetaData(unittest.TestCase):
    def test_get_meta_data(self):
        data_set_1 = odil.from_json(json.dumps({
            str(odil.registry.SOPInstanceUID): {
                "vr": "UI", "Value": ["1.2.3.4"]},
            str(odil.registry.EchoTime): {"vr": "DS", "Value": [10]},
            str(odil.registry.RepetitionTime): {"vr": "DS", "Value": [20]}
        }))
        data_set_2 = odil.from_json(json.dumps({
            str(odil.registry.SOPInstanceUID): {
                "vr": "UI", "Value": ["1.2.3.5"]},
            str(odil.registry.EchoTime): {"vr": "DS", "Value": [10]},
            str(odil.registry.RepetitionTime): {"vr": "DS", "Value": [30]}
        }))
        self.assertDictEqual(
            dicomifier.dicom_to_nifti.meta_data.get_meta_data(
                [(data_set_1, None), (data_set_2, None)]
            )._dictionary, {
                "EchoTime": [10],
                "RepetitionTime": [[20], [30]],
            })
    
    def test_get_tag_name(self):
        tag = odil.registry.PatientName
        self.assertEqual(
            dicomifier.dicom_to_nifti.meta_data.get_tag_name(tag), 
            tag.get_name())
        
        tag = odil.Tag(0x2345, 0x6789)
        self.assertEqual(
            dicomifier.dicom_to_nifti.meta_data.get_tag_name(tag), 
            "23456789")
    
    def test_convert_element(self):
        element = odil.Element(odil.VR.UN)
        self.assertEqual(
            dicomifier.dicom_to_nifti.meta_data.convert_element(element, []), 
            None)
        
        element = odil.Element([1, 2], odil.VR.UN)
        self.assertEqual(
            dicomifier.dicom_to_nifti.meta_data.convert_element(element, []), 
            [1, 2])
        
        element = odil.Element([1.2, 3.4], odil.VR.UN)
        self.assertEqual(
            dicomifier.dicom_to_nifti.meta_data.convert_element(element, []), 
            [1.2, 3.4])
        
        element = odil.Element([b"FOO"], odil.VR.CS)
        self.assertEqual(
            dicomifier.dicom_to_nifti.meta_data.convert_element(
                element, odil.Value.Strings()), 
            ["FOO"])
        
        # Note : \x03\x91 corresponds to greek's Aplha Capital letter
        element = odil.Element([b"\x03\x91"], odil.VR.PN)
        self.assertEqual(
            dicomifier.dicom_to_nifti.meta_data.convert_element(
                element, ["ISO_IR 126"]), 
            [{u"Alphabetic" : u"\x03\x91"}])
        
        element = odil.Element(
            [odil.Value.BinaryItem(b"\01\x02\x03\x04")], odil.VR.OB)
        self.assertEqual(
            dicomifier.dicom_to_nifti.meta_data.convert_element(element, []), 
            [base64.b64encode(b"\01\x02\x03\x04").decode()])
        
        data_set = odil.DataSet()
        data_set.add(odil.registry.ImageType, ["FOO"])
        element = odil.Element([data_set], odil.VR.SQ)
        self.assertEqual(
            dicomifier.dicom_to_nifti.meta_data.convert_element(
                element, odil.Value.Strings()), 
            [{"ImageType": ["FOO"]}])

if __name__ == "__main__":
    unittest.main()
