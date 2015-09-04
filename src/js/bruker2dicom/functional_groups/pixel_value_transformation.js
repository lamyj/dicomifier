require('bruker2dicom/common.js');

var _module = namespace('dicomifier.bruker2dicom.functionalGroups');

_module.PixelValueTransformation = function(indexGenerator, dicomSequenceItem, 
                                            brukerDataset, rescaleIntercept, 
                                            rescaleSlope) {
    var item = {};
    
    item[dicomifier.dictionary['RescaleIntercept'][1]] = {
        'vr': dicomifier.dictionary['RescaleIntercept'][0], 
        'Value' : [ rescaleIntercept ] };
        
    item[dicomifier.dictionary['RescaleSlope'][1]] = {
        'vr': dicomifier.dictionary['RescaleSlope'][0], 
        'Value' : [ rescaleSlope ] };
        
    item[dicomifier.dictionary['RescaleType'][1]] = {
        'vr': dicomifier.dictionary['RescaleType'][0], 
        'Value' : [ 'US' ] };
    
    dicomSequenceItem[dicomifier.dictionary['PixelValueTransformationSequence'][1]] = {
        'vr': dicomifier.dictionary['PixelValueTransformationSequence'][0], 
        'Value' : [ item ] };
};
