require('bruker2dicom/common.js');

var _module = namespace('dicomifier.bruker2dicom.functionalGroups');

_module.FrameContent = function(indexGenerator, dicomSequenceItem, 
                                brukerDataset) {
    var toDicom = dicomifier.bruker2dicom.toDicom;
    var dateTimeMapper = dicomifier.bruker2dicom.dateTimeMapper;

    var item = {};
    
    dicomSequenceItem[dicomifier.dictionary['FrameAcquisitionNumber'][1]] = {
        'vr': dicomifier.dictionary['FrameAcquisitionNumber'][0], 
        'Value' : [ indexGenerator.currentStep ] };
    
    toDicom(
        indexGenerator, item, 'FrameReferenceDateTime',
        brukerDataset, 'VisuAcqDate', 1, dateTimeMapper('datetime'));
    
    toDicom(
        indexGenerator, item, 'FrameAcquisitonDateTime',
        brukerDataset, 'VisuAcqDate', 1, dateTimeMapper('datetime'));
        
    var frameAcqDuration = function(brukerDataset) {
        var sliceNumber = brukerDataset['VisuCoreFrameCount'];
        if (brukerDataset.VisuCoreDim !== undefined &&
            brukerDataset.VisuCoreDim[0] === "3") {
            sliceNumber = parseInt(brukerDataset.VisuCoreFrameCount) * 
                          brukerDataset.VisuCoreSize[2]; 
        }
        return [(brukerDataset['VisuAcqScanTime'] / sliceNumber)];
    };
    toDicom(
        indexGenerator, item, 'FrameAcquisitionDuration',
        brukerDataset, null, 1, parseFloat, frameAcqDuration );
    
    var indexOrientation = 
        dicomifier.bruker2dicom.getFrameGroupIndex(brukerDataset, 
                                                   'VisuCoreOrientation');
    var value = [];
    if (indexOrientation === null) {
        value.push(indexGenerator.computeIndex([]) + 1);
        value.push(1);
    }
    else {
        value.push(indexGenerator.computeIndex([indexOrientation[0]]) + 1);
        value.push(indexGenerator.currentIndex[indexOrientation[0]] + 1);
    }
    item[dicomifier.dictionary['DimensionIndexValues'][1]] = {
        'vr': dicomifier.dictionary['DimensionIndexValues'][0], 
        'Value' : value };
        
    item[dicomifier.dictionary['StackID'][1]] = {
        'vr': dicomifier.dictionary['StackID'][0], 
        'Value' : [ String(value[0]) ] };
        
    item[dicomifier.dictionary['InStackPositionNumber'][1]] = {
        'vr': dicomifier.dictionary['InStackPositionNumber'][0], 
        'Value' : [ value[1] ] };
    
    dicomSequenceItem[dicomifier.dictionary['FrameContentSequence'][1]] = {
        'vr': dicomifier.dictionary['FrameContentSequence'][0], 
        'Value' : [ item ] };
};
