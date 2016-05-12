from __future__ import print_function
import itertools

import numpy
import odil

import meta_data
import image

def convert(dicom_data_sets, dtype, pretty_print=False):
    nifti_data = []
    
    stacks = get_stacks(dicom_data_sets)
    for key, data_sets in stacks.items():
        sort(data_sets)
        
        nifti_image = image.get_nifti_image(data_sets, dtype)
        nifti_meta_data = meta_data.get_nifti_meta_data(data_sets, key)
        
        nifti_data.append((nifti_image, nifti_meta_data))
    
    return nifti_data

def get_stacks(data_sets):
    splitters = _get_splitters(data_sets)
    
    stacks = {}
    for data_set in data_sets:
        key = []
        for tag, getter in splitters:
            tag = str(tag)
            value = getter(data_set, tag)
            
            key.append((tag, value))
        stacks.setdefault(tuple(key), []).append(data_set)
    
    return stacks

def sort(data_sets):
    getter = OrientationGetter()
    orientations = set(
        getter(data_set, str(odil.registry.ImageOrientationPatient))
        for data_set in data_sets
    )
    if len(orientations)>1:
        raise Exception("Cannot sort data sets with non-uniform orientation")
    
    orientation = orientations.pop()
    normal = numpy.cross(*numpy.reshape(orientation, (2, -1)))
    
    data_sets.sort(
        key=lambda x: numpy.dot(
            x[str(odil.registry.ImagePositionPatient)]["Value"], normal))

def _get_splitters(data_sets):
    splitters = {
        "ALL": [
            (odil.registry.SeriesInstanceUID, _default_getter),
            (odil.registry.ImageOrientationPatient, OrientationGetter()),
            (odil.registry.SpacingBetweenSlices, _default_getter),
        ],
        odil.registry.MRImageStorage: [
            (odil.registry.RepetitionTime, _default_getter),
            (odil.registry.EchoTime, _default_getter),
            (odil.registry.InversionTime, _default_getter),
        ],
    }
    
    sop_classes = set(
        x[str(odil.registry.SOPClassUID)]["Value"][0] 
        for x in data_sets
    )
    
    return list(itertools.chain(
        splitters["ALL"], 
        *[splitters[x] for x in sop_classes]
    ))

def _default_getter(data_set, tag):
    # List is not hashable, use tuple instead
    result = None
    if tag in data_set and "Value" in data_set[tag]:
        result = tuple(data_set[tag]["Value"])
    return result

class OrientationGetter(object):
    def __init__(self):
        self._orientations = {}

    def __call__(self, data_set, tag):
        value = _default_getter(data_set, tag)
        orientation = numpy.reshape(value, (2, -1))
        normal = numpy.cross(*orientation)
        
        closest = None
        for candidate in self._orientations.items():
            if OrientationGetter._comparator(normal, candidate[0]):
                closest = candidate[1]
                break
        
        if closest is None:
            self._orientations[tuple(normal)] = value
        else:
            value = closest
        
        return tuple(value)

    @staticmethod
    def _comparator(o1, o2, epsilon=0.05):
        if (o1, o2) == ((), ()) :
            return True
        elif () in (o1, o2) :
            return False
        else :
            return (numpy.linalg.norm(numpy.subtract(o1,o2), numpy.inf) <= epsilon)
