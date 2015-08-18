require('bruker2dicom/common.js');

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
        brukerDataset, 'VisuCoreFrameCount', 3, parseInt);

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

_module.ImagePixel = function(indexGenerator, dicomDataset, brukerDataset, pixelData) {
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
        'vr': 'OW', 'InlineBinary' : pixelData[indexGenerator.currentStep] };
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

_module.SOPCommon = function(indexGenerator, dicomDataset, brukerDataset) {
    var toDicom = dicomifier.bruker2dicom.toDicom;
    var dateTimeMapper = dicomifier.bruker2dicom.dateTimeMapper;

    dicomDataset[dicomifier.dictionary['SOPClassUID'][1]] = {
        'vr': dicomifier.dictionary['SOPClassUID'][0],
        'Value': [ '1.2.840.10008.5.1.4.1.1.4' ] };

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
