import unittest

import numpy

import dicomifier
import odil

class TestOdilGetter(unittest.TestCase):
   
    def test_orientation_getter_equal(self):
        d1 = odil.DataSet()
        d1.add("ImageOrientationPatient", [1.,0.,0.,0.,1.,0.])
        d2 = odil.DataSet()
        d2.add("ImageOrientationPatient", [1.,0.,0.,0.,1.,0.])

        orientationGetter = dicomifier.dicom_to_nifti.odil_getter.OrientationGetter()
        orientationGetter(d1, "ImageOrientationPatient")
        orientationGetter(d2, "ImageOrientationPatient")
        orientations = orientationGetter._orientations
        self.assertEqual(1, len(orientations))
        self.assertSequenceEqual(
            list(orientations.values())[0], [1.,0.,0.,0.,1.,0.])

    def test_orientation_getter_slightly_diff(self):
        d1 = odil.DataSet()
        d1.add("ImageOrientationPatient", [1.,0.,0.,0.,1.,0.])
        d2 = odil.DataSet()
        d2.add("ImageOrientationPatient", [1.,0.,0.,0.,1.,0.04])

        orientationGetter = dicomifier.dicom_to_nifti.odil_getter.OrientationGetter()
        orientationGetter(d1, "ImageOrientationPatient")
        second_ori = orientationGetter(d2, "ImageOrientationPatient")
        self.assertEqual(list(second_ori), [1.,0.,0.,0.,1.,0.])
        orientations = orientationGetter._orientations
        self.assertEqual(1, len(orientations))
        self.assertSequenceEqual(
            list(orientations.values())[0], [1.,0.,0.,0.,1.,0.])

    def test_orientation_getter_differents(self):
        d1 = odil.DataSet()
        d1.add("ImageOrientationPatient", [1.,0.,0.,0.,1.,0.])
        d2 = odil.DataSet()
        d2.add("ImageOrientationPatient", [-1.,0.5,0.2,0.,1.,-0.5])

        orientationGetter = dicomifier.dicom_to_nifti.odil_getter.OrientationGetter()
        orientationGetter(d1, "ImageOrientationPatient")
        orientationGetter(d2, "ImageOrientationPatient")
        orientations = orientationGetter._orientations
        self.assertEqual(2, len(orientations))

    def test_orientation_getter_none(self):
        d1 = odil.DataSet()
        orientationGetter = dicomifier.dicom_to_nifti.odil_getter.OrientationGetter()
        ori = orientationGetter(d1, "ImageOrientationPatient")
        self.assertEqual(ori, None)
        orientations = orientationGetter._orientations
        self.assertEqual(0, len(orientations))

if __name__ == "__main__":
    unittest.main()
