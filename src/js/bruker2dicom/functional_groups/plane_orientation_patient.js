require('bruker2dicom/common.js');

var _module = namespace('dicomifier.bruker2dicom.functionalGroups');

_module.PlaneOrientationPatient = function(indexGenerator, dicomSequenceItem, 
                                           brukerDataset) {
    var toDicom = dicomifier.bruker2dicom.toDicom;
    
    var item = {};
    
    var indexOrentation = dicomifier.bruker2dicom.getFrameGroupIndex(brukerDataset, 'VisuCoreOrientation');
    var beginIndex = indexOrentation[1] + indexGenerator.currentIndex[indexOrentation[0]] * 9;
    var value = brukerDataset['VisuCoreOrientation'].slice(beginIndex, beginIndex + 6);
    item[dicomifier.dictionary['ImageOrientationPatient'][1]] = {
        'vr': dicomifier.dictionary['ImageOrientationPatient'][0], 
        'Value' : value };
    
    dicomSequenceItem[dicomifier.dictionary['PlaneOrientationSequence'][1]] = {
        'vr': dicomifier.dictionary['PlaneOrientationSequence'][0], 
        'Value' : [ item ] };
};
