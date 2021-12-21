from __future__ import print_function

import base64
import json
import os
import shutil
import subprocess
import sys
import tempfile

import nibabel
import numpy

import diff

def main():
    root = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "data"))
    input_ = os.path.join(root, "baseline")
    baseline = os.path.join(root, "baseline")
    
    inputs = [
        "20160718_115906_plateforme_fantome_nouille_other_1_7",
        "20171114_094354_Plateforme_R17_06_1_2", 
        "20180818_175759_Rope_ChosenOne_1_2",
        "lb_140721.Bq1", 
        "lb_140721.Bx1"
    ]
    
    tests = []
    for path in inputs:
        for suffix in ["", ".multi"]:
            tests.append([
                os.path.join(baseline, "{}.dcm{}".format(path, suffix)),
                os.path.join(baseline, "{}.nii{}".format(path, suffix))])
    
    different = False
    for case_input, case_baseline in tests:
        print("Checking {}".format(case_baseline))
        
        case_output = tempfile.mkdtemp()
        try:
            try:
                subprocess.check_call([
                    "dicomifier", 
                    # "-v", "debug", 
                    "to-nifti", 
                    case_input, case_output])
            except subprocess.CalledProcessError as e:
                return 1
            
            different = different or diff_directories(case_baseline, case_output)
        finally:
            shutil.rmtree(case_output)
    
    if different:
        return 1
    else:
        return 0
        
def diff_directories(baseline, test):
    different = False
    
    for pathname, dirnames, filenames in os.walk(baseline):
        relative_pathname = pathname[len(os.path.join(baseline, "")):]
        test_pathname = os.path.join(test, relative_pathname)
        for filename in filenames:
            baseline_filename = os.path.join(pathname, filename)
            test_filename = os.path.join(test_pathname, filename)
            relative_filename = os.path.join(relative_pathname, filename)
            
            if not os.path.isfile(os.path.join(test_pathname, filename)):
                print("{} missing in test".format(relative_filename))
            else:
                if filename.endswith(".json"):
                    meta_data = [
                        json.load(open(baseline_filename)), 
                        json.load(open(test_filename))]
                    # Process EncapsulatedDocument separately
                    differences = diff.diff(
                        *meta_data, exclusions=["EncapsulatedDocument"])
                    if differences:
                        different = True
                        print(
                            "Meta-data differences in {}".format(
                                relative_filename))
                        diff.print_differences(differences, 1)
                    
                    encapsulated_documents = [
                        [
                            json.loads(base64.b64decode(x).strip(b"\x00").decode()) 
                            for x in m.get("EncapsulatedDocument", [])]
                        for m in meta_data]
                    for documents in zip(*encapsulated_documents):
                        differences = diff.diff(*documents)
                        if differences:
                            different = True
                            print(
                                "Encapsulated document differences in {}".format(
                                    relative_filename))
                            diff.print_differences(differences, 1)
                elif filename.endswith(".nii") or filename.endswith(".nii.gz"):
                    images = [
                        nibabel.load(x)
                        for x in [baseline_filename, test_filename]]
                    meta_data = [
                        [x.affine.shape, x.affine.ravel().tolist(), x.shape] 
                        for x in images]
                    differences = diff.diff(*meta_data)
                    if differences:
                        different = True
                        print(
                            "Geometry differences in {}".format(
                                relative_filename))
                        diff.print_differences(differences, 1)
                    pixel_data = [numpy.asanyarray(x.dataobj) for x in images]
                    if not numpy.allclose(*pixel_data):
                        different = True
                        print(
                            "Pixel data differences in {}".format(
                                relative_filename))
                else:
                    try:
                        subprocess.check_output(
                            ["diff", baseline_filename, test_filename],
                            stderr=subprocess.STDOUT)
                    except subprocess.CalledProcessError as e:
                        different = True
                        print("Differences on {}".format(
                            os.path.join(relative_pathname, filename)))
    
    # Walk the test to find files missing in baseline (the difference between 
    # files has already been tested).
    for pathname, dirnames, filenames in os.walk(test):
        relative_pathname = pathname[len(os.path.join(test, "")):]
        baseline_pathname = os.path.join(baseline, relative_pathname)
        for filename in filenames:
            if not os.path.isfile(os.path.join(baseline_pathname, filename)):
                different = True
                print("{} missing in baseline".format(
                    os.path.join(relative_pathname, filename)))
    
    return different

if __name__ == "__main__":
    sys.exit(main())
