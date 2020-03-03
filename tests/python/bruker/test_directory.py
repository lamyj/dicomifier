import os
import pathlib
import unittest

import dicomifier

class TestDirectory(unittest.TestCase):
    def setUp(self):
        self.path = pathlib.Path(os.environ["DICOMIFIER_TEST_DATA"])/"bruker"
    
    def test_list_subjects(self):
        actual = dicomifier.bruker.Directory.list_subjects(str(self.path))
        self.assertEqual(actual, [str(self.path)])
    
    def test_get_series_and_reco(self):
        actual = dicomifier.bruker.Directory.get_series_and_reco(str(self.path))
        self.assertEqual(actual, {"1": ["1"]})
    
    def test_load(self):
        directory = dicomifier.bruker.Directory()
        directory.load(str(self.path))
        self.assertTrue(directory.has_dataset("10001"))

    def test_get_dataset(self):
        directory = dicomifier.bruker.Directory()
        directory.load(str(self.path))
        
        dataset = directory.get_dataset("10001")
        self.assertTrue(dataset.has_field("VISU_param"))
    
    def test_get_bad_dataset(self):
        directory = dicomifier.bruker.Directory()
        directory.load(str(self.path))
        with self.assertRaises(Exception):
            directory.get_dataset("90009")
    
    def test_get_used_files(self):
        directory = dicomifier.bruker.Directory()
        directory.load(str(self.path))
    
        actual = directory.get_used_files("10001")
        expected = set([
            str((self.path/"subject").resolve()),
            str((self.path/"1/acqp").resolve()),
            str((self.path/"1/pdata/1/visu_pars").resolve()),
        ])
        self.assertEqual(set(actual), expected)

if __name__ == "__main__":
    unittest.main()
