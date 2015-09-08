require("common.js");
require("dicom2nifti/common.js");

var _module = namespace('dicomifier.dicom2nifti');

_module.convert = function(datasetlist, dimension) {
    if (datasetlist.length === 0) {
        throw new dicomifier.Exception("Missing input");
    }
    
    var listMRImageStorage = new Array();
    var listEnhancedMRImageStorage = new Array();
    for (var index = 0; index < datasetlist.length; ++index) {
        var sopClassUID = '';
        if (datasetlist[index]['00080016'] !== undefined && 
            datasetlist[index]['00080016']['Value'] !== undefined &&
            datasetlist[index]['00080016']['Value'].length > 0) {
            sopClassUID = datasetlist[index]['00080016']['Value'][0];
        }
        
        if (sopClassUID === '1.2.840.10008.5.1.4.1.1.4' ) {
            // MRImageStorage
            listMRImageStorage.push(datasetlist[index]);
        }
        else if (sopClassUID === '1.2.840.10008.5.1.4.1.1.4.1' ) {
            // EnhancedMRImageStorage
            listEnhancedMRImageStorage.push(datasetlist[index]);
        }
        else {
            log('Unknown SOPClassUID. Ignore Dataset', 'ERROR');
        }
    }

    // convert dicomifier.dictionary
    var dictionaryTagToName = {};
    for (var key in dicomifier.dictionary) {
        dictionaryTagToName[dicomifier.dictionary[key][1]] = key;
    }
    
    var output = [];
    
    // Process MRImageStorage
    if (listMRImageStorage.length > 0) {
        output = _module.processMRImageStorage(listMRImageStorage, 
                                               dimension, 
                                               dictionaryTagToName);
    }
    
    // Process EnhancedMRImageStorage
    //for (var i = 0; i < listEnhancedMRImageStorage.length; ++i) {
    if (listEnhancedMRImageStorage.length > 0) {
        output = _module.processMRImageStorage(listEnhancedMRImageStorage, 
                                               dimension, 
                                               dictionaryTagToName);
    }
    
    // Fusion stack
    if (dimension === 4) {
        if (dicomifier.dicom2nifti.is_synchronized(output)) {
            return dicomifier.dicom2nifti.mergeAllStacks(output);
        }
    }

    // Return output
    return output;
}

_module.processMRImageStorage = function(datasetlist, dimension, 
                                         dictionaryTagToName) {
    var count = 0;
    var currentDataset = datasetlist[count];
    var dictionary = new Array();
    // Create the stacks
    while (currentDataset !== undefined) {
        // Get stack keys
        var dataset_key = dicomifier.dicom2nifti.getKeys(currentDataset);
        
        // Get stack index
        var indexStack = dicomifier.dicom2nifti.findStack(dictionary, 
                                                          currentDataset);
        
        // If stack not found
        if (indexStack === null) {
            indexStack = dictionary.length;
            // Create a new stack
            dictionary.push([dataset_key, []]);
        }
        
        // Add to the stack
        dictionary[indexStack][1].push(currentDataset);
        
        ++count;
        currentDataset = datasetlist[count];
    }

    // Sort Dataset in each Stack
    var output = [];
    for (var stackIndex = 0; stackIndex < dictionary.length; ++stackIndex) {
        dictionary[stackIndex][1] = 
            dicomifier.dicom2nifti.sortStack(dictionary[stackIndex][1]);
        
        // Fusion image in stack
        output[stackIndex] = 
            dicomifier.dicom2nifti.mergeStack(dictionary[stackIndex][1], 
                                              dictionaryTagToName);
    }
    
    return output;
}

_module.processEnhancedMRImageStorage = function(dataset, dimension, 
                                                 dictionaryTagToName) {
    throw new dicomifier.Exception("Not implemented yet");
}
