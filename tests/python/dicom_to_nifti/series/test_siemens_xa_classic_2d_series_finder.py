import unittest

import numpy
import odil

import dicomifier

class TestSiemensXAClassic2DSeriesFinder(unittest.TestCase):
    def test_regular_data_set(self):
        data_set = odil.DataSet(SeriesInstanceUID=["1.2.3.4"])

        finder = dicomifier.dicom_to_nifti.series.SiemensXAClassic2DSeriesFinder()
        series_instance_uid = finder(data_set)

        self.assertEqual(series_instance_uid, None)
        self.assertEqual(finder.series_instance_uid, None)
        self.assertEqual(hash(finder), hash(None))

    def test_xa_data_set(self):
        data_set = odil.DataSet(
            ImageType=["ORIGINAL","PRIMARY","DIFFUSION","NONE","ND","MFSPLIT"],
            RelatedSeriesSequence=[odil.DataSet(
                SeriesInstanceUID=["5.6.7.8"],
                PurposeOfReferenceCodeSequence=[odil.DataSet(
                    CodingSchemeDesignator=["DCM"],
                    CodeValue=["121326"]
                )]
            )],
            SoftwareVersions=["syngo MR XA11"],
            SeriesInstanceUID=["1.2.3.4"])

        finder = dicomifier.dicom_to_nifti.series.SiemensXAClassic2DSeriesFinder()
        series_instance_uid = finder(data_set)

        self.assertEqual(series_instance_uid, b"5.6.7.8")
        self.assertEqual(finder.series_instance_uid, b"5.6.7.8")
        self.assertEqual(hash(finder), hash("5.6.7.8"))

if __name__ == "__main__":
    unittest.main()
