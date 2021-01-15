import json
import os
import shutil
import subprocess
import sys
import tempfile

import odil

import diff

def main():
    root = os.path.abspath(
        os.path.join(os.path.dirname(__file__), "..", "data"))
    input_ = os.path.join(root, "input")
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
        for options, suffix in [[[], ".dcm"], [["-m"], ".dcm.multi"]]:
            tests.append([
                options, 
                os.path.join(input_, path), 
                os.path.join(baseline, "{}{}".format(path, suffix))])
    
    different = False
    for arguments, case_input, case_baseline in tests:
        print("Checking {}".format(case_baseline))
        
        case_output = tempfile.mkdtemp()
        try:
            try:
                subprocess.check_call(
                    [
                        "dicomifier", 
                        # "-v", "debug", 
                        "to-dicom", "--dicomdir"]
                    +arguments
                    +[case_input, case_output])
            except subprocess.CalledProcessError as e:
                return 1
            
            different |= diff_directories(case_baseline, case_output)
        finally:
            shutil.rmtree(case_output)
    
    if different:
        return 1
    else:
        return 0

def diff_directories(baseline, test):
    exclusions = [
        str(getattr(odil.registry, x)) for x in [
            "MediaStorageSOPInstanceUID", "SOPInstanceUID", 
            "InstanceCreationDate", "InstanceCreationTime", 
            "SpecificCharacterSet", "ContentDate",
            "ContentTime", "EncapsulatedDocument"]]
    
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
            elif filename == "DICOMDIR":
                different |= check_dicomdir(
                    baseline_filename, test_filename, relative_filename)
            else:
                different |= check_file(
                    baseline_filename, test_filename, 
                    exclusions, relative_filename)
                different |= check_encapsulated_document(
                    baseline_filename, test_filename, relative_filename)
    
    for pathname, dirnames, filenames in os.walk(test):
        relative_pathname = pathname[len(os.path.join(test, "")):]
        baseline_pathname = os.path.join(baseline, relative_pathname)
        for filename in filenames:
            if not os.path.isfile(os.path.join(baseline_pathname, filename)):
                different = True
                print("{} missing in baseline".format(
                    os.path.join(relative_pathname, filename)))
    
    return different

def check_file(baseline, test, exclusions, relative):
    different = False
    
    d1 = odil.Reader.read_file(baseline)
    d2 = odil.Reader.read_file(test)
    
    differences = diff.diff(
        *[json.loads(odil.as_json(x[0])) for x in [d1, d2]], exclusions)
    if differences:
        different = True
        print("Header differences in {}".format(relative))
        diff.print_differences(differences, 1)
    
    differences = diff.diff(
        *[json.loads(odil.as_json(x[1])) for x in [d1, d2]], exclusions)
    if differences:
        different = True
        print("Data set differences in {}".format(relative))
        diff.print_differences(differences, 1)
    
    return different

def check_dicomdir(baseline, test, relative):
    different = False
    
    d1 = odil.Reader.read_file(baseline)
    d2 = odil.Reader.read_file(test)
    
    exclusions = [
        str(getattr(odil.registry, x)) for x in [
            "MediaStorageSOPInstanceUID", "SOPInstanceUID", 
            "SpecificCharacterSet", "DirectoryRecordSequence"]]
    
    differences = diff.diff(
        *[json.loads(odil.as_json(x[0])) for x in [d1, d2]], exclusions)
    if differences:
        different = True
        print("Header differences in {}".format(relative))
        diff.print_differences(differences, 1)
    
    differences = diff.diff(
        *[json.loads(odil.as_json(x[1])) for x in [d1, d2]], exclusions)
    if differences:
        different = True
        print("Data set differences in {}".format(relative))
        diff.print_differences(differences, 1)
        
    tested = [
        "DirectoryRecordType", 
        "PatientName", "PatientID", 
        "StudyDate", "StudyTime", "AccessionNumber", "StudyDescription",
            "StudyInstanceUID", "StudyID",
        "Modality", "SeriesDescription", "SeriesInstanceUID", "SeriesNumber",
        "ReferencedFileID", "ReferencedSOPClassUIDInFile",
            "ReferencedTransferSyntaxUIDInFile", "InstanceNumber"]
    tested = [getattr(odil.registry, x) for x in tested]
    
    sort_keys = [
        "DirectoryRecordType", "PatientName", "PatientID", "StudyInstanceUID",
        "SeriesInstanceUID", "ReferencedFileID"]
    sort_keys = [getattr(odil.registry, x) for x in sort_keys]
    sort_key = lambda r: [list(r[t]) for t in sort_keys if t in r]
    
    records = []
    for data_set in [d1, d2]:
        simplified_records = [
            odil.DataSet(**{
                tag.get_name(): record[tag] for tag in tested if tag in record}) 
            for record in data_set[1]["DirectoryRecordSequence"]]
        simplified_records.sort(key=sort_key)
        simplified_records = [
            json.loads(odil.as_json(r)) for r in simplified_records]
        records.append(simplified_records)
    
    differences = diff.diff(*records)
    if differences:
        different = True
        print("Record differences in {}".format(relative))
        diff.print_differences(differences, 1)
    
    return different

def check_encapsulated_document(baseline, test, relative):
    different = False
    
    # EncapsulatedDocument may contain different binary 
    # representation of the same Bruker data set: process 
    # separately
    baseline_bruker = get_encapsulated_document(baseline)
    test_bruker = get_encapsulated_document(test)
    if any(x is not None for x in [baseline_bruker, test_bruker]):
        differences = diff.diff(baseline_bruker, test_bruker)
        if differences:
            different = True
            print("Encapsulated document differences in {}".format(relative))
            diff.print_differences(differences, 1)
    
    return different

def get_encapsulated_document(path):
    with odil.open(path, "rb") as fd:
        data_set = odil.Reader.read_file(fd)[1]
    if "EncapsulatedDocument" in data_set:
        data = data_set.as_binary(
                "EncapsulatedDocument"
            )[0].get_memory_view().tobytes()
        return json.loads(data.decode().strip("\x00"))
    else:
        return None

if __name__ == "__main__":
    sys.exit(main())
