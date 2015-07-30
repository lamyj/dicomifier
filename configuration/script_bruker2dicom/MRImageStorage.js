
var spacingbetweenslice = function(brukerDataset) {
    var visucorepos = brukerDataset.VisuCorePosition;
    if (visucorepos.length < 6) {
        return null;
    }
    var difference = [ visucorepos[3] - visucorepos[0], 
                       visucorepos[4] - visucorepos[1], 
                       visucorepos[5] - visucorepos[2] ];
                       
    return [ difference[0] * difference[0] +
             difference[1] * difference[1] +
             difference[2] * difference[2] ];
}

var brukerDataset = dicomifier.inputs[0];
if (brukerDataset === undefined ) {
    throw new dicomifier.Exception("Missing input");
}

var frameGroups = dicomifier.getFrameGroups(brukerDataset);
var indexGenerator = new dicomifier.frameIndexGenerator(frameGroups);

while (indexGenerator.done() == false) {
    var dicomDataset = {};

    // Patient module
    toDicom(indexGenerator, dicomDataset, 'PatientName', 
            brukerDataset, 'VisuSubjectName', 2);
    toDicom(indexGenerator, dicomDataset, 'PatientID', 
            brukerDataset, 'VisuSubjectId', 2);
    toDicom(indexGenerator, dicomDataset, 'PatientBirthDate',
            brukerDataset, 'VisuSubjectBirthDate', 2);
    toDicom(indexGenerator, dicomDataset, 'PatientSex', 
            brukerDataset, 'VisuSubjectSex', 
            2, dictionaryMapper({'MALE': 'M', 'FEMALE': 'F',
                                 'UNDEFINED': 'O', 'UNKNOWN': 'O' }));
    toDicom(indexGenerator, dicomDataset, 'PatientComments',
            brukerDataset, 'VisuSubjectComment', 3);
    dicomDataset[dicomifier.dictionary['PatientSpeciesDescription'][1]] =
            { 'vr': dicomifier.dictionary['PatientSpeciesDescription'][0], 
              'Value' : ['UNKNOWN'] };
    toDicom(indexGenerator, dicomDataset, 'PatientBreedDescription', 
            brukerDataset, null, 2);
    toDicom(indexGenerator, dicomDataset, 'PatientBreedCodeSequence', 
            brukerDataset, null, 2);
    toDicom(indexGenerator, dicomDataset, 'BreedRegistrationSequence', 
            brukerDataset, null, 2);
    toDicom(indexGenerator, dicomDataset, 'ResponsiblePerson', 
            brukerDataset, null, 2);
    toDicom(indexGenerator, dicomDataset, 'ResponsibleOrganization', 
            brukerDataset, null, 2);

    // General Study module
    toDicom(indexGenerator, dicomDataset, 'StudyInstanceUID', 
            brukerDataset, 'VisuStudyUid', 1);
    toDicom(indexGenerator, dicomDataset, 'StudyDate', brukerDataset, 
            'VisuStudyDate', 2, dateTimeMapper('date'));
    toDicom(indexGenerator, dicomDataset, 'StudyTime', brukerDataset, 
            'VisuStudyDate', 2, dateTimeMapper('time'));
    toDicom(indexGenerator, dicomDataset, 'ReferringPhysicianName',
            brukerDataset, 'VisuStudyReferringPhysician', 2);
    toDicom(indexGenerator, dicomDataset, 'StudyID', 
            brukerDataset, 'VisuStudyNumber', 2);
    toDicom(indexGenerator, dicomDataset, 'AccessionNumber', 
            brukerDataset, null, 2);
    toDicom(indexGenerator, dicomDataset, 'StudyDescription', 
            brukerDataset, 'VisuStudyId', 3);

    // Patient Study module
    toDicom(indexGenerator, dicomDataset, 'PatientWeight',
            brukerDataset, 'VisuSubjectWeight', 3, parseFloat);
    toDicom(indexGenerator, dicomDataset, 'PatientSexNeutered', 
            brukerDataset, null, 2);

    // General Series module
    dicomDataset[dicomifier.dictionary['Modality'][1]] =
            { 'vr': dicomifier.dictionary['Modality'][0], 
              'Value' : ['MR'] };
    toDicom(indexGenerator, dicomDataset, 'SeriesInstanceUID', 
            brukerDataset, 'VisuUid', 1);
    toDicom(indexGenerator, dicomDataset, 'SeriesNumber', 
            brukerDataset, null, 2, parseInt, 
            function(brukerDS) { 
                    return [ brukerDS.VisuExperimentNumber || 
                             brukerDS.VisuSeriesNumber ]; } );
    toDicom(indexGenerator, dicomDataset, 'Laterality', 
            brukerDataset, null, 2);
    toDicom(indexGenerator, dicomDataset, 'SeriesDate', 
            brukerDataset, 'VisuSeriesDate', 2, dateTimeMapper('date'));
    toDicom(indexGenerator, dicomDataset, 'SeriesTime', 
            brukerDataset, 'VisuSeriesDate', 2, dateTimeMapper('time'));
    toDicom(indexGenerator, dicomDataset, 'PerformingPhysicianName', 
            brukerDataset, 'OWNER', 3);
    toDicom(indexGenerator, dicomDataset, 'ProtocolName',
            brukerDataset, 'VisuAcquisitionProtocol', 3);
    toDicom(indexGenerator, dicomDataset, 'SeriesDescription',
            brukerDataset, 'VisuAcquisitionProtocol', 3);
    toDicom(indexGenerator, dicomDataset, 'PatientPosition',
            brukerDataset, 'VisuSubjectPosition', 2,
            dictionaryMapper({ 'Head_Supine': 'HFS', 'Head_Prone': 'HFP',
                               'Head_Left' : 'HFDL', 'Head_Right': 'HFDR',
                               'Foot_Supine': 'FFS', 'Foot_Prone': 'FFP',
                               'Foot_Left': 'FFDL', 'Foot_Right': 'FFDR' }
                            ));
    toDicom(indexGenerator, dicomDataset, 'AnatomicalOrientationType',
            brukerDataset, 'VisuSubjectType', 3);
        
    // Frame of Reference Module
    toDicom(indexGenerator, dicomDataset, 'FrameOfReferenceUID', 
            brukerDataset, 'VisuUid', 1);
    toDicom(indexGenerator, dicomDataset, 'PositionReferenceIndicator', 
            brukerDataset, null, 2);

    // General Equipment Module
    toDicom(indexGenerator, dicomDataset, 'Manufacturer', 
            brukerDataset, 'ORIGIN', 2);
    toDicom(indexGenerator, dicomDataset, 'InstitutionName',
            brukerDataset, 'VisuInstitution', 3);
    toDicom(indexGenerator, dicomDataset, 'StationName', 
            brukerDataset, 'VisuStation', 3);
    toDicom(indexGenerator, dicomDataset, 'SoftwareVersions', 
            brukerDataset, null, 3, undefined, 
            function(brukerDS) { return [
                    (brukerDS.VisuCreator !== undefined &&
                     brukerDS.VisuCreator.length > 0 ?
                        brukerDS.VisuCreator[0] + ' ' : '') +
                    (brukerDS.VisuCreatorVersion !== undefined &&
                     brukerDS.VisuCreatorVersion.length > 0 ?
                        brukerDS.VisuCreatorVersion[0] : '') ]; } );
            
    // General Image Module
    dicomDataset[dicomifier.dictionary['InstanceNumber'][1]] =
            { 'vr': dicomifier.dictionary['InstanceNumber'][0], 
              'Value' : [ indexGenerator.currentStep + 1 ] };
    dicomDataset[dicomifier.dictionary['ImageType'][1]] =
            { 'vr': dicomifier.dictionary['ImageType'][0], 
              'Value' : [ 'ORIGINAL', 'PRIMARY' ] };
    toDicom(indexGenerator, dicomDataset, 'AcquisitionDate', 
            brukerDataset, 'VisuAcqDate', 3, dateTimeMapper('date'));
    toDicom(indexGenerator, dicomDataset, 'AcquisitionTime', 
            brukerDataset, 'VisuAcqDate', 3, dateTimeMapper('time'));
    toDicom(indexGenerator, dicomDataset, 'ImagesInAcquisition',
            brukerDataset, 'VisuCoreFrameCount', 3, parseInt);
    toDicom(indexGenerator, dicomDataset, 'ImageComments', 
            brukerDataset, null, 3);

    // Image Plane Module
    toDicom(indexGenerator, dicomDataset, 'PixelSpacing', brukerDataset, 
            null, 1, undefined, function(brukerDS) { 
                       var array = divideArray(brukerDS.VisuCoreExtent,
                                               brukerDS.VisuCoreSize);
                       return array; } );
    toDicom(indexGenerator, dicomDataset, 'ImageOrientationPatient', 
            brukerDataset, 'VisuCoreOrientation', 1, undefined,
            function(brukerDS) { 
                var array = [];
                for (var index = 0; 
                     index < brukerDS.VisuCoreOrientation.length; 
                     index += 9) {
                    array.push(brukerDS.VisuCoreOrientation.slice(
                                    index, index + 6));
                }
                return array;
            } );
    toDicom(indexGenerator, dicomDataset, 'ImagePositionPatient', 
            brukerDataset, 'VisuCorePosition', 1, undefined,
            function(brukerDS) { 
                var array = [];
                for (var index = 0; 
                     index < brukerDS.VisuCorePosition.length; 
                     index += 3) {
                    array.push(brukerDS.VisuCorePosition.slice(
                                    index, index + 3));
                }
                return array;
            } );
    toDicom(indexGenerator, dicomDataset, 'SliceThickness',
            brukerDataset, 'VisuCoreFrameThickness', 2);

    // Image Pixel Module
    dicomDataset[dicomifier.dictionary['SamplesPerPixel'][1]] =
            { 'vr': dicomifier.dictionary['SamplesPerPixel'][0], 
              'Value' : [ 1 ] };
    dicomDataset[dicomifier.dictionary['PhotometricInterpretation'][1]] =
            { 'vr': dicomifier.dictionary['PhotometricInterpretation'][0], 
              'Value' : [ 'MONOCHROME2' ] };
    toDicom(indexGenerator, dicomDataset, 'Rows', brukerDataset, 
            'VisuCoreSize', 1, undefined, 
            function(brukerDS) { 
                    return [ brukerDS.VisuCoreSize[0] ]; } );
    toDicom(indexGenerator, dicomDataset, 'Columns', brukerDataset, 
            'VisuCoreSize', 1, undefined, 
            function(brukerDS) { 
                    return [ brukerDS.VisuCoreSize[1] ]; } );
    dicomDataset[dicomifier.dictionary['BitsAllocated'][1]] =
            { 'vr': dicomifier.dictionary['BitsAllocated'][0], 
              'Value' : [ 16 ] };
    dicomDataset[dicomifier.dictionary['BitsStored'][1]] =
            { 'vr': dicomifier.dictionary['BitsStored'][0], 
              'Value' : [ 16 ] };
    dicomDataset[dicomifier.dictionary['HighBit'][1]] =
            { 'vr': dicomifier.dictionary['HighBit'][0], 
              'Value' : [ bigEndian() ? 0 : 15 ] };
    dicomDataset[dicomifier.dictionary['PixelRepresentation'][1]] =
            { 'vr': dicomifier.dictionary['PixelRepresentation'][0], 
              'Value' : [ 0 ] };
    pixelDataToDicom(indexGenerator, dicomDataset, 'PixelData', 
                     brukerDataset, 1);

    // MR Image Module
    dicomDataset[dicomifier.dictionary['ScanningSequence'][1]] =
            { 'vr': dicomifier.dictionary['ScanningSequence'][0], 
              'Value' : [ 'RM' ] };
    dicomDataset[dicomifier.dictionary['SequenceVariant'][1]] =
            { 'vr': dicomifier.dictionary['SequenceVariant'][0], 
              'Value' : [ 'NONE' ] };
    toDicom(indexGenerator, dicomDataset, 'ScanOptions', 
            brukerDataset, null, 2);
    toDicom(indexGenerator, dicomDataset, 'MRAcquisitionType', 
            brukerDataset, 'VisuCoreDim', 2, function(x) { 
                                                return x + 'D'; } );
    toDicom(indexGenerator, dicomDataset, 'RepetitionTime',
            brukerDataset, 'VisuAcqRepetitionTime', 2);
    toDicom(indexGenerator, dicomDataset, 'EchoTime', 
            brukerDataset, 'VisuAcqEchoTime', 2);
    toDicom(indexGenerator, dicomDataset, 'EchoTrainLength',
            brukerDataset, 'VisuAcqEchoTrainLength', 2, parseInt);
    toDicom(indexGenerator, dicomDataset, 'InversionTime',
            brukerDataset, 'VisuAcqInversionTime', 2);
    toDicom(indexGenerator, dicomDataset, 'SequenceName',
            brukerDataset, 'VisuAcqSequenceName', 3);
    toDicom(indexGenerator, dicomDataset, 'NumberOfAverages',
            brukerDataset, 'VisuAcqNumberOfAverages', 3, parseFloat);
    toDicom(indexGenerator, dicomDataset, 'ImagingFrequency',
            brukerDataset, 'VisuAcqImagingFrequency', 3, parseFloat);
    toDicom(indexGenerator, dicomDataset, 'ImagedNucleus',
            brukerDataset, 'VisuAcqImagedNucleus', 3);
    // According to Bruker doc, VisuAcqImagingFrequency is the imaging
    // frequency of 1H, regardless of VisuAcqImagingNucleus
    toDicom(indexGenerator, dicomDataset, 'MagneticFieldStrength',
            brukerDataset, 'VisuAcqImagingFrequency', 3,
            function(x) { return parseFloat(x) / 42.577480610; } );
    toDicom(indexGenerator, dicomDataset, 'SpacingBetweenSlices', 
            brukerDataset, null, 3, undefined, spacingbetweenslice );
    toDicom(indexGenerator, dicomDataset, 'NumberOfPhaseEncodingSteps',
            brukerDataset, 'VisuAcqPhaseEncSteps', 3, parseInt);
    toDicom(indexGenerator, dicomDataset, 'PixelBandwidth',
            brukerDataset, 'VisuAcqPixelBandwidth', 3, parseFloat);
    // AcquisitionMatrix => optional
    // InPlanePhaseEncodingDirection => optional
    toDicom(indexGenerator, dicomDataset, 'FlipAngle', brukerDataset, 
            'VisuAcqFlipAngle', 3, parseFloat);

    // SOP Common Module
    dicomDataset[dicomifier.dictionary['SOPClassUID'][1]] =
            { 'vr': dicomifier.dictionary['SOPClassUID'][0], 
              'Value' : [ '1.2.840.10008.5.1.4.1.1.4' ] };
    dicomDataset[dicomifier.dictionary['SOPInstanceUID'][1]] =
            { 'vr': dicomifier.dictionary['SOPInstanceUID'][0], 
              'Value' : [ dcmGenerateUniqueIdentifier() ] };
    toDicom(indexGenerator, dicomDataset, 'InstanceCreationDate', 
            brukerDataset, null, 3, dateTimeMapper('date'), 
            function(brukerDS) { return [ String(new Date()) ]; } );
    toDicom(indexGenerator, dicomDataset, 'InstanceCreationTime', 
            brukerDataset, null, 3, dateTimeMapper('time'),
            function(brukerDS) { return [ String(new Date()) ]; } );

    dicomifier.outputs[indexGenerator.currentStep] = dicomDataset;
    
    indexGenerator.next();
}

// Return number of outputs
String(dicomifier.outputs.length);
