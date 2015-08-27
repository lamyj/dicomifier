require('bruker2dicom/common.js');

var _module = namespace('dicomifier.bruker2dicom.modules');

_module.Patient = function(indexGenerator, dicomDataset, brukerDataset) {
    var toDicom = dicomifier.bruker2dicom.toDicom;
    var dictionaryMapper = dicomifier.bruker2dicom.dictionaryMapper;

    toDicom(
        indexGenerator, dicomDataset, 'PatientName',
        brukerDataset, 'VisuSubjectName', 2);

    toDicom(
        indexGenerator, dicomDataset, 'PatientID',
        brukerDataset, 'VisuSubjectId', 2);

    toDicom(
        indexGenerator, dicomDataset, 'PatientBirthDate',
        brukerDataset, 'VisuSubjectBirthDate', 2);

    toDicom(
        indexGenerator, dicomDataset, 'PatientSex',
        brukerDataset, 'VisuSubjectSex', 2,
        dictionaryMapper({
            'MALE': 'M', 'FEMALE': 'F', 'UNDEFINED': 'O', 'UNKNOWN': 'O' }));

    toDicom(
        indexGenerator, dicomDataset, 'PatientComments',
        brukerDataset, 'VisuSubjectComment', 3);

    dicomDataset[dicomifier.dictionary['PatientSpeciesDescription'][1]] = {
        'vr': dicomifier.dictionary['PatientSpeciesDescription'][0],
        'Value' : ['UNKNOWN'] };

    dicomDataset[dicomifier.dictionary['PatientBreedDescription'][1]] = {
        'vr': dicomifier.dictionary['PatientBreedDescription'][0] };

    dicomDataset[dicomifier.dictionary['PatientBreedCodeSequence'][1]] = {
        'vr': dicomifier.dictionary['PatientBreedCodeSequence'][0] };

    dicomDataset[dicomifier.dictionary['BreedRegistrationSequence'][1]] = {
        'vr': dicomifier.dictionary['BreedRegistrationSequence'][0] };

    dicomDataset[dicomifier.dictionary['ResponsiblePerson'][1]] = {
        'vr': dicomifier.dictionary['ResponsiblePerson'][0] };

    dicomDataset[dicomifier.dictionary['ResponsibleOrganization'][1]] = {
        'vr': dicomifier.dictionary['ResponsibleOrganization'][0] };
};
