require('bruker2dicom/common.js');

var _module = namespace('dicomifier.bruker2dicom.functionalGroups');

_module.MREcho = function(indexGenerator, dicomSequenceItem, 
                           brukerDataset) {
    var item = {};
    
    var indexEchoTime = dicomifier.bruker2dicom.getFrameGroupIndex(brukerDataset, 'VisuAcqEchoTime');
    var beginIndex = 0;
    if (indexEchoTime !== null) {
        beginIndex = indexEchoTime[1] + indexGenerator.currentIndex[indexEchoTime[0]];
    }
    var value = brukerDataset['VisuAcqEchoTime'].slice(beginIndex, beginIndex + 1);
    item[dicomifier.dictionary['EffectiveEchoTime'][1]] = {
        'vr': dicomifier.dictionary['EffectiveEchoTime'][0], 
        'Value' : value };
    
    dicomSequenceItem[dicomifier.dictionary['MREchoSequence'][1]] = {
        'vr': dicomifier.dictionary['MREchoSequence'][0], 
        'Value' : [ item ] };
};
