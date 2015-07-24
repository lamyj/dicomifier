
dicomifier.Exception = function(message) {
    this.message = message;
}
dicomifier.Exception.prototype = new Error;

function divideArray(array1, array2) {
    var array = new Array();
    for (var index = 0; index < array1.length; ++index) {
        array[index] = array1[index] / array2[index];
    }
    return array;
}

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

function toDicom(dataset, element, value, type, action) {
    var vrAndTag = dicomifier.dictionary[element];

    if (vrAndTag === undefined) {
        throw new dicomifier.Exception('Unknown DICOM element: "' +
                                      element + '"');
    }

    if (value === undefined) {
        if (type === 1) {
            // Must be present, may not be empty
            throw new dicomifier.Exception(
                'DICOM element "' + element + '" must not be empty');
        }
        else if (type === 2) {
            // Must be present, may be empty
            dataset[vrAndTag[1]] = { 'vr' : vrAndTag[0] };
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
            if (action !== undefined) {
                value = value.map(action);
            }

            if(vrAndTag[0] === 'PN') {
                value = value.map(function(x) 
                                    { return { "Alphabetic" : x }; });
            }
    
            dicomDataset[vrAndTag[1]]['Value'] = value;
        }
    }
}
