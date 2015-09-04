require('bruker2dicom/common.js');

var _module = namespace('dicomifier.bruker2dicom.functionalGroups');

_module.FrameAnatomy = function(indexGenerator, dicomSequenceItem, 
                                brukerDataset) {
    var item = {};
    
    item[dicomifier.dictionary['FrameLaterality'][1]] = {
        'vr': dicomifier.dictionary['FrameLaterality'][0], 
        'Value' : [ 'B' ] };
        
    var itemAnatomicRegion = {};
    
    itemAnatomicRegion[dicomifier.dictionary['CodeValue'][1]] = {
        'vr': dicomifier.dictionary['CodeValue'][0], 
        'Value' : [ 'T-D0010' ] };
    
    itemAnatomicRegion[dicomifier.dictionary['CodingSchemeDesignator'][1]] = {
        'vr': dicomifier.dictionary['CodingSchemeDesignator'][0], 
        'Value' : [ 'SRT' ] };
    
    itemAnatomicRegion[dicomifier.dictionary['CodeMeaning'][1]] = {
        'vr': dicomifier.dictionary['CodeMeaning'][0], 
        'Value' : [ 'Entire body' ] };
        
    item[dicomifier.dictionary['AnatomicRegionSequence'][1]] = {
        'vr': dicomifier.dictionary['AnatomicRegionSequence'][0], 
        'Value' : [ itemAnatomicRegion ] };
    
    dicomSequenceItem[dicomifier.dictionary['FrameAnatomySequence'][1]] = {
        'vr': dicomifier.dictionary['FrameAnatomySequence'][0], 
        'Value' : [ item ] };
};
