Object.prototype.equals = function(object2) {
    //For the first loop, we only check for types
    for (propName in this) {
        //Check for inherited methods and properties - like .equals itself
        //https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Object/hasOwnProperty
        //Return false if the return value is different
        if (this.hasOwnProperty(propName) != object2.hasOwnProperty(propName)) {
            return false;
        }
        //Check instance type
        else if (typeof this[propName] != typeof object2[propName]) {
            //Different types => not equal
            return false;
        }
    }
    //Now a deeper check using other objects property names
    for(propName in object2) {
        //We must check instances anyway, there may be a property that only exists in object2
            //I wonder, if remembering the checked values from the first loop would be faster or not 
        if (this.hasOwnProperty(propName) != object2.hasOwnProperty(propName)) {
            return false;
        }
        else if (typeof this[propName] != typeof object2[propName]) {
            return false;
        }
        //If the property is inherited, do not check any more (it must be equa if both objects inherit it)
        if(!this.hasOwnProperty(propName))
          continue;

        //Now the detail check and recursion

        //This returns the script back to the array comparing
        /**REQUIRES Array.equals**/
        if (this[propName] instanceof Array && object2[propName] instanceof Array) {
                   // recurse into the nested arrays
           if (!this[propName].equals(object2[propName]))
                        return false;
        }
        else if (this[propName] instanceof Object && object2[propName] instanceof Object) {
                   // recurse into another objects
                   //console.log("Recursing to compare ", this[propName],"with",object2[propName], " both named \""+propName+"\"");
           if (!this[propName].equals(object2[propName]))
                        return false;
        }
        //Normal value comparison for strings and numbers
        else if(this[propName] != object2[propName]) {
           return false;
        }
    }
    //If everything passed, let's say YES
    return true;
}

// attach the .equals method to Array's prototype to call it on any array
Array.prototype.equals = function (array) {
    // if the other array is a falsy value, return
    if (!array)
        return false;

    // compare lengths - can save a lot of time 
    if (this.length != array.length)
        return false;

    for (var i = 0, l=this.length; i < l; i++) {
        // Check if we have nested arrays
        if (this[i] instanceof Array && array[i] instanceof Array) {
            // recurse into the nested arrays
            if (!this[i].equals(array[i]))
                return false;       
        }
        else if (this[i] instanceof Object && array[i] instanceof Object) {
            // use .equals function of Object
            if (!this[i].equals(array[i]))
                return false; 
        }
        else if (this[i] != array[i]) { 
            // Warning - two different object instances will never 
            // be equal: {x:20} != {x:20}
            return false;   
        }           
    }       
    return true;
}

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
        // Value should be an array
        if ((value instanceof Array) == false)
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
