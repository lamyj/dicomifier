import json
import unittest

import numpy
import odil

import dicomifier

class TestSiemensXAClassic2DSeriesFinder(unittest.TestCase):
    def test_regular_data_set(self):
        data_set = odil.DataSet()
        data_set.add(odil.registry.SeriesInstanceUID, ["1.2.3.4"])
        
        finder = dicomifier.dicom_to_nifti.series.SiemensXAClassic2DSeriesFinder()
        series_instance_uid = finder(data_set)
        
        self.assertEqual(series_instance_uid, None)
        self.assertEqual(finder.series_instance_uid, None)
        self.assertEqual(hash(finder), hash(None))
    
    def test_xa_data_set(self):
        data_set = odil.from_json(json.dumps({
            str(odil.registry.ImageType): {
                "vr": "CS",
                "Value": ["ORIGINAL","PRIMARY","DIFFUSION","NONE","ND","MFSPLIT"]
            },
            str(odil.registry.RelatedSeriesSequence): {
                "vr": "SQ", 
                "Value": [{
                    str(odil.registry.SeriesInstanceUID): {
                        "vr": "UI", "Value": ["5.6.7.8"]},
                    str(odil.registry.PurposeOfReferenceCodeSequence): {
                        "vr": "SQ",
                        "Value": [{
                            str(odil.registry.CodingSchemeDesignator): {
                                "vr": "SH", "Value": ["DCM"]},
                            str(odil.registry.CodeValue): {
                                "vr": "SH", "Value": ["121326"]}
                        }]
                    }   
                }]
            },
            str(odil.registry.SoftwareVersions): {
                "vr": "LO", "Value": ["syngo MR XA11"]},
            str(odil.registry.SeriesInstanceUID): 
                {"vr": "UI", "Value": ["1.2.3.4"]}
        }))
        
        finder = dicomifier.dicom_to_nifti.series.SiemensXAClassic2DSeriesFinder()
        series_instance_uid = finder(data_set)
        
        self.assertEqual(series_instance_uid, b"5.6.7.8")
        self.assertEqual(finder.series_instance_uid, b"5.6.7.8")
        self.assertEqual(hash(finder), hash("5.6.7.8"))

if __name__ == "__main__":
    unittest.main()
