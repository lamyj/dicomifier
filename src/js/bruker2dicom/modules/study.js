require('bruker2dicom/common.js');

var _module = namespace('dicomifier.bruker2dicom.modules');

_module.GeneralStudy = function(indexGenerator, dicomDataset, brukerDataset) {
    var dateTimeMapper = dicomifier.bruker2dicom.dateTimeMapper;
    var toDicom = dicomifier.bruker2dicom.toDicom;

    toDicom(
        indexGenerator, dicomDataset, 'StudyInstanceUID',
        brukerDataset, 'VisuStudyUid', 1);

    toDicom(
        indexGenerator, dicomDataset, 'StudyDate', brukerDataset,
        'VisuStudyDate', 2, dateTimeMapper('date'));

    toDicom(
        indexGenerator, dicomDataset, 'StudyTime', brukerDataset,
        'VisuStudyDate', 2, dateTimeMapper('time'));

    toDicom(
        indexGenerator, dicomDataset, 'ReferringPhysicianName',
        brukerDataset, 'VisuStudyReferringPhysician', 2);

    toDicom(
        indexGenerator, dicomDataset, 'StudyID',
        brukerDataset, 'VisuStudyNumber', 2);

    dicomDataset[dicomifier.dictionary['AccessionNumber'][1]] = {
        'vr': dicomifier.dictionary['AccessionNumber'][0] };

    toDicom(
        indexGenerator, dicomDataset, 'StudyDescription',
        brukerDataset, 'VisuStudyId', 3);
};

_module.PatientStudy = function(indexGenerator, dicomDataset, brukerDataset) {
    var dateTimeMapper = dicomifier.bruker2dicom.dateTimeMapper;
    var toDicom = dicomifier.bruker2dicom.toDicom;

    toDicom(
        indexGenerator, dicomDataset, 'PatientWeight',
        brukerDataset, 'VisuSubjectWeight', 3, parseFloat);

    dicomDataset[dicomifier.dictionary['PatientSexNeutered'][1]] = {
        'vr': dicomifier.dictionary['PatientSexNeutered'][0] };
};
