require('bruker2dicom/common.js');

var _module = namespace('dicomifier.bruker2dicom.modules');

_module.GeneralEquipment = function(indexGenerator, dicomDataset, brukerDataset) {
    var toDicom = dicomifier.bruker2dicom.toDicom;

    toDicom(
        indexGenerator, dicomDataset, 'Manufacturer',
        brukerDataset, 'ORIGIN', 2);

    toDicom(
        indexGenerator, dicomDataset, 'InstitutionName',
        brukerDataset, 'VisuInstitution', 3);

    toDicom(
        indexGenerator, dicomDataset, 'StationName',
        brukerDataset, 'VisuStation', 3);

    toDicom(
        indexGenerator, dicomDataset, 'SoftwareVersions',
        brukerDataset, null, 3, undefined,
        function(brukerDataset) {
            var items = [];

            var fields = ['VisuCreator', 'VisuCreatorVersion'];
            fields.forEach(function(x) {
                var field = brukerDataset[x];
                if(field !== undefined && field !== '') {
                    items.push(x);
                }
            });
        });
};
