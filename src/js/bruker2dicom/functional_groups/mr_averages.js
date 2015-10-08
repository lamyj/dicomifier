require('bruker2dicom/common.js');

var _module = namespace('dicomifier.bruker2dicom.functionalGroups');

_module.MRAverages = function(indexGenerator, dicomSequenceItem, 
                              brukerDataset) {
    var item = {};
    
    item[dicomifier.dictionary['NumberOfAverages'][1]] = {
        'vr': dicomifier.dictionary['NumberOfAverages'][0], 
        'Value' : [ 0 ] }; // TODO
        
    dicomSequenceItem[dicomifier.dictionary['MRAveragesSequence'][1]] = {
        'vr': dicomifier.dictionary['MRAveragesSequence'][0], 
        'Value' : [ item ] };
};
