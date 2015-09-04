require('bruker2dicom/common.js');

var _module = namespace('dicomifier.bruker2dicom.functionalGroups');

_module.MRModifier = function(indexGenerator, dicomSequenceItem, 
                              brukerDataset) {
    var item = {};
    
    item[dicomifier.dictionary['InversionRecovery'][1]] = {
        'vr': dicomifier.dictionary['InversionRecovery'][0], 
        'Value' : [ 'NO' ] }; // TODO
        
    if (item[dicomifier.dictionary['InversionRecovery'][1]]['Value'][0] === 'NO') {
        item[dicomifier.dictionary['InversionTimes'][1]] = {
            'vr': dicomifier.dictionary['InversionTimes'][0], 
            'Value' : [ 0 ] }; // TODO
    }
    
    item[dicomifier.dictionary['FlowCompensation'][1]] = {
        'vr': dicomifier.dictionary['FlowCompensation'][0], 
        'Value' : [ 'NONE' ] }; // TODO
        
    if (item[dicomifier.dictionary['FlowCompensation'][1]]['Value'][0] !== 'NONE') {
        item[dicomifier.dictionary['FlowCompensationDirection'][1]] = {
            'vr': dicomifier.dictionary['FlowCompensationDirection'][0], 
            'Value' : [ 'OTHER' ] }; // TODO
    }
    
    // Spoiling
    //item[dicomifier.dictionary['Spoiling'][1]] = {
    //    'vr': dicomifier.dictionary['Spoiling'][0], 
    //    'Value' : [ 'NONE' ] }; // TODO
    
    item[dicomifier.dictionary['T2Preparation'][1]] = {
        'vr': dicomifier.dictionary['T2Preparation'][0], 
        'Value' : [ 'NO' ] }; // TODO
        
    item[dicomifier.dictionary['SpectrallySelectedExcitation'][1]] = {
        'vr': dicomifier.dictionary['SpectrallySelectedExcitation'][0], 
        'Value' : [ 'NONE' ] }; // TODO

    item[dicomifier.dictionary['SpatialPresaturation'][1]] = {
        'vr': dicomifier.dictionary['SpatialPresaturation'][0], 
        'Value' : [ 'NONE' ] }; // TODO
        
    item[dicomifier.dictionary['PartialFourier'][1]] = {
        'vr': dicomifier.dictionary['PartialFourier'][0], 
        'Value' : [ 'NO' ] }; // TODO
        
    if (item[dicomifier.dictionary['PartialFourier'][1]]['Value'][0] === 'YES') {
        item[dicomifier.dictionary['PartialFourierDirection'][1]] = {
            'vr': dicomifier.dictionary['PartialFourierDirection'][0], 
            'Value' : [ 'COMBINATION' ] }; // TODO
    }
    
    item[dicomifier.dictionary['ParallelAcquisition'][1]] = {
        'vr': dicomifier.dictionary['ParallelAcquisition'][0], 
        'Value' : [ 'NO' ] }; // TODO
        
    if (item[dicomifier.dictionary['ParallelAcquisition'][1]]['Value'][0] === 'YES') {
        item[dicomifier.dictionary['ParallelAcquisitionTechnique'][1]] = {
            'vr': dicomifier.dictionary['ParallelAcquisitionTechnique'][0], 
            'Value' : [ 'OTHER' ] }; // TODO
            
        item[dicomifier.dictionary['ParallelReductionFactorInPlane'][1]] = {
            'vr': dicomifier.dictionary['ParallelReductionFactorInPlane'][0], 
            'Value' : [ '0' ] }; // TODO
            
        item[dicomifier.dictionary['ParallelReductionFactorOutOfPlane'][1]] = {
            'vr': dicomifier.dictionary['ParallelReductionFactorOutOfPlane'][0], 
            'Value' : [ '0' ] }; // TODO
            
        item[dicomifier.dictionary['ParallelReductionFactorSecondInPlane'][1]] = {
            'vr': dicomifier.dictionary['ParallelReductionFactorSecondInPlane'][0], 
            'Value' : [ '0' ] }; // TODO
    }
    
    dicomSequenceItem[dicomifier.dictionary['MRModifierSequence'][1]] = {
        'vr': dicomifier.dictionary['MRModifierSequence'][0], 
        'Value' : [ item ] };
};
