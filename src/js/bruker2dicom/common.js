require("common.js");
require("bruker2dicom/frame_index_generator.js");

var _module = namespace('dicomifier.bruker2dicom');

/**
 * @brief Map a source value using a dictionary, throw an exception if the value
 * is not in the dictionary.
 */
_module.dictionaryMapper = function(dictionary) {
    return function(x) {
        var mapped = dictionary[x];
        if(mapped === undefined) {
            throw new dicomifier.Exception('Unknown value: "' + x + '"');
        }
        return mapped;
    };
};

/**
 * @brief Convert Bruker date or time format into DICOM format
 * @param type: output type ('date' or 'time')
 */
_module.dateTimeMapper = function(type) {
    return function(x) {
        var datetime = new Date(x.replace(',', '.'));
        
        if (datetime.toString() === 'Invalid Date') {
            throw new dicomifier.Exception(
                'Invalid Date: "' + x + '"');
        }

        var format = 123;
        if(type === 'date') {
            format = datetime.getUTCFullYear().toString() +
                ('0' + (datetime.getUTCMonth()+1).toString()).slice(-2) +
                ('0' + datetime.getUTCDate().toString()).slice(-2);
        }
        else if(type === 'time') {
            format = ('0' + datetime.getUTCHours().toString()).slice(-2) +
                ('0' + datetime.getUTCMinutes().toString()).slice(-2) +
                ('0' + datetime.getUTCSeconds().toString()).slice(-2);
        }
        else if(type === 'datetime') {
            format = datetime.getUTCFullYear().toString() +
                ('0' + (datetime.getUTCMonth()+1).toString()).slice(-2) +
                ('0' + datetime.getUTCDate().toString()).slice(-2) +
                ('0' + datetime.getUTCHours().toString()).slice(-2) +
                ('0' + datetime.getUTCMinutes().toString()).slice(-2) +
                ('0' + datetime.getUTCSeconds().toString()).slice(-2);
        }
        else {
            throw new dicomifier.Exception(
                'Unknown DateTime format: "' + format + '"');
        }

        return format;
    }
};

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
_module.toDicom = function(
        indexGenerator, dicomDataset, element, brukerDataset,
        brukerElement, type, setter, getter) {

    var vrAndTag = dicomifier.dictionary[element];

    if(vrAndTag === undefined) {
        throw new dicomifier.Exception(
            'Unknown DICOM element: "' + element + '"');
    }
    
    // Get Bruker Value
    var value = getter;
    if (getter !== undefined) {
        value = getter(brukerDataset);
    }
    else if (brukerElement !== null) {
        value = brukerDataset[brukerElement];
    }

    // Check frame groups
    var frameGroupIndex = dicomifier.bruker2dicom.getFrameGroupIndex(
        brukerDataset, brukerElement);
    if (frameGroupIndex !== null) {
        value = value[indexGenerator.currentIndex[frameGroupIndex[0]] +
                      frameGroupIndex[1]];
        // Value should be an array
        if(!(value instanceof Array))
        {
            value = [ value ];
        }
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
            throw dicomifier.Exception(
                'Unknown DICOM element type: "' +type+'"');
        }
    }
    else {
        dicomDataset[vrAndTag[1]] = { 'vr': vrAndTag[0] };
        if (value !== null) {
            if (setter !== undefined) {
                value = value.map(setter);
            }

            if(vrAndTag[0] === 'PN') {
                value = value.map(function(x) { return { "Alphabetic" : x }; });
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
};
