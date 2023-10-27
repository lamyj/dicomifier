#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

import argparse
import os
import pathlib
import re

import dicomifier
import odil

def setup(subparsers):
    parser = subparsers.add_parser(
        "search", help="Search for DICOM data", 
        description="Search for DICOM data matching the supplied search terms. "
            "Search terms can be specified either as a tag name or tag number, "
            "and may be followed by a value. Value-less search terms match "
            "files where the tag is present, while valued search terms match "
            "elements following the DICOM rules (match any value in the "
            "element, '?' and '*' wildcards for strings).")
    
    parser.add_argument(
        "sources", nargs="+", type=pathlib.Path,
        help="DICOM file, directory or DICOMDIR", metavar="source")
    parser.add_argument(
        "--match", "-m", action="append", default=[], type=SearchTerm, 
        dest="search_terms", metavar="search_term", help="Search criteria")
    parser.add_argument(
        "--pipe", "-p", action="store_true", dest="use_pipe",
        help="Format data to be sent to dicomifier to-nifti")
    
    return parser

class SearchTerm:
    def __init__(self, argument):
        items = argument.split("=", 2)
        if items[0] in dir(odil.registry):
            self.tag = getattr(odil.registry, items[0])
        else:
            try:
                tag = int(items[0], 16)
            except ValueError:
                raise argparse.ArgumentTypeError(
                    "Invalid DICOM tag '{}'".format(items[0]))
            else:
                self.tag = odil.Tag(tag)
        
        if len(items) == 2:
            self.value = items[1]
            self.int_value = None
            self.float_value = None
            self.pattern = None
        else:
            self.value = None
    
    def match(self, data_set):
        try:
            result = False
            if self.tag in data_set:
                element = list(data_set[self.tag])
                if self.value is None:
                    result = len(element) != 0
                elif isinstance(element[0], int):
                    if self.int_value is None:
                        self.int_value = int(self.value)
                    result = self.int_value in element
                elif isinstance(element[0], float):
                    if self.float_value is None:
                        self.float_value = int(self.float_value)
                    result = self.float_value in element
                elif isinstance(element[0], bytes):
                    if self.pattern is None:
                        self.pattern = self.value.replace("*", ".*")
                        self.pattern = self.pattern.replace("?", ".")
                        self.pattern = re.compile(self.pattern.encode())
                    
                    result = any(self.pattern.search(x) for x in element)
        except Exception as e:
            dicomifier.logger.info(e)
        return result
        
def action(sources, search_terms, use_pipe):
    max_tag = max(x.tag for x in search_terms)
    halt_condition = lambda x: x>max_tag
    
    matches = []
    for source in sorted(sources):
        files = list_dicom(source)
        for file in sorted(files):
            data_set = odil.Reader.read_file(
                file, halt_condition=halt_condition)[1]
            
            is_match = True
            for search_term in search_terms:
                if not search_term.match(data_set):
                    is_match = False
                    break
            if is_match:
                matches.append(file)
    for file in matches:
        print(file, end="\0" if use_pipe else "\n")

def list_dicom(source):
    all_files = []
    for dirpath, dirnames, filenames in os.walk(str(source)):
        dicomdir = [x for x in filenames if x.upper() == "DICOMDIR"]
        if dicomdir:
            files = dicomifier.dicom_to_nifti.io.get_dicomdir_files(
                os.path.join(dirpath, dicomdir[0]))
            # Don't recurse
            dirnames[:] = []
        else:
            files = [os.path.join(dirpath, file_) for file_ in filenames]
        all_files.extend(files)
    return all_files
