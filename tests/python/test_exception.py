import unittest

import dicomifier

class TestException(unittest.TestCase):
    def test_python_generic(self):
        with self.assertRaises(Exception):
            raise dicomifier.Exception()
    
    def test_python_specific(self):
        with self.assertRaises(dicomifier.Exception):
            raise dicomifier.Exception()

    def test_cpp_generic(self):
        with self.assertRaises(Exception):
            dicomifier.bruker.Directory().get_dataset("foo")
    
    def test_cpp_specific(self):
        with self.assertRaises(dicomifier.Exception):
            dicomifier.bruker.Directory().get_dataset("foo")

if __name__ == "__main__":
    unittest.main()
