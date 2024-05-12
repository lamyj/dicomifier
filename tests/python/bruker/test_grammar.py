import os
import pathlib
import tempfile
import textwrap
import unittest

import dicomifier

class TestGrammar(unittest.TestCase):
    def test_comment(self):
        data_set = __class__._get_dataset("$$Comment")
        self.assertEqual(len(data_set), 0)
    
    def test_unquoted_string(self):
        data_set = __class__._get_dataset("##FieldName=A few words")
        self.assertEqual(list(data_set.keys()), ["FieldName"])
        self.assertEqual(data_set["FieldName"].value, ["A few words"])
    
    def test_quoted_strings(self):
        data_set = __class__._get_dataset("##FieldName=( 3, 5 )\n<foo> <bar>")
        self.assertEqual(list(data_set.keys()), ["FieldName"])
        self.assertEqual(data_set["FieldName"].value, ["foo", "bar"])
    
    def test_real(self):
        data_set = __class__._get_dataset("##FieldName=1.23")
        self.assertEqual(list(data_set.keys()), ["FieldName"])
        self.assertEqual(data_set["FieldName"].value, [1.23])
    
    def test_not_real(self):
        data_set = __class__._get_dataset("##FieldName=1.23 foo")
        self.assertEqual(list(data_set.keys()), ["FieldName"])
        self.assertEqual(data_set["FieldName"].value, ["1.23 foo"])
    
    def test_reals(self):
        data_set = __class__._get_dataset("##FieldName=( 2 )\n1.23 -4.56")
        self.assertEqual(list(data_set.keys()), ["FieldName"])
        self.assertEqual(data_set["FieldName"].value, [1.23, -4.56])
    
    def test_integer(self):
        data_set = __class__._get_dataset("##FieldName=123")
        self.assertEqual(list(data_set.keys()), ["FieldName"])
        self.assertEqual(data_set["FieldName"].value, [123])
    
    def test_not_integer(self):
        data_set = __class__._get_dataset("##FieldName=123 foo")
        self.assertEqual(list(data_set.keys()), ["FieldName"])
        self.assertEqual(data_set["FieldName"].value, ["123 foo"])
    
    def test_integers(self):
        data_set = __class__._get_dataset("##FieldName=( 2 )\n123 -456")
        self.assertEqual(list(data_set.keys()), ["FieldName"])
        self.assertEqual(data_set["FieldName"].value, [123, -456])
    
    def test_structure(self):
        data_set = __class__._get_dataset("##FieldName=( 1 )\n(3, <Foo>)")
        self.assertEqual(list(data_set.keys()), ["FieldName"])
        self.assertEqual(data_set["FieldName"].value, [[3, "Foo"]])
    
    def test_rle(self):
        data_set = __class__._get_dataset(
            "##FieldName=( 7 )\n12.34 @3*(12) @2*(3.14) 42")
        self.assertEqual(list(data_set.keys()), ["FieldName"])
        self.assertEqual(
            data_set["FieldName"].value, [12.34, *(3*[12]), *(2*[3.14]), 42])
    
    @staticmethod
    def _get_dataset(content):
        with tempfile.TemporaryDirectory() as directory:
            path = os.path.join(directory, "data")
            with open(path, "w") as fd:
                fd.write(content)
            
            data_set = dicomifier.bruker.Dataset()
            data_set.load(path)
        
        return data_set

if __name__ == "__main__":
    unittest.main()
