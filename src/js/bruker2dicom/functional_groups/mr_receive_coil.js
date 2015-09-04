require('bruker2dicom/common.js');

var _module = namespace('dicomifier.bruker2dicom.functionalGroups');

_module.MRReceiveCoil = function(indexGenerator, dicomSequenceItem, 
                                 brukerDataset) {
    var item = {};
    
    item[dicomifier.dictionary['ReceiveCoilName'][1]] = {
        'vr': dicomifier.dictionary['ReceiveCoilName'][0], 
        'Value' : [ 'Default' ] }; // TODO
    
    item[dicomifier.dictionary['ReceiveCoilManufacturerName'][1]] = {
        'vr': dicomifier.dictionary['ReceiveCoilManufacturerName'][0], 
        'Value' : [ ] }; // TODO
    
    item[dicomifier.dictionary['ReceiveCoilType'][1]] = {
        'vr': dicomifier.dictionary['ReceiveCoilType'][0], 
        'Value' : [ 'BODY' ] }; // TODO
    
    item[dicomifier.dictionary['QuadratureReceiveCoil'][1]] = {
        'vr': dicomifier.dictionary['QuadratureReceiveCoil'][0], 
        'Value' : [ 'NO' ] }; // TODO
        
    if (item[dicomifier.dictionary['ReceiveCoilType'][1]]['Value'][0] === 'MULTICOIL') {
        // add Multi-Coil Definition Sequence
    }
    
    dicomSequenceItem[dicomifier.dictionary['MRReceiveCoilSequence'][1]] = {
        'vr': dicomifier.dictionary['MRReceiveCoilSequence'][0], 
        'Value' : [ item ] };
};
