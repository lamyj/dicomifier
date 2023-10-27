#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

import json
import itertools
import pickle
import re

import numpy
import odil

from .. import logger
from . import siemens

def get_stacks(data_sets, extra_splitters=None):
    """ Return the stacks contained in the data sets. The result is a dictionary
        in which the values are pairs of (data_set, frame_index) (in the case
        of single-frame data sets, frame_index is None), and in which the keys
        are tuples of selectors. In this context, a selector is defined as 
        a pair of (group sequence, group, tag) (group sequence and group being
        None for single-frame data sets), and a value.
        
        :param data_sets: list of dicom data sets
        :param extra_splitters: additional splitters to be used when building
            stacks
    """

    splitters = _get_splitters(data_sets)
    if extra_splitters:
        splitters.extend(extra_splitters)
    stacks = {}
    
    def build_selector(
            data_set, getter, group_sequence, group, tag, in_stack_position):
        selector = None
        if getter is get_dimension_index:
            original_getter = getter
            getter = lambda d,t: original_getter(d, t, in_stack_position)
        if group is not None and group in data_set:
            value = getter(data_set[group][0], tag)
        else:
            value = getter(data_set, tag)
        if value is not None:
            selector = ((group_sequence, group, tag), tuple(value))
        return selector
    
    for data_set in data_sets:
        
        frames = []
        in_stack_position = None
        if odil.registry.SharedFunctionalGroupsSequence not in data_set:
            frames.append([(data_set,), None, [None]])
        else:
            in_stack_position = get_in_stack_position_index(data_set)
            
            shared_groups = data_set[odil.registry.SharedFunctionalGroupsSequence][0]
            frames_groups = data_set[odil.registry.PerFrameFunctionalGroupsSequence]
            
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
        key_items.update(x[0] for x in key)
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
    keys = numpy.asarray(list(stacks.keys()), dtype=object)
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
        # NOTE: prefer Image Orientation to In-Stack Position as there is no
        # guarantee that In-Stack Position follows the stack normal.
        if tag == odil.registry.ImageOrientationPatient:
            data_set, frame_idx = frames[0]
            if get_frame_position(data_set, frame_idx) is not None:
                normal = numpy.cross(value[:3], value[3:])
                ordering = lambda x: numpy.dot(get_frame_position(*x), normal)
                break
            else:
                logger.warning(
                    "Orientation found but no position available to sort frames")
            break
        elif tag == odil.registry.DimensionIndexValues:
            # sort by In-Stack Position
            position = []
            for data_set, frame_index in frames:
                position_index = get_in_stack_position_index(data_set)
                frame = data_set[
                    odil.registry.PerFrameFunctionalGroupsSequence][frame_index]
                frame_content = frame[odil.registry.FrameContentSequence][0]
                position.append(
                    frame_content[odil.registry.DimensionIndexValues][position_index])
            
            keydict = dict(zip((id(x) for x in frames), numpy.argsort(position)))
            ordering = lambda x: keydict[id(x)]
    
    if ordering is not None:
        frames.sort(key=ordering)
    else:
        logger.warning(
            "Cannot sort frames for the moment, available tags : {}".format(
                [x[0][2].get_name() for x in key]))

def get_frame_position(data_set, frame_index):
    """ Get the position of the specified frame.
    """

    if odil.registry.PerFrameFunctionalGroupsSequence in data_set:
        frame = data_set[odil.registry.PerFrameFunctionalGroupsSequence][frame_index]
        if odil.registry.PlanePositionSequence in frame:
            plane_position_seq = frame[odil.registry.PlanePositionSequence][0]
        else:
            return None
    else:
        plane_position_seq = data_set
    if odil.registry.ImagePositionPatient not in plane_position_seq:
        return None
    return plane_position_seq[odil.registry.ImagePositionPatient]

def get_in_stack_position_index(data_set):
    """ Return the position of In Stack Position element inside the Dimension
        Index.
    """

    if (
            odil.registry.DimensionIndexSequence in data_set
            and not data_set.empty(odil.registry.DimensionIndexSequence)):
        dimension_indices = data_set[odil.registry.DimensionIndexSequence]
        position = set()
        for i, dimension_index in enumerate(dimension_indices):
            if odil.registry.DimensionIndexPointer in dimension_index:
                idx = dimension_index[odil.registry.DimensionIndexPointer][0]
                if odil.Tag(idx) == odil.registry.InStackPositionNumber:
                    position.add(i)
        if len(position) == 1:
            return list(position)[0]
        else:
            return None
    else:
        return None

class OrientationGetter:
    """ Return the ideal orientation of a data set, i.e. allow small variations
        in the actual orientation.
    """
    
    def __init__(self):
        self._orientations = {}

    def __call__(self, data_set, tag):
        value = data_set.get(tag)
        if value is None:
            return None
        # WARNING: a rotating plane will yield the same normal
        orientation = [value[:3], value[3:]]
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

    value = data_set.get(tag)
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

    value = data_set.get(tag)
    if value is not None:
        b_value = value[0][odil.registry.DiffusionBValue][0]
        directionality = value[0][odil.registry.DiffusionDirectionality][0]
        sensitization = None
        if directionality == b"DIRECTIONAL":
            item = value[0][odil.registry.DiffusionGradientDirectionSequence][0]
            sensitization = tuple(item[odil.registry.DiffusionGradientOrientation])
        elif directionality == b"BMATRIX":
            item = value[0][odil.registry.DiffusionBMatrixSequence][0]
            sensitization = tuple(
                item[getattr(odil.registry, "DiffusionBValue{}".format(x))][0]
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
    
    value = data_set.get(tag)
    if value is None:
        return value
    
    frame_group_index_entries = [
        x for x in value 
        if (
            x[odil.registry.Manufacturer][0] == b"Dicomifier"
            and x[odil.registry.ManufacturerModelName][0] == b"Bruker Frame Group index")]
    if not frame_group_index_entries:
        return None
    elif len(frame_group_index_entries) > 1:
        raise Exception("Multiple Frame Group index entries found")
    
    contribution_description = json.loads(
        frame_group_index_entries[0][
            odil.registry.ContributionDescription][0].decode())
    
    index = tuple(tuple(x) for x in contribution_description)
    return index

def ge_diffusion_getter(data_set, tag):
    """ Return GE-specific diffusion data.
    """
    
    if data_set[odil.registry.Manufacturer][0] != b"GE MEDICAL SYSTEMS":
        return None
    
    # GEMS_ACQU_01 contains directions, GEMS_PARM_01 contains b-value
    gems_acq = _find_private_creator(data_set, b"GEMS_ACQU_01", 0x0019)
    gems_parm = _find_private_creator(data_set, b"GEMS_PARM_01", 0x0043)
    
    direction = None
    if gems_acq is not None:
        direction = tuple(
            data_set.get(odil.Tag(gems_acq+x), [None])[0]
            for x in [0xbb, 0xbc, 0xbd])
    if direction is None or not(isinstance(direction[0], (int, float))):
        return None
    
    # WARNING: this is the *maximal* b-value. The real b-value is determined
    # by the square of the norm of the gradient direction (at on RX29.0).
    # This is still not enough for multiple b=0 in the same series
    maximal_b_value = None
    if gems_parm is not None:
        data_set.get(odil.Tag(gems_parm+0x39), [None])[0]
    if maximal_b_value is None:
        maximal_b_value = data_set.get(odil.registry.DiffusionBValue, [None])[0]
    if not isinstance(maximal_b_value, (int, float)):
        return None
    
    # b-value, rounded to nearest multiple of 5
    b_value = maximal_b_value * numpy.linalg.norm(direction)**2
    b_value = 5 * round(b_value/5)
    
    return direction, b_value

def ge_complex_image_component_getter(data_set, tag):
    """ Return GE-specific Complex Image Component data.
    """
    
    if data_set[odil.registry.Manufacturer][0] != b"GE MEDICAL SYSTEMS":
        return None
    
    gems_parm = _find_private_creator(data_set, b"GEMS_PARM_01", 0x0043)
    if gems_parm is None:
        return None
    content = data_set.get(odil.Tag(gems_parm+0x2f), [None])[0]
    if isinstance(content, odil.Value.BinaryItem):
        content = content.get_memory_view().tobytes()
    return (content, )

def siemens_coil_getter(data_set, tag):
    """ Return Siemens-specific coil identifier.
    """
    
    if data_set[odil.registry.Manufacturer][0] != b"SIEMENS":
        return None
    
    if data_set[odil.registry.Modality][0] != b"MR":
        return None
    
    csa_header = _find_private_creator(data_set, b"SIEMENS CSA HEADER", 0x0029)
    if csa_header is None:
        return None
    
    item = data_set.get(odil.Tag(csa_header + 0x10), [None])[0]
    if item is None:
        return None
    
    siemens_data = siemens.parse_csa(item.get_memory_view().tobytes())
    return siemens_data.get("ImaCoilString", [b""])[0].strip(b"\x00")

def canon_getter(data_set, tag):
    """ Return Canon-specific diffusion information.
    """
    
    if data_set[odil.registry.Manufacturer][0] != b"CANON_MEC":
        return None
    
    if data_set[odil.registry.SOPClassUID][0] != odil.registry.MRImageStorage:
        # NOTE Enhanced MR Image Storage use the standard fields
        return None
    
    if odil.registry.DiffusionBValue not in data_set:
        return None
    b_value_element = data_set[odil.registry.DiffusionBValue][0]
    
    if odil.registry.ImageComments not in data_set:
        if b_value_element != 0:
            logger.debug("No ImageComments, b-value={}".format(b_value_element))
            return None
        else:
            image_comments = b"b=0(0,0,0)"
    else:
        image_comments = data_set[odil.registry.ImageComments][0]
    
        match = re.match(
            br"^b=([\d.]+)\("
                br"(-?[\d.]+),(-?[\d.]+),(-?[\d.]+)"
            br"\)$",
            image_comments)
        if not match:
            logger.debug("ImageComments not matched: '{}'".format(image_comments))
            return None
        
        try:
            b_value_comment, x, y, z = [float(x) for x in match.groups()]
        except ValueError:
            logger.debug(
                "b-value discrepancy: {} != {}".format(
                    b_value_element, b_value_comment))
            return None
        
        if not numpy.isclose(b_value_element, b_value_comment):
            return None
    
    return image_comments

def _get_splitters(data_sets):
    """ Return a list of splitters (tag and getter) depending on the SOPClassUID
        of each dataset

        :param data_sets: Data sets of the current stack 
    """
    
    def default_getter(data_set, tag):
        element = data_set.get(tag)
        if element is not None and element.is_binary():
            # WARNING: random error either with odil wrappers or with 
            # numpy.array when simplifying keys. Fix by pickling the binary
            # DICOM elements.
            element = pickle.dumps(element)
        return element
    
    splitters = {
        "ALL": [
            # Single Frame generic tags
            ((None, odil.registry.SeriesInstanceUID), default_getter),
            ((None, odil.registry.ImageType), default_getter),
            (
                (None, odil.registry.ImageOrientationPatient), 
                OrientationGetter()),
            ((None, odil.registry.SpacingBetweenSlices), default_getter),
            ((None, odil.registry.Rows), default_getter), 
            ((None, odil.registry.Columns), default_getter), 
            # FIXME: PixelSpacing; both X and Y must be close
            ((None, odil.registry.PhotometricInterpretation), default_getter), 
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
                default_getter),
            (
                (
                    odil.registry.FrameContentSequence, 
                    odil.registry.FrameAcquisitionNumber),
                default_getter),
            (
                (odil.registry.FrameContentSequence, odil.registry.FrameLabel),
                default_getter)
        ],
        odil.registry.MRImageStorage: [
            ((None, odil.registry.AcquisitionNumber), default_getter),
            ((None, odil.registry.RepetitionTime), default_getter),
            ((None, odil.registry.EchoTime), default_getter),
            ((None, odil.registry.InversionTime), default_getter),
            ((None, odil.registry.EchoNumbers), default_getter),
            ((None, odil.registry.MRDiffusionSequence), get_diffusion),
            # Philips Ingenia stores these fields at top-level
            ((None, odil.registry.DiffusionGradientOrientation), default_getter),
            ((None, odil.registry.DiffusionBValue), default_getter),
            ((None, odil.registry.TriggerTime), default_getter),
            (
                (None, odil.registry.ContributingEquipmentSequence), 
                frame_group_index_getter)
        ],
        odil.registry.EnhancedMRImageStorage: [
            (
                (
                    odil.registry.MRTimingAndRelatedParametersSequence, 
                    odil.registry.RepetitionTime),
                default_getter),
            (
                (odil.registry.MREchoSequence, odil.registry.EffectiveEchoTime),
                default_getter),
            (
                (odil.registry.MRModifierSequence, odil.registry.InversionTimes),
                default_getter),
            (
                (odil.registry.MRImageFrameTypeSequence, odil.registry.FrameType),
                default_getter),
            (
                (
                    odil.registry.MRMetaboliteMapSequence, 
                    odil.registry.MetaboliteMapDescription),
                default_getter),
            ((None, odil.registry.MRDiffusionSequence), get_diffusion),
        ],
        odil.registry.EnhancedPETImageStorage: [
            (
                (odil.registry.PETFrameTypeSequence, odil.registry.FrameType),
                default_getter)
        ],
        odil.registry.EnhancedCTImageStorage: [
            (
                (odil.registry.CTImageFrameTypeSequence, odil.registry.FrameType),
                default_getter)
        ]
    }

    sop_classes = set(x[odil.registry.SOPClassUID][0] for x in data_sets)

    splitters = list(itertools.chain(
        splitters["ALL"],
        *[splitters.get(x, []) for x in sop_classes]
    ))
    
    if any(d.get(odil.registry.Manufacturer, [None])[0] == b"GE MEDICAL SYSTEMS" for d in data_sets):
        splitters.append(((None, "GE_diffusion"), ge_diffusion_getter))
        splitters.append(((None, "GE_component"), ge_complex_image_component_getter))
    if any(d.get(odil.registry.Manufacturer, [None])[0] == b"SIEMENS" for d in data_sets):
        splitters.append(((None, "Siemens_coil"), siemens_coil_getter))
    if any(d.get(odil.registry.Manufacturer, [None])[0] == b"CANON_MEC" for d in data_sets):
        splitters.append(((None, None), canon_getter))
    
    return splitters

def _find_private_creator(data_set, private_creator, group):
    """ Return the private group (as an integer) corresponding to the given
        private creator and root group, or None.
    """
    
    tag = odil.Tag(group, 0x0000)
    private_group = None
    for element in range(0, 256):
        tag.element = element
        
        # Get the content of the potential private creator. It may be stored as
        # a binary item (e.g. when VR=UN), in that case convert it to a byte
        # string.
        content = data_set.get(tag, [None])[0]
        if isinstance(content, odil.Value.BinaryItem):
            content = content.get_memory_view().tobytes()
        
        if content == private_creator:
            private_group = (group << 16) + (element << 8)
            break
    return private_group
