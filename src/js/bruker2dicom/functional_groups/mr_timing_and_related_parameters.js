require('bruker2dicom/common.js');

var _module = namespace('dicomifier.bruker2dicom.functionalGroups');

_module.MRTimingAndRelatedParameters = function(indexGenerator, 
                                                dicomSequenceItem, 
                                                brukerDataset) {
    var toDicom = dicomifier.bruker2dicom.toDicom;
    
    var item = {};
    
    toDicom(
        indexGenerator, item, 'RepetitionTime',
        brukerDataset, 'VisuAcqRepetitionTime', 1);
        
    toDicom(
        indexGenerator, item, 'FlipAngle',
        brukerDataset, 'VisuAcqFlipAngle', 1, parseFloat);
        
    toDicom(
        indexGenerator, item, 'EchoTrainLength',
        brukerDataset, 'VisuAcqEchoTrainLength', 1, parseInt);
        
    item[dicomifier.dictionary['RFEchoTrainLength'][1]] = {
        'vr': dicomifier.dictionary['RFEchoTrainLength'][0],
        'Value': [ 0 ] }; // TODO
        
    item[dicomifier.dictionary['GradientEchoTrainLength'][1]] = {
        'vr': dicomifier.dictionary['GradientEchoTrainLength'][0],
        'Value': [ 0 ] }; // TODO
        
    dicomSequenceItem[dicomifier.dictionary['MRTimingAndRelatedParametersSequence'][1]] = {
        'vr': dicomifier.dictionary['MRTimingAndRelatedParametersSequence'][0], 
        'Value' : [ item ] };
};
