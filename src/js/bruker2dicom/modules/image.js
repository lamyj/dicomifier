require('bruker2dicom/common.js');
require('bruker2dicom/functional_groups/pixel_measures.js');
require('bruker2dicom/functional_groups/frame_anatomy.js');
require('bruker2dicom/functional_groups/pixel_value_transformation.js');
require('bruker2dicom/functional_groups/frame_content.js');
require('bruker2dicom/functional_groups/plane_position_patient.js');
require('bruker2dicom/functional_groups/plane_orientation_patient.js');
require('bruker2dicom/functional_groups/mr_image_frame_type.js');
require('bruker2dicom/functional_groups/mr_timing_and_related_parameters.js');
require('bruker2dicom/functional_groups/mr_echo.js');
require('bruker2dicom/functional_groups/mr_modifier.js');
require('bruker2dicom/functional_groups/mr_imaging_modifier.js');
require('bruker2dicom/functional_groups/mr_receive_coil.js');
require('bruker2dicom/functional_groups/mr_transmit_coil.js');
require('bruker2dicom/functional_groups/mr_averages.js');

var _module = namespace('dicomifier.bruker2dicom.modules');

_module.GeneralImage = function(indexGenerator, dicomDataset, brukerDataset) {
    var toDicom = dicomifier.bruker2dicom.toDicom;
    var dateTimeMapper = dicomifier.bruker2dicom.dateTimeMapper;

    dicomDataset[dicomifier.dictionary['InstanceNumber'][1]] = {
        'vr': dicomifier.dictionary['InstanceNumber'][0],
        'Value': [ indexGenerator.currentStep + 1 ] };

    dicomDataset[dicomifier.dictionary['ImageType'][1]] = {
        'vr': dicomifier.dictionary['ImageType'][0],
        'Value': [ 'ORIGINAL', 'PRIMARY' ] };

    toDicom(
        indexGenerator, dicomDataset, 'AcquisitionDate',
        brukerDataset, 'VisuAcqDate', 3, dateTimeMapper('date'));

    toDicom(
        indexGenerator, dicomDataset, 'AcquisitionTime',
        brukerDataset, 'VisuAcqDate', 3, dateTimeMapper('time'));

    toDicom(
        indexGenerator, dicomDataset, 'ImagesInAcquisition',
        brukerDataset, 'VisuCoreFrameCount', 3, parseInt, 
        function(brukerDataset) { 
            if (brukerDataset.VisuCoreDim !== undefined &&
                brukerDataset.VisuCoreDim[0] === "3") {
                return [ parseInt(brukerDataset.VisuCoreFrameCount) * 
                         brukerDataset.VisuCoreSize[2] ]; 
            }
            else { 
                return [ brukerDataset.VisuCoreFrameCount ]; 
            }});

    dicomDataset[dicomifier.dictionary['ImageComments'][1]] = {
        'vr': dicomifier.dictionary['ImageComments'][0] };
};

_module.ImagePlane = function(indexGenerator, dicomDataset, brukerDataset) {
    var toDicom = dicomifier.bruker2dicom.toDicom;

    toDicom(
        indexGenerator, dicomDataset, 'PixelSpacing',
        brukerDataset, null, 1, undefined,
        function(brukerDataset) {
            return brukerDataset.VisuCoreExtent.map(function(x, i) {
                return x/brukerDataset.VisuCoreSize[i]; } ); } );

    toDicom(
        indexGenerator, dicomDataset, 'ImageOrientationPatient',
        brukerDataset, 'VisuCoreOrientation', 1, undefined,
        function(brukerDataset) {
            var orientation = brukerDataset.VisuCoreOrientation;
            var array = [];
            for(var index = 0; index < orientation.length; index += 9) {
                array.push(orientation.slice(index, index + 6));
            }

            var isInFrameGroups = indexGenerator.frameGroups.some(function(x) {
                return x[2].some(function(y) {
                    return (y[0] === 'VisuCoreOrientation');
                });
            });
            if(!isInFrameGroups) {
                // Avoid nested arrays.
                array = array[0];
            }

            return array;
        });

    toDicom(
        indexGenerator, dicomDataset, 'ImagePositionPatient',
        brukerDataset, 'VisuCorePosition', 1, undefined,
        function(brukerDataset) {
            var position = brukerDataset.VisuCorePosition;
            var array = [];
            for(var index = 0; index < position.length; index += 3) {
                array.push(position.slice(index, index + 3));
            }

            var isInFrameGroups = indexGenerator.frameGroups.some(function(x) {
                return x[2].some(function(y) {
                    return (y[0] === 'VisuCoreOrientation');
                });
            });
            if(!isInFrameGroups) {
                // Avoid nested arrays.
                array = array[0];
            }

            return array;
        });

    toDicom(
        indexGenerator, dicomDataset, 'SliceThickness',
        brukerDataset, 'VisuCoreFrameThickness', 2);
};

_module.ImagePixel = function(indexGenerator, dicomDataset, brukerDataset, 
                              pixelData) {
    var toDicom = dicomifier.bruker2dicom.toDicom;

    dicomDataset[dicomifier.dictionary['SamplesPerPixel'][1]] = {
        'vr': dicomifier.dictionary['SamplesPerPixel'][0], 'Value': [ 1 ] };

    dicomDataset[dicomifier.dictionary['PhotometricInterpretation'][1]] = {
        'vr': dicomifier.dictionary['PhotometricInterpretation'][0],
        'Value': [ 'MONOCHROME2' ] };

    toDicom(
        indexGenerator, dicomDataset, 'Rows', brukerDataset,
        'VisuCoreSize', 1, undefined,
        function(brukerDataset) { return [ brukerDataset.VisuCoreSize[0] ]; } );

    toDicom(
        indexGenerator, dicomDataset, 'Columns', brukerDataset,
        'VisuCoreSize', 1, undefined,
        function(brukerDataset) { return [ brukerDataset.VisuCoreSize[1] ]; } );

    dicomDataset[dicomifier.dictionary['BitsAllocated'][1]] = {
        'vr': dicomifier.dictionary['BitsAllocated'][0], 'Value': [ 16 ] };

    dicomDataset[
        dicomifier.dictionary['BitsStored'][1]] = {
        'vr': dicomifier.dictionary['BitsStored'][0], 'Value': [ 16 ] };

    dicomDataset[dicomifier.dictionary['HighBit'][1]] = {
        'vr': dicomifier.dictionary['HighBit'][0], 'Value': [ bigEndian()?0:15 ] };

    dicomDataset[dicomifier.dictionary['PixelRepresentation'][1]] = {
        'vr': dicomifier.dictionary['PixelRepresentation'][0], 'Value': [ 0 ] };

    // Force VR to OW (and not vrAndTag[0] = OB)
    dicomDataset[dicomifier.dictionary['PixelData'][1]] = {
        'vr': 'OW', 'InlineBinary' : pixelData[indexGenerator.currentIndex] };
};

_module.MRImage = function(indexGenerator, dicomDataset, brukerDataset) {
    var toDicom = dicomifier.bruker2dicom.toDicom;

    dicomDataset[dicomifier.dictionary['ScanningSequence'][1]] = {
        'vr': dicomifier.dictionary['ScanningSequence'][0], 'Value': [ 'RM' ] };

    dicomDataset[dicomifier.dictionary['SequenceVariant'][1]] = {
        'vr': dicomifier.dictionary['SequenceVariant'][0], 'Value': [ 'NONE' ] };

    dicomDataset[dicomifier.dictionary['ScanOptions'][1]] = {
        'vr': dicomifier.dictionary['ScanOptions'][0] };

    toDicom(
        indexGenerator, dicomDataset, 'MRAcquisitionType',
        brukerDataset, 'VisuCoreDim', 2, function(x) { return x + 'D'; } );

    toDicom(
        indexGenerator, dicomDataset, 'RepetitionTime',
        brukerDataset, 'VisuAcqRepetitionTime', 2);

    toDicom(
        indexGenerator, dicomDataset, 'EchoTime',
        brukerDataset, 'VisuAcqEchoTime', 2);

    toDicom(
        indexGenerator, dicomDataset, 'EchoTrainLength',
        brukerDataset, 'VisuAcqEchoTrainLength', 2, parseInt);

    toDicom(
        indexGenerator, dicomDataset, 'InversionTime',
        brukerDataset, 'VisuAcqInversionTime', 2);

    toDicom(
        indexGenerator, dicomDataset, 'SequenceName',
        brukerDataset, 'VisuAcqSequenceName', 3);

    toDicom(
        indexGenerator, dicomDataset, 'NumberOfAverages',
        brukerDataset, 'VisuAcqNumberOfAverages', 3, parseFloat);

    toDicom(
        indexGenerator, dicomDataset, 'ImagingFrequency',
        brukerDataset, 'VisuAcqImagingFrequency', 3, parseFloat);

    toDicom(
        indexGenerator, dicomDataset, 'ImagedNucleus',
        brukerDataset, 'VisuAcqImagedNucleus', 3);

    // According to Bruker doc, VisuAcqImagingFrequency is the imaging
    // frequency of 1H, regardless of VisuAcqImagingNucleus
    toDicom(
        indexGenerator, dicomDataset, 'MagneticFieldStrength',
        brukerDataset, 'VisuAcqImagingFrequency', 3,
        function(x) { return parseFloat(x) / 42.577480610; } );

    var spacingBetweenSlices = function(brukerDataset) {
        var positions = brukerDataset.VisuCorePosition;
        var first = positions.slice(0, 3);
        var second =  positions.slice(3, 3);
        var difference = second.map(function(x, i) { return x-first[i]; });

        return difference.reduce(function(v, x) { return v+x*x; }, 0);
    }

    toDicom(
        indexGenerator, dicomDataset, 'SpacingBetweenSlices',
        brukerDataset, null, 3, undefined, spacingBetweenSlices );

    toDicom(
        indexGenerator, dicomDataset, 'NumberOfPhaseEncodingSteps',
        brukerDataset, 'VisuAcqPhaseEncSteps', 3, parseInt);

    toDicom(
        indexGenerator, dicomDataset, 'PixelBandwidth',
        brukerDataset, 'VisuAcqPixelBandwidth', 3, parseFloat);

    // AcquisitionMatrix => optional
    // InPlanePhaseEncodingDirection => optional

    toDicom(
        indexGenerator, dicomDataset, 'FlipAngle', brukerDataset,
        'VisuAcqFlipAngle', 3, parseFloat);
};

_module.SOPCommon = function(indexGenerator, dicomDataset, brukerDataset, SOPClassUID) {
    var toDicom = dicomifier.bruker2dicom.toDicom;
    var dateTimeMapper = dicomifier.bruker2dicom.dateTimeMapper;

    dicomDataset[dicomifier.dictionary['SOPClassUID'][1]] = {
        'vr': dicomifier.dictionary['SOPClassUID'][0],
        'Value': [ SOPClassUID ] };

    dicomDataset[dicomifier.dictionary['SOPInstanceUID'][1]] = {
        'vr': dicomifier.dictionary['SOPInstanceUID'][0],
        'Value': [ dcmGenerateUniqueIdentifier() ] };

    dicomDataset[dicomifier.dictionary['InstanceCreationDate'][1]] = {
        'vr': dicomifier.dictionary['InstanceCreationDate'][0],
        'Value': [ dateTimeMapper('date')(String(new Date())) ] };

    dicomDataset[dicomifier.dictionary['InstanceCreationTime'][1]] = {
        'vr': dicomifier.dictionary['InstanceCreationTime'][0],
        'Value': [ dateTimeMapper('time')(String(new Date())) ] };
};

_module.AcquisitionContext = function(indexGenerator, dicomDataset, brukerDataset) {
    dicomDataset[dicomifier.dictionary['AcquisitionContextSequence'][1]] = {
        'vr': dicomifier.dictionary['AcquisitionContextSequence'][0],
        'Value': [] };
};

_module.EnhancedMRImage = function(indexGenerator, dicomDataset, brukerDataset) {
    var toDicom = dicomifier.bruker2dicom.toDicom;
    var dateTimeMapper = dicomifier.bruker2dicom.dateTimeMapper;
    var dictionaryMapper = dicomifier.bruker2dicom.dictionaryMapper;
    
    toDicom(
        indexGenerator, dicomDataset, 'AcquisitionDateTime',
        brukerDataset, 'VisuAcqDate', 1, dateTimeMapper('datetime'));
    
    toDicom(
        indexGenerator, dicomDataset, 'AcquisitionDuration',
        brukerDataset, 'VisuAcqScanTime', 1, parseFloat);
        
    dicomDataset[dicomifier.dictionary['ContentQualification'][1]] = {
        'vr': dicomifier.dictionary['ContentQualification'][0], 'Value' : ['RESEARCH'] };
        
    toDicom(
        indexGenerator, dicomDataset, 'ResonantNucleus',
        brukerDataset, 'VisuAcqImagedNucleus', 1);
        
    dicomDataset[dicomifier.dictionary['KSpaceFiltering'][1]] = {
        'vr': dicomifier.dictionary['KSpaceFiltering'][0], 'Value' : ['NONE'] };
        
    dicomDataset[dicomifier.dictionary['MagneticFieldStrength'][1]] = {
        'vr': dicomifier.dictionary['MagneticFieldStrength'][0], 'Value' : [ 7 ] }; // TODO
        
    dicomDataset[dicomifier.dictionary['ImageType'][1]] = {
        'vr': dicomifier.dictionary['ImageType'][0],
        'Value': [ 'ORIGINAL', 'PRIMARY' ] };
        
    dicomDataset[dicomifier.dictionary['PixelRepresentation'][1]] = {
        'vr': dicomifier.dictionary['PixelRepresentation'][0], 'Value' : ['MONOCHROME'] };
        
    dicomDataset[dicomifier.dictionary['VolumetricProperties'][1]] = {
        'vr': dicomifier.dictionary['VolumetricProperties'][0], 'Value' : ['VOLUME'] };
        
    dicomDataset[dicomifier.dictionary['VolumeBasedCalculationTechnique'][1]] = {
        'vr': dicomifier.dictionary['VolumeBasedCalculationTechnique'][0], 'Value' : ['NONE'] };
        
    toDicom(
        indexGenerator, dicomDataset, 'ComplexImageComponent',
        brukerDataset, 'VisuCoreFrameType', 1,
        dictionaryMapper({ 'MAGNITUDE_IMAGE': 'MAGNITUDE', 'PHASE_IMAGE': 'PHASE', 
                           'REAL_IMAGE': 'REAL', 'IMAGINARY_IMAGE': 'IMAGINARY', 
                           'MIXED_IMAGE': 'MIXED' }));
                           
    dicomDataset[dicomifier.dictionary['AcquisitionContrast'][1]] = {
        'vr': dicomifier.dictionary['AcquisitionContrast'][0], 'Value' : ['UNKNOWN'] };
    
    dicomDataset[dicomifier.dictionary['SamplesPerPixel'][1]] = {
        'vr': dicomifier.dictionary['SamplesPerPixel'][0], 'Value': [ 1 ] };

    dicomDataset[dicomifier.dictionary['PhotometricInterpretation'][1]] = {
        'vr': dicomifier.dictionary['PhotometricInterpretation'][0],
        'Value': [ 'MONOCHROME2' ] };
        
    dicomDataset[dicomifier.dictionary['BitsAllocated'][1]] = {
        'vr': dicomifier.dictionary['BitsAllocated'][0], 'Value': [ 16 ] };

    dicomDataset[
        dicomifier.dictionary['BitsStored'][1]] = {
        'vr': dicomifier.dictionary['BitsStored'][0], 'Value': [ 16 ] };

    dicomDataset[dicomifier.dictionary['HighBit'][1]] = {
        'vr': dicomifier.dictionary['HighBit'][0], 'Value': [ bigEndian()?0:15 ] };

    dicomDataset[dicomifier.dictionary['PixelRepresentation'][1]] = {
        'vr': dicomifier.dictionary['PixelRepresentation'][0], 'Value': [ 0 ] };
        
    dicomDataset[dicomifier.dictionary['BurnedInAnnotation'][1]] = {
        'vr': dicomifier.dictionary['BurnedInAnnotation'][0], 'Value' : ['NO'] };
        
    dicomDataset[dicomifier.dictionary['LossyImageCompression'][1]] = {
        'vr': dicomifier.dictionary['LossyImageCompression'][0], 'Value' : ['00'] };
        
    dicomDataset[dicomifier.dictionary['PresentationLUTShape'][1]] = {
        'vr': dicomifier.dictionary['PresentationLUTShape'][0], 'Value' : ['IDENTITY'] };
};

_module.MRPulseSequence = function(indexGenerator, dicomDataset, brukerDataset) {
    var toDicom = dicomifier.bruker2dicom.toDicom;
    
    dicomDataset[dicomifier.dictionary['PulseSequenceName'][1]] = {
        'vr': dicomifier.dictionary['PulseSequenceName'][0], 'Value' : ['Default'] };
        
    toDicom(
        indexGenerator, dicomDataset, 'MRAcquisitionType',
        brukerDataset, 'VisuCoreDim', 1, function(x) { return x + 'D'; } );
        
    dicomDataset[dicomifier.dictionary['EchoPulseSequence'][1]] = {
        'vr': dicomifier.dictionary['EchoPulseSequence'][0], 'Value' : ['GRADIENT'] }; // TODO
        
    // if EchoPulseSequence = SPIN or BOTH
    //dicomDataset[dicomifier.dictionary['MultipleSpinEcho'][1]] = {
    //    'vr': dicomifier.dictionary['MultipleSpinEcho'][0], 'Value' : ['NO'] }; // TODO
    
    dicomDataset[dicomifier.dictionary['MultiPlanarExcitation'][1]] = {
        'vr': dicomifier.dictionary['MultiPlanarExcitation'][0], 'Value' : ['NO'] }; // TODO
        
    dicomDataset[dicomifier.dictionary['PhaseContrast'][1]] = {
        'vr': dicomifier.dictionary['PhaseContrast'][0], 'Value' : ['NO'] }; // TODO
        
    dicomDataset[dicomifier.dictionary['TimeOfFlightContrast'][1]] = {
        'vr': dicomifier.dictionary['TimeOfFlightContrast'][0], 'Value' : ['NO'] }; // TODO
        
    dicomDataset[dicomifier.dictionary['SteadyStatePulseSequence'][1]] = {
        'vr': dicomifier.dictionary['SteadyStatePulseSequence'][0], 'Value' : ['NONE'] }; // TODO
        
    dicomDataset[dicomifier.dictionary['EchoPlanarPulseSequence'][1]] = {
        'vr': dicomifier.dictionary['EchoPlanarPulseSequence'][0], 'Value' : ['NO'] }; // TODO
        
    dicomDataset[dicomifier.dictionary['SaturationRecovery'][1]] = {
        'vr': dicomifier.dictionary['SaturationRecovery'][0], 'Value' : ['NO'] }; // TODO
        
    dicomDataset[dicomifier.dictionary['SpectrallySelectedSuppression'][1]] = {
        'vr': dicomifier.dictionary['SpectrallySelectedSuppression'][0], 'Value' : ['NONE'] }; // TODO
        
    dicomDataset[dicomifier.dictionary['OversamplingPhase'][1]] = {
        'vr': dicomifier.dictionary['OversamplingPhase'][0], 'Value' : ['NONE'] }; // TODO
        
    dicomDataset[dicomifier.dictionary['GeometryOfKSpaceTraversal'][1]] = {
        'vr': dicomifier.dictionary['GeometryOfKSpaceTraversal'][0], 'Value' : ['RECTILINEAR'] }; // TODO
        
    dicomDataset[dicomifier.dictionary['RectilinearPhaseEncodeReordering'][1]] = {
        'vr': dicomifier.dictionary['RectilinearPhaseEncodeReordering'][0], 'Value' : ['LINEAR'] }; // TODO
        
    dicomDataset[dicomifier.dictionary['SegmentedKSpaceTraversal'][1]] = {
        'vr': dicomifier.dictionary['SegmentedKSpaceTraversal'][0], 'Value' : ['SINGLE'] }; // TODO
        
    if (dicomDataset[dicomifier.dictionary['MRAcquisitionType'][1]]['Value'][0] === '3D') {
        dicomDataset[dicomifier.dictionary['CoverageOfKSpace'][1]] = {
            'vr': dicomifier.dictionary['CoverageOfKSpace'][0], 'Value' : ['FULL'] }; // TODO
    }
    
    dicomDataset[dicomifier.dictionary['NumberOfKSpaceTrajectories'][1]] = {
        'vr': dicomifier.dictionary['NumberOfKSpaceTrajectories'][0], 'Value' : [0] }; // TODO
};

_module.MultiFrameFunctionalGroups = function(indexGenerator, dicomDataset, 
                                              brukerDataset, rescaleIntercept, 
                                              rescaleSlope) {
    var toDicom = dicomifier.bruker2dicom.toDicom;
    var functionGroups = dicomifier.bruker2dicom.functionalGroups;
    var dateTimeMapper = dicomifier.bruker2dicom.dateTimeMapper;
    
    // Add Shared functional Groups
    // Only a single Item shall be included in this sequence
    var itemShared = {};

    functionGroups.PixelMeasures(indexGenerator, itemShared, brukerDataset);
    functionGroups.FrameAnatomy(indexGenerator, itemShared, brukerDataset);
    functionGroups.PixelValueTransformation(indexGenerator, itemShared, 
                                            brukerDataset, rescaleIntercept, 
                                            rescaleSlope);
    
    dicomDataset[dicomifier.dictionary['SharedFunctionalGroupsSequence'][1]] = {
        'vr': dicomifier.dictionary['SharedFunctionalGroupsSequence'][0], 
        'Value' : [ itemShared ] };
        
    // Add Per Frame functional Groups
    // The number of Items shall be the same as the number of frames 
    // in the Multi-frame image   
    var itemsPerFrame = [];
    
    while(!indexGenerator.done()) {
        var itemFrame = {};
        
        functionGroups.FrameContent(indexGenerator, itemFrame, brukerDataset);
        functionGroups.PlanePositionPatient(indexGenerator, itemFrame, brukerDataset);
        functionGroups.PlaneOrientationPatient(indexGenerator, itemFrame, brukerDataset);
        functionGroups.MRImageFrameType(indexGenerator, itemFrame, brukerDataset);
        functionGroups.MRTimingAndRelatedParameters(indexGenerator, itemFrame, brukerDataset);
        functionGroups.MREcho(indexGenerator, itemFrame, brukerDataset);
        functionGroups.MRModifier(indexGenerator, itemFrame, brukerDataset);
        functionGroups.MRImagingModifier(indexGenerator, itemFrame, brukerDataset);
        functionGroups.MRReceiveCoil(indexGenerator, itemFrame, brukerDataset);
        functionGroups.MRTransmitCoil(indexGenerator, itemFrame, brukerDataset);
        functionGroups.MRAverages(indexGenerator, itemFrame, brukerDataset);
        
        itemsPerFrame.push(itemFrame);
        
        indexGenerator.next();
    }
    
    dicomDataset[dicomifier.dictionary['PerFrameFunctionalGroupsSequence'][1]] = {
        'vr': dicomifier.dictionary['PerFrameFunctionalGroupsSequence'][0], 
        'Value' : itemsPerFrame };
        
    // Others fields
    dicomDataset[dicomifier.dictionary['InstanceNumber'][1]] = {
        'vr': dicomifier.dictionary['InstanceNumber'][0],
        'Value': [ 1 ] };
        
    toDicom(
        indexGenerator, dicomDataset, 'ContentDate',
        brukerDataset, 'VisuAcqDate', 1, dateTimeMapper('date'));

    toDicom(
        indexGenerator, dicomDataset, 'ContentTime',
        brukerDataset, 'VisuAcqDate', 1, dateTimeMapper('time'));
        
    toDicom(
        indexGenerator, dicomDataset, 'NumberOfFrames',
        brukerDataset, 'VisuCoreFrameCount', 1, parseInt, 
        function(brukerDataset) { 
            if (brukerDataset.VisuCoreDim !== undefined &&
                brukerDataset.VisuCoreDim[0] === "3") {
                return [ parseInt(brukerDataset.VisuCoreFrameCount) * 
                         brukerDataset.VisuCoreSize[2] ]; 
            }
            else {
                return [ brukerDataset.VisuCoreFrameCount ]; 
            }});
};
