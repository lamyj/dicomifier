
var _module = namespace('dicomifier.dicom2nifti');

_module.getKeys = function(dataset) {
    var keys = {};
    
    // Image Orientation (Patient) (0020,0037)
    var imageOrientation = dataset['00200037'];
    if (imageOrientation !== undefined) {
        keys['00200037'] = imageOrientation['Value'];
    }
    
    // Repetition Time (0018,0080)
    var repetitionTime = dataset['00180080'];
    if (repetitionTime !== undefined) {
        keys['00180080'] = repetitionTime['Value'];
    }
    
    // Echo Time (0018,0081)
    var echoTime = dataset['00180081'];
    if (echoTime !== undefined) {
        keys['00180081'] = echoTime['Value'];
    }
    
    // Inversion Time (0018,0082)
    var inversionTime = dataset['00180082'];
    if (inversionTime !== undefined) {
        keys['00180082'] = inversionTime['Value'];
    }
    
    return keys;
}

var closeEquals = function(x, y) {
    var vect = [];
    for (var i = 0; i < x.length; ++i) {
        vect[i] = x[i] - y[i];
    }
    
    var dist = 0;
    for (var i = 0; i < vect.length; ++i) {
        dist += vect[i] * vect[i];
    }
    
    dist = Math.sqrt(dist);
    
    return (dist < 0.05);
}

_module.findStack = function(stacks, dataset) {
    
    var equalsMapper = { '00200037': closeEquals };
    
    for (var i = 0; i < stacks.length; ++i) {
        var stack = stacks[i][0];
        
        var match = true;
        for (var key in stack) {
            if (stack[key] === undefined) {
                continue;
            }
            
            if (stack[key] instanceof Function) { 
                continue; 
            }
            
            // Missing field
            if (dataset[key] === undefined) {
                match = false;
                break;
            }
            
            if (equalsMapper[key] !== undefined && 
                ! equalsMapper[key](stack[key], dataset[key]['Value']) ||
                ! stack[key].equals(dataset[key]['Value'])) {
                match = false;
                break;
            }
        }
        
        // Find stack
        if (match === true) {
            return i;
        }
    }
    
    // not find
    return null;
}


_module.distance = function(position, normal) {
    var sum = 0;
    for (var i = 0; i < position.length; ++i) {
        sum += position[i] * normal[i];
    }
    
    return sum;
}
    
_module.sortStack = function(datasets) {
    // if only one dataset, nothing to do
    if (datasets.length === 1) {
        return datasets;
    }
    
    // Should contains field 00200032
    datasets.forEach(function(element, index, array) {
                        if (element['00200032'] === undefined || 
                            element['00200032']['Value'] === undefined || 
                            element['00200032']['Value'] === null) {
                        throw new dicomifier.Exception("Image Position Patient is not in DataSet");
                        }
                     });
                     
    // Compute normal from image_orientation_patient
    var v1 = datasets[0]['00200037']['Value'].slice(0, 3);
    var v2 = datasets[0]['00200037']['Value'].slice(3);
    var normal = [ v1[1] * v2[2] - v1[2] * v2[1], 
                   v1[2] * v2[0] - v1[0] * v2[2], 
                   v1[0] * v2[1] - v1[1] * v2[0] ];
                   
    // Compute distance for each frame
    var distances = [];
    for (var i = 0; i < datasets.length; ++i) {
        distances.push( [ dicomifier.dicom2nifti.distance(datasets[i]['00200032']['Value'], normal), datasets[i] ] );
    }
    
    // Sort frame by distance
    distances.sort(function(a,b) { return a[0] - b[0]; });
    
    // Create sorted stack
    var newStack = [];
    for (var i = 0; i < distances.length; ++i) {
        newStack.push(distances[i][1]);
    }
    
    return newStack;
}

_module.mergeStack = function(datasets, dictionaryTagToName) {
    var finalDataset = {};
    for (var dsIndex = 0; dsIndex < datasets.length; ++dsIndex) {
        for (var key in datasets[dsIndex]) {
            if (datasets[dsIndex][key] instanceof Function) { 
                continue; 
            }
            
            // ignore unknown keys
            if (dictionaryTagToName[key] === undefined) {
                continue;
            }
            
            if (finalDataset[dictionaryTagToName[key]] === undefined) {
                finalDataset[dictionaryTagToName[key]] = [];
            }
            
            // Store each PixelData
            if (key === '7fe00010') {
                finalDataset[dictionaryTagToName[key]].push(datasets[dsIndex][key]['InlineBinary']); 
            }
            else {
                finalDataset[dictionaryTagToName[key]].push(datasets[dsIndex][key]['Value']);
            }
        }
    }
    
    for (var key in finalDataset) {
        if (finalDataset[key] instanceof Function) { 
            continue; 
        }
        
        // PixelData: nothing to do
        if (key === 'PixelData') {
            continue;
        }
        
        // ImagePositionPatient: don't merge (error if only one dataset)
        if (key === 'ImagePositionPatient') {
            continue;
        }
        
        if (finalDataset[key].every(function(element, indice, array) { if (array[0] instanceof Array) { return array[0].equals(element); } else { return array[0] === element; } })) {
            finalDataset[key] = finalDataset[key][0];
        }
        else {
            log('Cannot not merge element ' + key + ' = ' + JSON.stringify(finalDataset[key]));
        }
    }
    
    return finalDataset;
}
