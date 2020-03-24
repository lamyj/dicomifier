#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

import itertools

import numpy
import odil

from . import odil_getter

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
        if getter is odil_getter.get_dimension_index_seq:
            original_getter = getter
            getter = lambda d,t: original_getter(d, t, in_stack_position)
        if group is not None and data_set.has(group):
            value = getter(data_set.as_data_set(group)[0], tag)
        else:
            value = getter(data_set, tag)
        if value is not None:
            selector = ((group_sequence, group, tag), value)
        return selector
    
    for data_set in data_sets:
        
        frames = []
        in_stack_position = None
        if not data_set.has(odil.registry.SharedFunctionalGroupsSequence):
            frames.append([(data_set,), None, [None]])
        else:
            in_stack_position = odil_getter.get_in_stack_position_index(data_set)
            
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
            
            # frames.extend([
            #     [frame_groups, i, odil.registry.PerFrameFunctionalGroupsSequence] 
            #     for i, frame_groups in enumerate(frames_groups)])
        
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
        is_orientation = (
            keys[:,index,:][0][0][2] == odil.registry.ImageOrientationPatient)
        if len(unique_values) > 1 or is_orientation:
            # Key must be kept
            to_keep.append(index)
    stacks = {
        tuple(v for (i, v) in enumerate(stack_key) if i in to_keep): stack_value
        for stack_key, stack_value in stacks.items()
    }
    
    return stacks

def _get_splitters(data_sets):
    """ Return a list of splitters (tag and getter) depending on the SOPClassUID
        of each dataset

        :param data_sets: Data sets of the current stack 
    """

    splitters = {
        "ALL": [
            # Single Frame generic tags
            ((None, odil.registry.SeriesInstanceUID), odil_getter.getter),
            ((None, odil.registry.ImageType), odil_getter.getter),
            (
                (None, odil.registry.ImageOrientationPatient), 
                odil_getter.OrientationGetter()),
            ((None, odil.registry.SpacingBetweenSlices), odil_getter.getter),
            ((None, odil.registry.Rows), odil_getter.getter), 
            ((None, odil.registry.Columns), odil_getter.getter), 
            # FIXME: PixelSpacing; both X and Y must be close
            (
                (None, odil.registry.PhotometricInterpretation), 
                odil_getter.getter), 
            # Multiframe generic tags
            (
                (
                    odil.registry.FrameContentSequence,
                    odil.registry.DimensionIndexValues),
                odil_getter.get_dimension_index_seq),
            (
                (
                    odil.registry.PlaneOrientationSequence, 
                    odil.registry.ImageOrientationPatient),
                odil_getter.OrientationGetter()),
            (
                (
                    odil.registry.PixelMeasuresSequence, 
                    odil.registry.SpacingBetweenSlices),
                odil_getter.getter),
            (
                (
                    odil.registry.FrameContentSequence, 
                    odil.registry.FrameAcquisitionNumber),
                odil_getter.getter),
            (
                (odil.registry.FrameContentSequence, odil.registry.FrameLabel),
                odil_getter.getter)
        ],
        odil.registry.MRImageStorage: [
            ((None, odil.registry.AcquisitionNumber), odil_getter.getter),
            ((None, odil.registry.RepetitionTime), odil_getter.getter),
            ((None, odil.registry.EchoTime), odil_getter.getter),
            ((None, odil.registry.InversionTime), odil_getter.getter),
            ((None, odil.registry.EchoNumbers), odil_getter.getter),
            (
                (None, odil.registry.MRDiffusionSequence), 
                odil_getter.diffusion_getter),
            # Philips Ingenia stores these fields at top-level
            (
                (None, odil.registry.DiffusionGradientOrientation),
                odil_getter.getter),
            ((None, odil.registry.DiffusionBValue), odil_getter.getter),
            ((None, odil.registry.TriggerTime), odil_getter.getter),
            (
                (None, odil.registry.ContributingEquipmentSequence), 
                odil_getter.frame_group_index_getter)
        ],
        odil.registry.EnhancedMRImageStorage: [
            (
                (
                    odil.registry.MRTimingAndRelatedParametersSequence, 
                    odil.registry.RepetitionTime),
                odil_getter.getter),
            (
                (odil.registry.MREchoSequence, odil.registry.EffectiveEchoTime),
                odil_getter.getter),
            (
                (odil.registry.MRModifierSequence, odil.registry.InversionTimes),
                odil_getter.getter),
            (
                (odil.registry.MRImageFrameTypeSequence, odil.registry.FrameType),
                odil_getter.getter),
            (
                (
                    odil.registry.MRMetaboliteMapSequence, 
                    odil.registry.MetaboliteMapDescription),
                odil_getter.getter),
            (
                (None, odil.registry.MRDiffusionSequence),
                odil_getter.diffusion_getter),
        ],
        odil.registry.EnhancedPETImageStorage: [
            (
                (odil.registry.PETFrameTypeSequence, odil.registry.FrameType),
                odil_getter.getter)
        ],
        odil.registry.EnhancedCTImageStorage: [
            (
                (odil.registry.CTImageFrameTypeSequence, odil.registry.FrameType),
                odil_getter.getter)
        ]
    }

    sop_classes = set(
        x.as_string(odil.registry.SOPClassUID)[0] for x in data_sets)

    return list(itertools.chain(
        splitters["ALL"],
        *[splitters.get(x, []) for x in sop_classes]
    ))
