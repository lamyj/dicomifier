require('bruker2dicom/common.js');

var _module = namespace('dicomifier.bruker2dicom.functionalGroups');

_module.MRImageFrameType = function(indexGenerator, dicomSequenceItem, 
                                    brukerDataset) {
    var toDicom = dicomifier.bruker2dicom.toDicom;
    var dictionaryMapper = dicomifier.bruker2dicom.dictionaryMapper;
    
    var item = {};
    
    item[dicomifier.dictionary['FrameType'][1]] = {
        'vr': dicomifier.dictionary['FrameType'][0],
        'Value': [ 'ORIGINAL', 'PRIMARY' ] };
        
    item[dicomifier.dictionary['PixelPresentation'][1]] = {
        'vr': dicomifier.dictionary['PixelPresentation'][0],
        'Value': [ 'MONOCHROME' ] };
        
    item[dicomifier.dictionary['VolumetricProperties'][1]] = {
        'vr': dicomifier.dictionary['VolumetricProperties'][0],
        'Value': [ 'VOLUME' ] };
        
    item[dicomifier.dictionary['VolumeBasedCalculationTechnique'][1]] = {
        'vr': dicomifier.dictionary['VolumeBasedCalculationTechnique'][0],
        'Value': [ 'NONE' ] };
        
    toDicom(
        indexGenerator, item, 'ComplexImageComponent',
        brukerDataset, 'VisuCoreFrameType', 1,
        dictionaryMapper({ 'MAGNITUDE_IMAGE': 'MAGNITUDE', 'PHASE_IMAGE': 'PHASE', 
                           'REAL_IMAGE': 'REAL', 'IMAGINARY_IMAGE': 'IMAGINARY', 
                           'MIXED_IMAGE': 'MIXED' }));
        
    item[dicomifier.dictionary['AcquisitionContrast'][1]] = {
        'vr': dicomifier.dictionary['AcquisitionContrast'][0],
        'Value': [ 'UNKNOWN' ] };
    
    dicomSequenceItem[dicomifier.dictionary['MRImageFrameTypeSequence'][1]] = {
        'vr': dicomifier.dictionary['MRImageFrameTypeSequence'][0], 
        'Value' : [ item ] };
};
