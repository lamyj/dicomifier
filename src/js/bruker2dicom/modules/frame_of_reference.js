require('bruker2dicom/common.js');

var _module = namespace('dicomifier.bruker2dicom.modules');

_module.FrameOfReference = function(indexGenerator, dicomDataset, brukerDataset) {
    var toDicom = dicomifier.bruker2dicom.toDicom;

    toDicom(
        indexGenerator, dicomDataset, 'FrameOfReferenceUID',
        brukerDataset, 'VisuUid', 1);

    dicomDataset[dicomifier.dictionary['PositionReferenceIndicator'][1]] = {
        'vr': dicomifier.dictionary['PositionReferenceIndicator'][0] };
};
