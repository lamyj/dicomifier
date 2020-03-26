#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

import json
import itertools

import numpy
import odil

from . import get_dicom_element
from .. import logger

def get_stacks(data_sets):
    """ Return the stacks contained in the data sets. The result is a dictionary
        in which the values are pairs of (data_set, frame_index) (in the case
        of single-frame data sets, frame_index is None), and in which the keys
        are tuples of selectors. In this context, a selector is defined a 
        a pair of (group sequence, group, tag) (group sequence and group being
        None for single-frame data sets), and a value.
    """

    splitters = _get_splitters(data_sets)
    stacks = {}
    
    def build_selector(
            data_set, getter, group_sequence, group, tag, in_stack_position):
        selector = None
        if getter is get_dimension_index:
            original_getter = getter
            getter = lambda d,t: original_getter(d, t, in_stack_position)
        if group is not None and data_set.has(group):
            value = getter(data_set.as_data_set(group)[0], tag)
        else:
            value = getter(data_set, tag)
        if value is not None:
            selector = ((group_sequence, group, tag), tuple(value))
        return selector
    
    for data_set in data_sets:
        
        frames = []
        in_stack_position = None
        if not data_set.has(odil.registry.SharedFunctionalGroupsSequence):
            frames.append([(data_set,), None, [None]])
        else:
            in_stack_position = get_in_stack_position_index(data_set)
            
            shared_groups = data_set.as_data_set(
                odil.registry.SharedFunctionalGroupsSequence)[0]
            frames_groups = data_set.as_data_set(
                odil.registry.PerFrameFunctionalGroupsSequence)
            
            group_sequences = [
                odil.registry.SharedFunctionalGroupsSequence,
                odil.registry.PerFrameFunctionalGroupsSequence
            ]
            frames.extend([
                [(shared_groups, frame_groups), i, group_sequences] 
                for i, frame_groups in enumerate(frames_groups)])
        
        for frame_infos, frame_index, group_sequences in frames:
            key = []
            for (group, tag), getter in splitters:
                if frame_index is None and group is not None:
                    # Use top-level tags only for single-frame data sets
                    continue
                elif frame_index is not None and group is None:
                    # Use frame group tags only for multi-frame data sets
                    continue
                
                for frame_info, group_sequence in zip(frame_infos, group_sequences):
                    selector = build_selector(
                        frame_info, getter, group_sequence, group, tag,
                        in_stack_position)
                    
                    if selector is not None:
                        key.append(selector)
            
            stacks.setdefault(tuple(key), []).append((data_set, frame_index))
    
    # Normalize the keys so that all stacks have the same key fields
    key_items = set()
    for key in stacks.keys():
        key_items.union(x[0] for x in key)
    normalized_keys = {}
    for key in stacks.keys():
        normalized_keys[key] = list(key)
        for key_item in key_items:
            if key_item not in [x[0] for x in key]:
                normalized_keys[key].append((key_item, None))
    for key, normalized_key in normalized_keys.items():
        normalized_keys[key] = tuple(normalized_key)
    stacks = { normalized_keys[key]: value for key, value in stacks.items() }
    
    # Simplify keys: remove those that have the same value for all stacks
    keys = numpy.asarray(list(stacks.keys())) # stack_id, tag, value
    to_keep = []
    for index in range(keys.shape[1]):
        unique_values = set(keys[:,index,:][:,1])
        # We need to keep these keys as they will be used in the sort() function
        is_sorting_key = keys[:,index,:][0][0][2] in [
            odil.registry.ImageOrientationPatient,
            odil.registry.DimensionIndexValues
        ]
        if len(unique_values) > 1 or is_sorting_key:
            to_keep.append(index)
    stacks = {
        tuple(v for (i, v) in enumerate(stack_key) if i in to_keep): stack_value
        for stack_key, stack_value in stacks.items()
    }
    
    return stacks

def sort(key, frames):
    """ Sort the frames of a stack according to the items present in the 
        stack key.
    """
    
    if len(frames) <= 1:
        return
    
    ordering = None
    for (_, _, tag), value in key:
        if tag == odil.registry.DimensionIndexValues:
            # sort by In-Stack Position
            position = []
            for data_set, frame_index in frames:
                position_index = get_in_stack_position_index(data_set)
                frame = data_set.as_data_set(
                        odil.registry.PerFrameFunctionalGroupsSequence
                    )[frame_index]
                frame_content = frame.as_data_set(
                        odil.registry.FrameContentSequence
                    )[0]
                position.append(
                    frame_content.as_int(
                        odil.registry.DimensionIndexValues
                    )[position_index])
            
            keydict = dict(zip(frames, numpy.argsort(position)))
            ordering = keydict.get
            break
        if tag == odil.registry.ImageOrientationPatient:
            data_set, frame_idx = frames[0]
            if get_frame_position(data_set, frame_idx) is not None:
                normal = numpy.cross(value[:3], value[3:])
                ordering = lambda x: numpy.dot(get_frame_position(*x), normal)
                break
            else:
                logger.warning(
                    "Orientation found but no position available to sort frames")
    
    if ordering is not None:
        frames.sort(key=ordering)
    else:
        logger.warning(
            "Cannot sort frames for the moment, available tags : {}".format(
                [x[0][2].get_name() for x in key]))

def get_frame_position(data_set, frame_index):
    """ Get the position of the specified frame.
    """

    if data_set.has(odil.registry.PerFrameFunctionalGroupsSequence):
        frame = data_set.as_data_set(
            odil.registry.PerFrameFunctionalGroupsSequence)[frame_index]
        if frame.has(odil.registry.PlanePositionSequence):
            plane_position_seq = frame.as_data_set(
                odil.registry.PlanePositionSequence)[0]
        else:
            return None
    else:
        plane_position_seq = data_set
    if not plane_position_seq.has(odil.registry.ImagePositionPatient):
        return None
    return plane_position_seq.as_real(odil.registry.ImagePositionPatient)

def get_in_stack_position_index(data_set):
    """ Return the position of In Stack Position element inside the Dimension
        Index.
    """

    if (
            data_set.has(odil.registry.DimensionIndexSequence)
            and not data_set.empty(odil.registry.DimensionIndexSequence)):
        dimension_indices = data_set.as_data_set(
            odil.registry.DimensionIndexSequence)
        position = set()
        for i, dimension_index in enumerate(dimension_indices):
            if dimension_index.has(odil.registry.DimensionIndexPointer):
                idx = dimension_index.as_string(odil.registry.DimensionIndexPointer)[0]
                if odil.Tag(idx) == odil.registry.InStackPositionNumber:
                    position.add(i)
        if len(position) == 1:
            return list(position)[0]
        else:
            return None
    else:
        return None

class OrientationGetter(object):
    """ Return the ideal orientation of a data set, i.e. allow small variations
        in the actual orientation.
    """
    
    def __init__(self):
        self._orientations = {}

    def __call__(self, data_set, tag):
        value = get_dicom_element(data_set, tag)
        if value is None:
            return None
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
    
    @property
    def orientations(self):
        return self._orientations

    @staticmethod
    def _comparator(o1, o2, epsilon=0.05):
        if numpy.shape(o1) == (0,) and numpy.shape(o2) == (0,):
            return True
        elif any(numpy.shape(x) == (0,) for x in (o1, o2)):
            return False
        else:
            return (
                numpy.linalg.norm(numpy.subtract(o1, o2), numpy.inf) <= epsilon)

def get_dimension_index(data_set, tag, in_stack_position_index):
    """ Return the dimension index pointer without InStackPosition in order to 
        find the different volumes

        :param in_stack_position_index: index of the In Stack Position element 
            within the Dimension Index tuple
    """

    value = get_dicom_element(data_set, tag)
    if value is not None:
        value = list(value)
        if in_stack_position_index is not None:
            del value[in_stack_position_index]
            return tuple(value)
        else:
            raise Exception(
                "Dimension Index Values found but InStackPosition is missing")
    return None

def get_diffusion(data_set, tag):
    """ Get b-value and gradient diffusion from the data_set.
    """

    value = get_dicom_element(data_set, tag)
    if value is not None:
        b_value = tuple(get_dicom_element(value[0], odil.registry.DiffusionBValue))
        directionality = get_dicom_element(
            value[0], odil.registry.DiffusionDirectionality)[0]
        sensitization = None
        if directionality == b"DIRECTIONAL":
            item = get_dicom_element(
                value[0], odil.registry.DiffusionGradientDirectionSequence)[0]
            sensitization = tuple(get_dicom_element(
                item, odil.registry.DiffusionGradientOrientation))
        elif directionality == b"BMATRIX":
            item = get_dicom_element(value[0], odil.registry.DiffusionBMatrixSequence)[0]
            sensitization = tuple(
                get_dicom_element(
                        item, 
                        getattr(odil.registry, "DiffusionBValue{}".format(x))
                    )[0]
                for x in ["XX", "XY", "XZ", "YY", "YZ", "ZZ"])
        elif directionality == b"ISOTROPIC" or directionality == b"NONE":
            return None
        else:
            raise Exception(
                "Unknown directionality: {}".format(directionality))
        value = (b_value, sensitization)
    return value

def frame_group_index_getter(data_set, tag):
    """ Return bruker_to_dicom-specific frame group information.
    """
    
    value = get_dicom_element(data_set, tag)
    if value is None:
        return value
    
    frame_group_index_entries = [
        x for x in value 
        if (
            x.as_string("Manufacturer")[0] == b"Dicomifier"
            and x.as_string("ManufacturerModelName")[0] == b"Bruker Frame Group index")]
    if not frame_group_index_entries:
        return None
    elif len(frame_group_index_entries) > 1:
        raise Exception("Multiple Frame Group index entries found")
    
    contribution_description = json.loads(
        frame_group_index_entries[0].as_string("ContributionDescription")[0].decode())
    
    index = tuple(tuple(x) for x in contribution_description)
    return index


def _get_splitters(data_sets):
    """ Return a list of splitters (tag and getter) depending on the SOPClassUID
        of each dataset

        :param data_sets: Data sets of the current stack 
    """

    splitters = {
        "ALL": [
            # Single Frame generic tags
            ((None, odil.registry.SeriesInstanceUID), get_dicom_element),
            ((None, odil.registry.ImageType), get_dicom_element),
            (
                (None, odil.registry.ImageOrientationPatient), 
                OrientationGetter()),
            ((None, odil.registry.SpacingBetweenSlices), get_dicom_element),
            ((None, odil.registry.Rows), get_dicom_element), 
            ((None, odil.registry.Columns), get_dicom_element), 
            # FIXME: PixelSpacing; both X and Y must be close
            (
                (None, odil.registry.PhotometricInterpretation), 
                get_dicom_element), 
            # Multiframe generic tags
            (
                (
                    odil.registry.FrameContentSequence,
                    odil.registry.DimensionIndexValues),
                get_dimension_index),
            (
                (
                    odil.registry.PlaneOrientationSequence, 
                    odil.registry.ImageOrientationPatient),
                OrientationGetter()),
            (
                (
                    odil.registry.PixelMeasuresSequence, 
                    odil.registry.SpacingBetweenSlices),
                get_dicom_element),
            (
                (
                    odil.registry.FrameContentSequence, 
                    odil.registry.FrameAcquisitionNumber),
                get_dicom_element),
            (
                (odil.registry.FrameContentSequence, odil.registry.FrameLabel),
                get_dicom_element)
        ],
        odil.registry.MRImageStorage: [
            ((None, odil.registry.AcquisitionNumber), get_dicom_element),
            ((None, odil.registry.RepetitionTime), get_dicom_element),
            ((None, odil.registry.EchoTime), get_dicom_element),
            ((None, odil.registry.InversionTime), get_dicom_element),
            ((None, odil.registry.EchoNumbers), get_dicom_element),
            ((None, odil.registry.MRDiffusionSequence), get_diffusion),
            # Philips Ingenia stores these fields at top-level
            (
                (None, odil.registry.DiffusionGradientOrientation),
                get_dicom_element),
            ((None, odil.registry.DiffusionBValue), get_dicom_element),
            ((None, odil.registry.TriggerTime), get_dicom_element),
            (
                (None, odil.registry.ContributingEquipmentSequence), 
                frame_group_index_getter)
        ],
        odil.registry.EnhancedMRImageStorage: [
            (
                (
                    odil.registry.MRTimingAndRelatedParametersSequence, 
                    odil.registry.RepetitionTime),
                get_dicom_element),
            (
                (odil.registry.MREchoSequence, odil.registry.EffectiveEchoTime),
                get_dicom_element),
            (
                (odil.registry.MRModifierSequence, odil.registry.InversionTimes),
                get_dicom_element),
            (
                (odil.registry.MRImageFrameTypeSequence, odil.registry.FrameType),
                get_dicom_element),
            (
                (
                    odil.registry.MRMetaboliteMapSequence, 
                    odil.registry.MetaboliteMapDescription),
                get_dicom_element),
            ((None, odil.registry.MRDiffusionSequence), get_diffusion),
        ],
        odil.registry.EnhancedPETImageStorage: [
            (
                (odil.registry.PETFrameTypeSequence, odil.registry.FrameType),
                get_dicom_element)
        ],
        odil.registry.EnhancedCTImageStorage: [
            (
                (odil.registry.CTImageFrameTypeSequence, odil.registry.FrameType),
                get_dicom_element)
        ]
    }

    sop_classes = set(
        x.as_string(odil.registry.SOPClassUID)[0] for x in data_sets)

    return list(itertools.chain(
        splitters["ALL"],
        *[splitters.get(x, []) for x in sop_classes]
    ))
