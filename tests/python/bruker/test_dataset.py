import os
import pathlib
import tempfile
import textwrap
import unittest

import dicomifier

class TestDataset(unittest.TestCase):
    def setUp(self):
        fd, self.path = tempfile.mkstemp()
        os.write(fd, textwrap.dedent("""\
            ##FieldName=1 Field Value
            ##$OtherName=( 2, 60 )
            <Other> <Values>
            ##Pi=3.14
            ##$VisuFGOrderDescDim=1
            ##$VisuFGOrderDesc=( 1 )
            (3, <FG_Name>, <FG_Comment>, 0, 2)
            ##$VisuGroupDepVals=( 2 )
            (<Foo>, 0) (<Bar>, 1)""").encode())
        os.close(fd)
    
    def tearDown(self):
        pathlib.Path(self.path).unlink()
        
    def test_empty(self):
        dataset = dicomifier.bruker.Dataset()
        size = 0
        for _ in dataset:
            size += 1
        self.assertEqual(size, 0)
    
    def test_load(self):
        dataset = dicomifier.bruker.Dataset()
        dataset.load(self.path)
        
        fields = []
        for name, value in dataset.items():
            fields.append([name, value])
        self.assertEqual([x[0] for x in fields], [x for x in dataset])
        
        expected_fields = [
            ["FieldName", [], ["1 Field Value"]],
            ["OtherName", [2, 60], ["Other", "Values"]],
            ["Pi", [], [3.14]],
            ["VisuFGOrderDesc", [1], [[3, "FG_Name", "FG_Comment", 0, 2]]],
            ["VisuFGOrderDescDim", [], [1]],
            ["VisuGroupDepVals", [2], [["Foo", 0], ["Bar", 1]]]
        ]
        
        self.assertEqual(len(fields), len(expected_fields))
        
        for field_index, (name, shape, items) in enumerate(expected_fields):
            self.assertTrue(dataset.has_field(name))
            self.assertTrue(name in dataset)
            self.assertEqual(name, fields[field_index][0])
            
            field = dataset.get_field(name)
            self.assertEqual(field.name, name)
            self.assertEqual(field.shape, shape)
            
            self.assertEqual(field, dataset[name])
            
            for index, (item, expected_item) in enumerate(zip(field.value, items)):
                type_info = [
                    ["int", int], ["float", float], ["string", str], 
                    ["struct", list]]
                for typename, type_ in type_info:
                    test = "is_{}".format(typename)
                    getter = "get_{}".format(typename)
                    
                    if getattr(field, test)(index):
                        internal_item = getattr(field, getter)(index)
                        if typename == "struct":
                            internal_item = [x.value for x in internal_item]
                        self.assertIsInstance(internal_item, type_)
                        if isinstance(item, float):
                            self.assertTrue(
                                abs(internal_item-expected_item)/expected_item 
                                < 1e4)
                        else:
                            self.assertEqual(internal_item, expected_item)
                    else:
                        with self.assertRaises(Exception):
                            getattr(field, getter)(index)
                
                self.assertEqual(type(item), type(expected_item))
                
                if isinstance(item, float):
                    self.assertTrue(abs(item-expected_item)/expected_item < 1e4)
                else:
                    self.assertEqual(item, expected_item)
        
        self.assertEqual(dataset.get_used_files(), [self.path])

if __name__ == "__main__":
    unittest.main()
