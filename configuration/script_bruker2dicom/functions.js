
/**
 * @brief Exception class
 */
dicomifier.Exception = function(message) {
    this.message = message;
}
dicomifier.Exception.prototype = new Error;

/**
 * @brief Make a division between 2 arrays
 * @param array1
 * @param array2
 * @return array = [ array1[0] / array2[0], ..., array1[n] / array2[n] ]
 */
function divideArray(array1, array2) {
    var array = new Array();
    for (var index = 0; index < array1.length; ++index) {
        array[index] = 
            parseFloat(array1[index]) / parseFloat(array2[index]);
    }
    return array;
}

/**
 * @brief use a dictionary to convert Bruker field into DICOM field
 * @param dictionary: dictionary to used
 * @return DICOM value
 */
function dictionaryMapper(dictionary) {
    return function(x) {
        var mapped = dictionary[x];
        if (mapped === undefined) {
            // Cannot map value
            throw new dicomifier.Exception('Unknown value: "' + x + '"');
        }
        return mapped;
    };
}

/**
 * @brief Convert Bruker Date-Time format into DICOM format
 * @param format: output format ('date' or 'time')
 * @return date or time into DICOM Format
 */
function dateTimeMapper(format) {
    return function(x) {
        var datetime = new Date(x.replace(',', '.'));
        
        if (format === 'date') {
            return (String(datetime.getUTCFullYear()) +
                   ("0" + String(datetime.getUTCMonth()+1)).slice(-2) +
                   ("0" + String(datetime.getUTCDate())).slice(-2));
        }
        else if (format === 'time') {
            return (("0" + String(datetime.getUTCHours())).slice(-2) +
                    ("0" + String(datetime.getUTCMinutes())).slice(-2) +
                    ("0" + String(datetime.getUTCSeconds())).slice(-2));
        }
        else {
            throw new dicomifier.Exception('Unknown DateTime format: "' +
                                          format + '"');
        }
    }
}

/**
 * @brief Convert Bruker field into DICOM field
 * @param indexGenerator: Generate current index for frame Groups
 * @param dicomDataset: DICOM dataset
 * @param element: Keyword of the DICOM element to add
 * @param brukerDataset: JSON representation of the BrukerDataset
 * @param brukerElement: Name of the Bruker field
 * @param type: type of the DICOM element (1 = mandatory and not empty, 
 *                                         2 = mandatory, 3 = optional)
 * @param setter: action apply to write values into DICOM Dataset
 * @param getter: action apply to read values from BrukerDataset
 */
function toDicom(indexGenerator, dicomDataset, element, brukerDataset, 
                 brukerElement, type, setter, getter) {
    var vrAndTag = dicomifier.dictionary[element];

    if (vrAndTag === undefined) {
        throw new dicomifier.Exception('Unknown DICOM element: "' +
                                      element + '"');
    }
    
    // Get Bruker Value
    var value = undefined;
    if (getter !== undefined) {
        value = getter(brukerDataset);
    }
    else if (brukerElement !== null) {
        value = brukerDataset[brukerElement];
    }

    // Check frame groups
    var frameGroupIndex = dicomifier.getFrameGroupIndex(brukerDataset, 
                                                        brukerElement);
    if (frameGroupIndex !== null) {
        value = value[indexGenerator.currentIndex[frameGroupIndex[0]] + 
                      frameGroupIndex[1]];
    }

    // Set value into DICOM
    if (value === undefined) {
        if (type === 1) {
            // Must be present, may not be empty
            throw new dicomifier.Exception(
                'DICOM element "' + element + '" must not be empty');
        }
        else if (type === 2) {
            // Must be present, may be empty
            dicomDataset[vrAndTag[1]] = { 'vr' : vrAndTag[0] };
        }
        else if (type === 3) {
            // May be absent
        }
        else {
            throw dicomifier.Exception('Unknown DICOM element type: "' +
                                      type+'"');
        }
    }
    else {
        dicomDataset[vrAndTag[1]] = { 'vr': vrAndTag[0] };
        if (value !== null) {
            if (setter !== undefined) {
                value = value.map(setter);
            }

            if(vrAndTag[0] === 'PN') {
                value = value.map(function(x) 
                                    { return { "Alphabetic" : x }; });
            }
    
            if (type === 1 && value.length === 0) {
                // Must be present, may not be empty
                throw new dicomifier.Exception(
                    'DICOM element "' + element + '" must not be empty');
            }
        
            dicomDataset[vrAndTag[1]]['Value'] = value;
        }
        else {
            if (type === 1) {
                // Must be present, may not be empty
                throw new dicomifier.Exception(
                    'DICOM element "' + element + '" must not be empty');
            }
        }
    }
}

function pixelDataToDicom(indexGenerator, dicomDataset, element, 
                          brukerDataset, type) {
    var vrAndTag = dicomifier.dictionary[element];

    if (vrAndTag === undefined) {
        throw new dicomifier.Exception('Unknown DICOM element: "' +
                                      element + '"');
    }
    
    var value = loadPixelData(brukerDataset, indexGenerator.currentStep);

    if (type === 1 && value.length === 0) {
        // Must be present, may not be empty
        throw new dicomifier.Exception(
            'DICOM element "' + element + '" must not be empty');
    }
    
    // Force VR to OW (and not vrAndTag[0] = OB)
    dicomDataset[vrAndTag[1]] = { 'vr': 'OW' };
    dicomDataset[vrAndTag[1]]['InlineBinary'] = value;
}
