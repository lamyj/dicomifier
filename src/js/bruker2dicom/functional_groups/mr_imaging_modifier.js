require('bruker2dicom/common.js');

var _module = namespace('dicomifier.bruker2dicom.functionalGroups');

_module.MRImagingModifier = function(indexGenerator, dicomSequenceItem, 
                                     brukerDataset) {
    var item = {};
    
    item[dicomifier.dictionary['MagnetizationTransfer'][1]] = {
        'vr': dicomifier.dictionary['MagnetizationTransfer'][0], 
        'Value' : [ 'NONE' ] }; // TODO
        
    item[dicomifier.dictionary['BloodSignalNulling'][1]] = {
        'vr': dicomifier.dictionary['BloodSignalNulling'][0], 
        'Value' : [ 'NO' ] }; // TODO
    
    item[dicomifier.dictionary['Tagging'][1]] = {
        'vr': dicomifier.dictionary['Tagging'][0], 
        'Value' : [ 'NONE' ] }; // TODO
        
    if (item[dicomifier.dictionary['Tagging'][1]]['Value'][0] !== 'NONE') {
        item[dicomifier.dictionary['TagSpacingFirstDimension'][1]] = {
            'vr': dicomifier.dictionary['TagSpacingFirstDimension'][0], 
            'Value' : [ 0 ] }; // TODO
            
        item[dicomifier.dictionary['TagAngleFirstAxis'][1]] = {
            'vr': dicomifier.dictionary['TagAngleFirstAxis'][0], 
            'Value' : [ 0 ] }; // TODO
    
        if (item[dicomifier.dictionary['Tagging'][1]]['Value'][0] === 'GRID') {
            item[dicomifier.dictionary['TagSpacingSecondDimension'][1]] = {
                'vr': dicomifier.dictionary['TagSpacingSecondDimension'][0], 
                'Value' : [ 0 ] }; // TODO
            
            item[dicomifier.dictionary['TagAngleSecondAxis'][1]] = {
                'vr': dicomifier.dictionary['TagAngleSecondAxis'][0], 
                'Value' : [ 0 ] }; // TODO
        }
            
        item[dicomifier.dictionary['TagThickness'][1]] = {
            'vr': dicomifier.dictionary['TagThickness'][0], 
            'Value' : [ 0 ] }; // TODO
    }
    
    item[dicomifier.dictionary['TransmitterFrequency'][1]] = {
        'vr': dicomifier.dictionary['TransmitterFrequency'][0], 
        'Value' : [ 0 ] }; // TODO
    
    item[dicomifier.dictionary['PixelBandwidth'][1]] = {
        'vr': dicomifier.dictionary['PixelBandwidth'][0], 
        'Value' : [ 0 ] }; // TODO
    
    dicomSequenceItem[dicomifier.dictionary['MRImagingModifierSequence'][1]] = {
        'vr': dicomifier.dictionary['MRImagingModifierSequence'][0], 
        'Value' : [ item ] };
};
