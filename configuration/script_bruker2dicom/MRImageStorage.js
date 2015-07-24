
var brukerDataset = dicomifier.inputs[0];
if (brukerDataset === undefined ) {
    throw new dicomifier.Exception("Missing input");
}

var dicomDataset = {};

// Patient module
toDicom(dicomDataset, 'PatientName', brukerDataset.VisuSubjectName, 2);
toDicom(dicomDataset, 'PatientID', brukerDataset.VisuSubjectId, 2);
toDicom(dicomDataset, 'PatientBirthDate',
        brukerDataset.VisuSubjectBirthDate, 2);
toDicom(dicomDataset, 'PatientSex', brukerDataset.VisuSubjectSex, 2,
    dictionaryMapper({'MALE': 'M', 'FEMALE': 'F',
                      'UNDEFINED': 'O', 'UNKNOWN': 'O' }));
toDicom(dicomDataset, 'PatientComments',
        brukerDataset.VisuSubjectComment, 3);
toDicom(dicomDataset, 'PatientSpeciesDescription', ['UNKNOWN'], 1);
toDicom(dicomDataset, 'PatientBreedDescription', null, 2);
toDicom(dicomDataset, 'PatientBreedCodeSequence', null, 2);
toDicom(dicomDataset, 'BreedRegistrationSequence', null, 2);
toDicom(dicomDataset, 'ResponsiblePerson', null, 2);
toDicom(dicomDataset, 'ResponsibleOrganization', null, 2);

// General Study module
toDicom(dicomDataset, 'StudyInstanceUID', brukerDataset.VisuStudyUid, 1);
toDicom(dicomDataset, 'StudyDate', brukerDataset.VisuStudyDate, 2,
        dateTimeMapper('date'));
toDicom(dicomDataset, 'StudyTime', brukerDataset.VisuStudyDate, 2,
        dateTimeMapper('time'));
toDicom(dicomDataset, 'ReferringPhysicianName',
        brukerDataset.VisuStudyReferringPhysician, 2);
toDicom(dicomDataset, 'StudyID', brukerDataset.VisuStudyNumber, 2);
toDicom(dicomDataset, 'AccessionNumber', null, 2);
toDicom(dicomDataset, 'StudyDescription', brukerDataset.VisuStudyId, 3);

// Patient Study module
toDicom(dicomDataset, 'PatientWeight',
        brukerDataset.VisuSubjectWeight, 3, parseFloat);
toDicom(dicomDataset, 'PatientSexNeutered', null, 2);

// General Series module
toDicom(dicomDataset, 'Modality', [ 'MR' ], 1);
toDicom(dicomDataset, 'SeriesInstanceUID', brukerDataset.VisuUid, 1);
toDicom(dicomDataset, 'SeriesNumber',
        brukerDataset.VisuExperimentNumber ||
        brukerDataset.VisuSeriesNumber, 2, parseInt);
toDicom(dicomDataset, 'Laterality', null, 2);
toDicom(dicomDataset, 'SeriesDate', brukerDataset.VisuSeriesDate, 2,
        dateTimeMapper('date'));
toDicom(dicomDataset, 'SeriesTime', brukerDataset.VisuSeriesDate, 2,
        dateTimeMapper('time'));
toDicom(dicomDataset, 'PerformingPhysicianName', brukerDataset.OWNER, 3);
toDicom(dicomDataset, 'ProtocolName',
        brukerDataset.VisuAcquisitionProtocol, 3);
toDicom(dicomDataset, 'SeriesDescription',
        brukerDataset.VisuAcquisitionProtocol, 3);
toDicom(dicomDataset, 'PatientPosition',
        brukerDataset.VisuSubjectPosition, 2,
        dictionaryMapper({ 'Head_Supine': 'HFS', 'Head_Prone': 'HFP',
                           'Head_Left' : 'HFDL', 'Head_Right': 'HFDR',
                           'Foot_Supine': 'FFS', 'Foot_Prone': 'FFP',
                           'Foot_Left': 'FFDL', 'Foot_Right': 'FFDR' }));
toDicom(dicomDataset, 'AnatomicalOrientationType',
        brukerDataset.VisuSubjectType, 3);
        
// Frame of Reference Module
toDicom(dicomDataset, 'FrameOfReferenceUID', brukerDataset.VisuUid, 1);
toDicom(dicomDataset, 'PositionReferenceIndicator', null, 2);

// General Equipment Module
toDicom(dicomDataset, 'Manufacturer', brukerDataset.ORIGIN, 2);
toDicom(dicomDataset, 'InstitutionName',
        brukerDataset.VisuInstitution, 3);
toDicom(dicomDataset, 'StationName', brukerDataset.VisuStation, 3);
toDicom(dicomDataset, 'SoftwareVersions',
        (brukerDataset.VisuCreator !== undefined &&
         brukerDataset.VisuCreator.length > 0 ?
            brukerDataset.VisuCreator[0] : '') +
        (brukerDataset.VisuCreatorVersion !== undefined &&
         brukerDataset.VisuCreatorVersion.length > 0 ?
            brukerDataset.VisuCreatorVersion[0] : ''), 3);
            
// General Image Module
// InstanceNumber => FrameIndexGenerator
toDicom(dicomDataset, 'ImageType', [ 'ORIGINAL', 'PRIMARY' ], 1);
toDicom(dicomDataset, 'AcquisitionDate', brukerDataset.VisuAcqDate, 3,
        dateTimeMapper('date'));
toDicom(dicomDataset, 'AcquisitionTime', brukerDataset.VisuAcqDate, 3,
        dateTimeMapper('time'));
toDicom(dicomDataset, 'ImagesInAcquisition',
        brukerDataset.VisuCoreFrameCount, 3, parseInt);
toDicom(dicomDataset, 'ImageComments', null, 3);

// Image Plane Module
toDicom(dicomDataset, 'PixelSpacing',
        divideArray(brukerDataset.VisuCoreExtent,
                    brukerDataset.VisuCoreSize), 1);
// ImageOrientationPatient => FrameIndexGenerator
// ImagePositionPatient => FrameIndexGenerator
toDicom(dicomDataset, 'SliceThickness',
        brukerDataset.VisuCoreFrameThickness, 2);

// Image Pixel Module
toDicom(dicomDataset, 'SamplesPerPixel', [ 1 ], 1);
toDicom(dicomDataset, 'PhotometricInterpretation', [ 'MONOCHROME2' ], 1);
toDicom(dicomDataset, 'Rows', [ brukerDataset.VisuCoreSize[0] ], 1);
toDicom(dicomDataset, 'Columns', [ brukerDataset.VisuCoreSize[1] ], 1);
toDicom(dicomDataset, 'BitsAllocated', [ 16 ], 1);
toDicom(dicomDataset, 'BitsStored', [ 16 ], 1);
toDicom(dicomDataset, 'HighBit', [ bigEndian() ? 0 : 15 ], 1);
toDicom(dicomDataset, 'PixelRepresentation', [ 0 ], 1);
// PixelData => todo

// MR Image Module
toDicom(dicomDataset, 'ScanningSequence', [ 'MR' ], 1);
toDicom(dicomDataset, 'SequenceVariant', [ 'NONE' ], 1);
toDicom(dicomDataset, 'ScanOptions', null, 2);
toDicom(dicomDataset, 'MRAcquisitionType', brukerDataset.VisuCoreDim, 2,
        function(x) { return x + 'D'; } );
toDicom(dicomDataset, 'RepetitionTime',
        brukerDataset.VisuAcqRepetitionTime, 2);
toDicom(dicomDataset, 'EchoTime', brukerDataset.VisuAcqEchoTime, 2);
toDicom(dicomDataset, 'EchoTrainLength',
        brukerDataset.VisuAcqEchoTrainLength, 2, parseInt);
toDicom(dicomDataset, 'InversionTime',
        brukerDataset.VisuAcqInversionTime, 2);
toDicom(dicomDataset, 'SequenceName',
        brukerDataset.VisuAcqSequenceName, 3);
toDicom(dicomDataset, 'NumberOfAverages',
        brukerDataset.VisuAcqNumberOfAverages, 3, parseFloat);
toDicom(dicomDataset, 'ImagingFrequency',
        brukerDataset.VisuAcqImagingFrequency, 3, parseFloat);
toDicom(dicomDataset, 'ImagedNucleus',
        brukerDataset.VisuAcqImagedNucleus, 3);
// According to Bruker doc, VisuAcqImagingFrequency is the imaging
// frequency of 1H, regardless of VisuAcqImagingNucleus
toDicom(dicomDataset, 'MagneticFieldStrength',
        brukerDataset.VisuAcqImagingFrequency, 3,
        function(x) { return parseFloat(x) / 42.577480610; } );
function spacingbetweenslice() {
    var visucorepos = brukerDataset.VisuCorePosition;
    if (visucorepos.length < 6) {
        return null;
    }
    var difference = [ visucorepos[3] - visucorepos[0], 
                       visucorepos[4] - visucorepos[1], 
                       visucorepos[5] - visucorepos[2] ];
                       
    return difference[0] * difference[0] +
           difference[1] * difference[1] +
           difference[2] * difference[2];
}
toDicom(dicomDataset, 'SpacingBetweenSlices', [ spacingbetweenslice() ], 3);
toDicom(dicomDataset, 'NumberOfPhaseEncodingSteps',
        brukerDataset.VisuAcqPhaseEncSteps, 3, parseInt);
toDicom(dicomDataset, 'PixelBandwidth',
        brukerDataset.VisuAcqPixelBandwidth, 3, parseFloat);
// AcquisitionMatrix => optional
// InPlanePhaseEncodingDirection => optional
toDicom(dicomDataset, 'FlipAngle', brukerDataset.VisuAcqFlipAngle, 3,
        parseFloat);

// SOP Common Module
toDicom(dicomDataset, 'SOPClassUID', [ '1.2.840.10008.5.1.4.1.1.4' ], 1);
toDicom(dicomDataset, 'SOPInstanceUID',
        [ dcmGenerateUniqueIdentifier() ], 1);
toDicom(dicomDataset, 'InstanceCreationDate', [ String(new Date()) ], 3,
        dateTimeMapper('date'));
toDicom(dicomDataset, 'InstanceCreationTime', [ String(new Date()) ], 3,
        dateTimeMapper('time'));

dicomifier.outputs[0] = dicomDataset;
