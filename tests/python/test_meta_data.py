import unittest

import numpy

import dicomifier

class TestMetaData(unittest.TestCase):
    def test_constructor(self):
        meta_data = dicomifier.MetaData({"Name": ["value"]})
        self.assertEqual(len(meta_data), 1)
        self.assertTrue("Name" in meta_data)
        self.assertEqual(meta_data["Name"], ["value"])

    def test_expand_0d(self):
        meta_data = dicomifier.MetaData({"ImageType": ["ORIGINAL", "PRIMARY"]})
        value = meta_data.expand("ImageType", (2, 3))
        self.assertEqual(value.shape, (2, 3, 2))
        self.assertTrue(
            all([all(x == ["ORIGINAL", "PRIMARY"]) for x in value.reshape(-1, 2)])
        )

    def test_expand_1d(self):
        meta_data = dicomifier.MetaData({"EchoTime": [[10], [20]]})
        value = meta_data.expand("EchoTime", (2, 3, 5))
        self.assertEqual(value.shape, (2, 3, 5, 1))
        self.assertTrue(all(x == 10 for x in value[0].ravel()))
        self.assertTrue(all(x == 20 for x in value[1].ravel()))

    def test_expand_2d(self):
        meta_data = dicomifier.MetaData({
            "InstanceNumber": [ [ [1], [2], [3] ], [ [4], [5], [6] ] ]
        })
        value = meta_data.expand("InstanceNumber", (2, 3, 5, 7))
        self.assertEqual(value.shape, (2, 3, 5, 7, 1))
        self.assertTrue(all(x == 1 for x in value[0,0].ravel()))
        self.assertTrue(all(x == 2 for x in value[0,1].ravel()))
        self.assertTrue(all(x == 3 for x in value[0,2].ravel()))
        self.assertTrue(all(x == 4 for x in value[1,0].ravel()))
        self.assertTrue(all(x == 5 for x in value[1,1].ravel()))
        self.assertTrue(all(x == 6 for x in value[1,2].ravel()))

    def test_at(self):
        meta_data = dicomifier.MetaData({"EchoTime": [[10], [20]]})
        # Note that here, only the first dimension is "important" (see at() doc)
        self.assertTrue(all(meta_data.at("EchoTime",[0,0,0]) == [10]))
        self.assertTrue(all(meta_data.at("EchoTime",[1,0]) == [20]))

if __name__ == "__main__":
    unittest.main()
