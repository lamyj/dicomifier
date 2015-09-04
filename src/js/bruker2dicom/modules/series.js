require('bruker2dicom/common.js');

var _module = namespace('dicomifier.bruker2dicom.modules');

_module.GeneralSeries = function(indexGenerator, dicomDataset, brukerDataset) {
    var toDicom = dicomifier.bruker2dicom.toDicom;
    var dateTimeMapper = dicomifier.bruker2dicom.dateTimeMapper;
    var dictionaryMapper = dicomifier.bruker2dicom.dictionaryMapper;

    dicomDataset[dicomifier.dictionary['Modality'][1]] = {
        'vr': dicomifier.dictionary['Modality'][0], 'Value' : ['MR'] };

    toDicom(
        indexGenerator, dicomDataset, 'SeriesInstanceUID',
        brukerDataset, 'VisuUid', 1);

    toDicom(
        indexGenerator, dicomDataset, 'SeriesNumber',
        brukerDataset, null, 2, parseInt,
        function(brukerDataset) { return [
            brukerDataset.VisuExperimentNumber || brukerDataset.VisuSeriesNumber ]; } );

    dicomDataset[dicomifier.dictionary['Laterality'][1]] = {
        'vr': dicomifier.dictionary['Laterality'][0] };

    toDicom(
        indexGenerator, dicomDataset, 'SeriesDate',
        brukerDataset, 'VisuSeriesDate', 2, dateTimeMapper('date'));

    toDicom(
        indexGenerator, dicomDataset, 'SeriesTime',
        brukerDataset, 'VisuSeriesDate', 2, dateTimeMapper('time'));

    toDicom(
        indexGenerator, dicomDataset, 'PerformingPhysicianName',
        brukerDataset, 'OWNER', 3);

    toDicom(
        indexGenerator, dicomDataset, 'ProtocolName',
        brukerDataset, 'VisuAcquisitionProtocol', 3);

    toDicom(
        indexGenerator, dicomDataset, 'SeriesDescription',
        brukerDataset, 'VisuAcquisitionProtocol', 3);

    toDicom(
        indexGenerator, dicomDataset, 'PatientPosition',
        brukerDataset, 'VisuSubjectPosition', 2,
        dictionaryMapper({
            'Head_Supine': 'HFS', 'Head_Prone': 'HFP',
            'Head_Left' : 'HFDL', 'Head_Right': 'HFDR',
            'Foot_Supine': 'FFS', 'Foot_Prone': 'FFP',
            'Foot_Left': 'FFDL', 'Foot_Right': 'FFDR' }));

    toDicom(
        indexGenerator, dicomDataset, 'AnatomicalOrientationType',
        brukerDataset, 'VisuSubjectType', 3);
};

_module.MRSeries = function(indexGenerator, dicomDataset, brukerDataset) {

    dicomDataset[dicomifier.dictionary['Modality'][1]] = {
        'vr': dicomifier.dictionary['Modality'][0], 'Value' : ['MR'] };
    
    // add field ReferencedPerformedProcedureStepSequence
    // Required if a Performed Procedure Step SOP Class was
    // involved in the creation of this Series.
    /*
    // Only one item
    var item = {};
    item[dicomifier.dictionary['ReferencedSOPClassUID'][1]] = {
        'vr': dicomifier.dictionary['ReferencedSOPClassUID'][0], 'Value' : ['to_defined']};
    item[dicomifier.dictionary['ReferencedSOPInstanceUID'][1]] = {
        'vr': dicomifier.dictionary['ReferencedSOPInstanceUID'][0], 'Value' : ['to_defined']};
        
    dicomDataset[dicomifier.dictionary['ReferencedPerformedProcedureStepSequence'][1]] = {
        'vr': dicomifier.dictionary['ReferencedPerformedProcedureStepSequence'][0], 'Value' : [ item ] };
    */
    
};
