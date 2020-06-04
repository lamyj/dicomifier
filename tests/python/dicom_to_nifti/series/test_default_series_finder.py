import unittest

import numpy
import odil

import dicomifier

class TestDefaultSeriesFinder(unittest.TestCase):
    def test_valid_data_set(self):
        data_set = odil.DataSet(SeriesInstanceUID=["1.2.3.4"])
        
        finder = dicomifier.dicom_to_nifti.series.DefaultSeriesFinder()
        series_instance_uid = finder(data_set)
        
        self.assertEqual(series_instance_uid, b"1.2.3.4")
        self.assertEqual(finder.series_instance_uid, b"1.2.3.4")
        self.assertEqual(hash(finder), hash("1.2.3.4"))
    
    def test_no_series_instance_uid(self):
        data_set = odil.DataSet()
        
        finder = dicomifier.dicom_to_nifti.series.DefaultSeriesFinder()
        series_instance_uid = finder(data_set)
        
        self.assertEqual(series_instance_uid, None)
        self.assertEqual(finder.series_instance_uid, None)
        self.assertEqual(hash(finder), hash(None))
    
    def test_empty_series_instance_uid(self):
        data_set = odil.DataSet(SeriesInstanceUID=[])
        
        finder = dicomifier.dicom_to_nifti.series.DefaultSeriesFinder()
        with self.assertRaises(Exception):
            finder(data_set)
    
    def test_multiple_series_instance_uid(self):
        data_set = odil.DataSet(SeriesInstanceUID=["1", "2"])
        
        finder = dicomifier.dicom_to_nifti.series.DefaultSeriesFinder()
        with self.assertRaises(Exception):
            finder(data_set)

if __name__ == "__main__":
    unittest.main()
