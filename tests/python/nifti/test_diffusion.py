import io
import json
import textwrap
import unittest

import dicomifier
import numpy

class TestDiffusion(unittest.TestCase):
    def test_from_standard(self):
        data = json.loads(
            """
            {
              "MRDiffusionSequence": [
                [
                  {
                    "DiffusionDirectionality": [ "DIRECTIONAL" ],
                    "DiffusionGradientDirectionSequence": [ { 
                      "DiffusionGradientOrientation": [ 0, 0, 0 ] } ],
                    "DiffusionBValue": [ 0 ]
                  }
                ], [
                  {
                    "DiffusionDirectionality": [ "DIRECTIONAL" ],
                    "DiffusionGradientDirectionSequence": [ {
                      "DiffusionGradientOrientation": [
                        0.06652903112048635, 0.9626102087765988, 0.26259374321800266 ]
                    } ],
                    "DiffusionBValue": [ 1500 ]
                  }
                ], [
                  {
                    "DiffusionDirectionality": [ "DIRECTIONAL" ],
                    "DiffusionGradientDirectionSequence": [ {
                      "DiffusionGradientOrientation": [
                        0.14141032124851927, 0.8937442367016847, -0.4257045459082079 ]
                    } ],
                    "DiffusionBValue": [ 1500 ]
                  }
                ]
              ]
            }""")
        scheme = dicomifier.nifti.diffusion.from_standard(data)
        
        numpy.testing.assert_almost_equal(
            [x[0] for x in scheme], 1e6*numpy.asarray([0, 1500, 1500]))
        
        numpy.testing.assert_almost_equal(
            [x[1] for x in scheme],
            [
                [0,                   0,                   0], 
                [0.06652903112048635, 0.9626102087765988,  0.26259374321800266],
                [0.14141032124851927, 0.8937442367016847, -0.4257045459082079]
            ])
    
    def test_to_mrtrix(self):
        scheme = [
            [0, [0,0,0]],
            [1e6, [0,0,1]],
            [1e6, [0,1,0]]]
        stream = io.StringIO()
        dicomifier.nifti.diffusion.to_mrtrix(scheme, stream)
        
        stream.seek(0)
        saved_scheme = numpy.loadtxt(stream)
        expected_scheme = [
            [0, 0, 0, 0],
            [0, 0, 1, 1],
            [0, 1, 0, 1]]
        numpy.testing.assert_almost_equal(saved_scheme, expected_scheme)
    
    def test_to_fsl_positive_determinant(self):
        scheme = [
            [0, [0,0,0]],
            [1e6, [0,0,1]],
            [2e6, [0,1,0]],
            [3e6, [-1,0,0]]]
        transform = numpy.array([
            [0, 1, 0],
            [0, 0, 1],
            [1, 0, 0]], dtype=float)
        
        bvecs_stream = io.StringIO()
        bvals_stream = io.StringIO()
        dicomifier.nifti.diffusion.to_fsl(
            scheme, transform, bvecs_stream, bvals_stream)
        
        bvecs_stream.seek(0)
        saved_bvecs = numpy.loadtxt(bvecs_stream)
        expected_bvecs = [
            [0, -1, 0, 0],
            [0,  0, 0, -1],
            [0,  0, 1,  0]]
        numpy.testing.assert_almost_equal(saved_bvecs, expected_bvecs)
        
        bvals_stream.seek(0)
        saved_bvals = numpy.loadtxt(bvals_stream)
        expected_bvals = [0, 1, 2, 3]
        numpy.testing.assert_almost_equal(saved_bvals, expected_bvals)
    
    def test_to_fsl_negative_determinant(self):
        scheme = [
            [0, [0,0,0]],
            [1e6, [0,0,1]],
            [2e6, [0,1,0]],
            [3e6, [-1,0,0]]]
        transform = numpy.array([
            [0, -1, 0],
            [0,  0, 1],
            [1,  0, 0]], dtype=float)
        
        bvecs_stream = io.StringIO()
        bvals_stream = io.StringIO()
        dicomifier.nifti.diffusion.to_fsl(
            scheme, transform, bvecs_stream, bvals_stream)
        
        bvecs_stream = io.StringIO()
        bvals_stream = io.StringIO()
        dicomifier.nifti.diffusion.to_fsl(
            scheme, transform, bvecs_stream, bvals_stream)
        
        bvecs_stream.seek(0)
        saved_bvecs = numpy.loadtxt(bvecs_stream)
        expected_bvecs = [
            [0, 1, 0, 0],
            [0, 0, 0, 1],
            [0, 0, 1, 0]]
        numpy.testing.assert_almost_equal(saved_bvecs, expected_bvecs)

if __name__ == "__main__":
    unittest.main()
