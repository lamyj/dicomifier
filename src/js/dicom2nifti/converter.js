require("common.js");
require("dicom2nifti/common.js");

var _module = namespace('dicomifier.dicom2nifti');

_module.convert = function(datasetlist, dimension) {
    var count = 0;

    var currentDataset = datasetlist[count];
    if (currentDataset === undefined) {
        throw new dicomifier.Exception("Missing input");
    }

    // convert dicomifier.dictionary
    var dictionaryTagToName = {};
    for (var key in dicomifier.dictionary) {
        dictionaryTagToName[dicomifier.dictionary[key][1]] = key;
    }

    var dictionary = new Array();
    // Create the stacks
    while (currentDataset !== undefined) {
        // Get stack keys
        var dataset_key = dicomifier.dicom2nifti.getKeys(currentDataset);
        
        // Get stack index
        var indexStack = dicomifier.dicom2nifti.findStack(dictionary, currentDataset);
        
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
        dictionary[stackIndex][1] = dicomifier.dicom2nifti.sortStack(dictionary[stackIndex][1]);
        
        // Fusion image in stack
        output[stackIndex] = dicomifier.dicom2nifti.mergeStack(dictionary[stackIndex][1], dictionaryTagToName);
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
