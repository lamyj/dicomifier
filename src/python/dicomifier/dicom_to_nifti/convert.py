import logging
import itertools

import nifti
import numpy
import odil

import meta_data
import image

from .. import MetaData

def convert(dicom_data_sets, dtype, pretty_print=False):
    nifti_data = []
    
    stacks = get_stacks(dicom_data_sets)
    logging.info(
        "Found {} stack{}".format(len(stacks), "s" if len(stacks)>1 else ""))
    for key, data_sets in stacks.items():
        logging.info(
            "Merging {} data set{}".format(
                len(data_sets), "s" if len(data_sets)>1 else ""))
        sort(data_sets)
        
        nifti_image = image.get_image(data_sets, dtype)
        nifti_meta_data = meta_data.get_meta_data(data_sets, key)
        
        nifti_data.append((nifti_image, nifti_meta_data))
    
    # Try to merge stacks in each series
    merged_stacks = []
    series = {}
    for nitfi_image, nifti_meta_data in nifti_data:
        series.setdefault(nifti_meta_data["SeriesInstanceUID"][0], []).append(
            (nitfi_image, nifti_meta_data))
    for stacks in series.values():
        mergeable = {}
        for nitfi_image, nifti_meta_data in stacks:
            geometry = (
                nitfi_image.qoffset, nifti_image.voxdim, nifti_image.quatern)
            mergeable.setdefault(geometry, []).append(
                (nitfi_image, nifti_meta_data))
        
        for stack in mergeable.values():
            if len(stack)>1:
                logging.info(
                    "{} stack{} can be merged".format(
                        len(stack), "s" if len(stack)>1 else ""))
                merged = merge_images_and_meta_data(stack)
                merged_stacks.append(merged)
            else: 
                merged_stacks.append(stack[0])
    
    return merged_stacks

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

def merge_images_and_meta_data(images_and_meta_data):
    """ Merge the pixel and meta-data of geometrically coherent images.
    """
    
    images = [x[0] for x in images_and_meta_data]
    array = numpy.asarray([x.asarray() for x in images])
    
    merged_image = nifti.NiftiImage(array)
    
    merged_image.setQForm(images[0].getQForm(), images[0].getQFormCode())
    merged_image.setQOffset(images[0].getQOffset(), images[0].getQFormCode())
    merged_image.setVoxDims(images[0].voxdim)
    merged_image.setXYZUnit(images[0].getXYZUnit())
    
    meta_data = [x[1] for x in images_and_meta_data]
    merged_meta_data = MetaData()
    keys = set()
    for m in meta_data:
        keys.update(m.keys())
    for key in keys:
        value = [m.get(key, None) for m in meta_data]
        if all(x == value[0] for x in value):
            value = value[0]
        merged_meta_data[key] = value
    
    return merged_image, merged_meta_data

def _get_splitters(data_sets):
    splitters = {
        "ALL": [
            (odil.registry.SeriesInstanceUID, _default_getter),
            (odil.registry.ImageOrientationPatient, OrientationGetter()),
            (odil.registry.SpacingBetweenSlices, _default_getter),
        ],
        odil.registry.MRImageStorage: [
            (odil.registry.AcquisitionNumber, _default_getter),
            (odil.registry.RepetitionTime, _default_getter),
            (odil.registry.EchoTime, _default_getter),
            (odil.registry.InversionTime, _default_getter),
            (odil.registry.MRDiffusionSequence, _diffusion_getter)
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

def _diffusion_getter(data_set, tag):
    value = _default_getter(data_set, tag)
    if value is not None:
        b_value = _default_getter(value[0], str(odil.registry.DiffusionBValue))
        directionality = value[0][str(odil.registry.DiffusionDirectionality)]["Value"][0]
        sensitization = None
        if directionality == "DIRECTIONAL":
            item = value[0][str(odil.registry.DiffusionGradientDirectionSequence)]["Value"][0]
            sensitization = tuple(item[str(odil.registry.DiffusionGradientOrientation)]["Value"])
        elif directionality == "BMATRIX":
            item = value[0][str(odil.registry.DiffusionBMatrixSequence)]["Value"][0]
            sensitization = tuple([
                item[str(getattr(odil.registry, "DiffusionBValue{}".format(x)))]["Value"][0]
                for x in ["XX", "XY", "XZ", "YY", "YZ", "ZZ"]])
        else:
            raise Exception("Unknown directionality: {}".format(directionality))
        value = (b_value, sensitization)
    return value
