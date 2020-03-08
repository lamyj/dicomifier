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
            ##$VisuFGOrderDescDim=1
            ##$VisuFGOrderDesc=( 1 )
            (3, <FG_Name>, <FG_Comment>, 0, 2)
            ##$VisuGroupDepVals=( 2 )
            (<Foo>, 0) (<Bar>, 1)""").encode())
    
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
        for name, value in dataset:
            fields.append([name, value])
        self.assertEqual(len(fields), 5)
        
        expected_fields = [
            ["FieldName", [], ["1 Field Value"]],
            ["OtherName", [2, 60], ["Other", "Values"]],
            ["VisuFGOrderDesc", [1], [[3, "FG_Name", "FG_Comment", 0, 2]]],
            ["VisuFGOrderDescDim", [], [1]],
            ["VisuGroupDepVals", [2], [["Foo", 0], ["Bar", 1]]]
        ]
        for field_index, (name, shape, items) in enumerate(expected_fields):
            self.assertTrue(dataset.has_field(name))
            self.assertTrue(name in dataset)
            self.assertEqual(name, fields[field_index][0])
            
            field = dataset.get_field(name)
            self.assertEqual(field.name, name)
            self.assertEqual(field.shape, shape)
            self.assertEqual(len(field.value), len(items))
            
            self.assertEqual(field, dataset[name])
            
            for index, (item, expected_item) in enumerate(zip(field.value, items)):
                type_info = [
                    ["int", int], ["float", float], ["string", str], 
                    ["struct", list]]
                
                for typename, type in type_info:
                    test = "is_{}".format(typename)
                    getter = "get_{}".format(typename)
                    
                    self.assertEqual(
                        getattr(field, test)(index), 
                        isinstance(expected_item, type))
                    self.assertEqual(
                        getattr(item, test)(), 
                        isinstance(expected_item, type))
                    
                    if getattr(item, test)():
                        value = getattr(field, getter)(index)
                        if typename == "struct":
                            value = [x.value for x in value]
                        self.assertEqual(value, expected_item)
                        
                        value = getattr(item, getter)()
                        if typename == "struct":
                            value = [x.value for x in value]
                        self.assertEqual(value, expected_item)
                    else:
                        with self.assertRaises(Exception):
                            getattr(field, getter)(index)
                        with self.assertRaises(Exception):
                            getattr(item, getter)()
                self.assertEqual(item.value, expected_item)
        
        self.assertEqual(dataset.get_used_files(), [self.path])

if __name__ == "__main__":
    unittest.main()
