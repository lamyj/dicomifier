require('bruker2dicom/common.js');

var _module = namespace('dicomifier.bruker2dicom.functionalGroups');

_module.PixelMeasures = function(indexGenerator, dicomSequenceItem, 
                                 brukerDataset) {
    var toDicom = dicomifier.bruker2dicom.toDicom;
    
    var item = {};
    
    toDicom(
        indexGenerator, item, 'PixelSpacing',
        brukerDataset, null, 1, undefined,
        function(brukerDataset) {
            return brukerDataset.VisuCoreExtent.map(function(x, i) {
                return x/brukerDataset.VisuCoreSize[i]; } ); } );
    
    toDicom(
        indexGenerator, item, 'SliceThickness',
        brukerDataset, 'VisuCoreFrameThickness', 1);
    
    dicomSequenceItem[dicomifier.dictionary['PixelMeasuresSequence'][1]] = {
        'vr': dicomifier.dictionary['PixelMeasuresSequence'][0], 
        'Value' : [ item ] };
};
