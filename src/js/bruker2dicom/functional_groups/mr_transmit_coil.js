require('bruker2dicom/common.js');

var _module = namespace('dicomifier.bruker2dicom.functionalGroups');

_module.MRTransmitCoil = function(indexGenerator, dicomSequenceItem, 
                                  brukerDataset) {
    var item = {};
    
    item[dicomifier.dictionary['TransmitCoilName'][1]] = {
        'vr': dicomifier.dictionary['TransmitCoilName'][0], 
        'Value' : [ 'Default' ] }; // TODO
        
    item[dicomifier.dictionary['TransmitCoilManufacturerName'][1]] = {
        'vr': dicomifier.dictionary['TransmitCoilManufacturerName'][0], 
        'Value' : [ ] }; // TODO
    
    item[dicomifier.dictionary['TransmitCoilType'][1]] = {
        'vr': dicomifier.dictionary['TransmitCoilType'][0], 
        'Value' : [ 'BODY' ] }; // TODO
    
    dicomSequenceItem[dicomifier.dictionary['MRTransmitCoilSequence'][1]] = {
        'vr': dicomifier.dictionary['MRTransmitCoilSequence'][0], 
        'Value' : [ item ] };
};

