require('bruker2dicom/frame_index_generator.js');
require('bruker2dicom/modules/patient.js');
require('bruker2dicom/modules/study.js');
require('bruker2dicom/modules/series.js');
require('bruker2dicom/modules/frame_of_reference.js');
require('bruker2dicom/modules/equipment.js');
require('bruker2dicom/modules/image.js');

var _module = namespace('dicomifier.bruker2dicom');

_module.MRImageStorage = function(brukerDataset) {
    
    if(brukerDataset.VisuCoreDim == 3) {
        _module.to2D(brukerDataset);
    }
    
    var frameGroups = dicomifier.bruker2dicom.getFrameGroups(brukerDataset);
    var indexGenerator =
        new dicomifier.bruker2dicom.FrameIndexGenerator(frameGroups);

    var conversionInfo = convertPixelDataToDicom(
        brukerDataset, indexGenerator.countMax);
    var pixelData = conversionInfo[0];
    var resampled = conversionInfo[1];
    var rescaleSlope = conversionInfo[2];
    var rescaleIntercept = conversionInfo[3];

    var modules = dicomifier.bruker2dicom.modules;

    var output = [];
    while(!indexGenerator.done()) {
        var dicomDataset = {};

        modules.Patient(indexGenerator, dicomDataset, brukerDataset);

        modules.GeneralStudy(indexGenerator, dicomDataset, brukerDataset);
        modules.PatientStudy(indexGenerator, dicomDataset, brukerDataset);

        modules.GeneralSeries(indexGenerator, dicomDataset, brukerDataset);

        modules.FrameOfReference(indexGenerator, dicomDataset, 
                                 brukerDataset);

        modules.GeneralEquipment(indexGenerator, dicomDataset, 
                                 brukerDataset);

        modules.GeneralImage(indexGenerator, dicomDataset, brukerDataset);
        modules.ImagePlane(indexGenerator, dicomDataset, brukerDataset);
        modules.ImagePixel(
            indexGenerator, dicomDataset, brukerDataset, pixelData);
        modules.MRImage(indexGenerator, dicomDataset, brukerDataset);
        modules.SOPCommon(indexGenerator, dicomDataset, brukerDataset, 
                          '1.2.840.10008.5.1.4.1.1.4');

        output[indexGenerator.currentStep] = dicomDataset;

        indexGenerator.next();
    }

    return output;
};

_module.to2D = function(brukerDataset) {
    if(brukerDataset.VisuFGOrderDescDim !== undefined) {
        throw new dicomifier.Exception(
            'Cannot convert 3D datasets with frame groups');
    }
    
    var origin = brukerDataset.VisuCorePosition;
    var z = brukerDataset.VisuCoreOrientation.slice(6, 9);
    var dz = brukerDataset.VisuCoreExtent[2]/brukerDataset.VisuCoreSize[2];
    
    var sliceCount = brukerDataset.VisuCoreSize[2];
    
    // 1. Constant fields
    brukerDataset.VisuCoreDim = [2];
    brukerDataset.VisuCoreFrameCount = [sliceCount];
    brukerDataset.VisuFGOrderDescDim = [1];
    brukerDataset.VisuFGOrderDesc = [[sliceCount, 'FG_SLICE', '', 0, 2]];
    brukerDataset.VisuGroupDepVals = [
        ['VisuCoreOrientation', 0], 
        ['VisuCorePosition', 0] ];
    
    // 2. Sliced fields: subsets of original fields
    var slicedFields = [
        'VisuCoreSize', 'VisuCoreDimDesc', 'VisuCoreExtent', 'VisuCoreUnits'];
    slicedFields.forEach(function(name) {
        brukerDataset[name] = brukerDataset[name].slice(0, 2);
    });
    
    // 3. Repeated fields: repeat the same value for each slice
    var repeatedFields = {
        'VisuCoreOrientation': null,
        'VisuCoreDataMin': null,
        'VisuCoreDataMax': null,
        'VisuCoreDataOffs': null,
        'VisuCoreDataSlope': null,
    };
    Object.keys(repeatedFields).forEach(function(name) {
        repeatedFields[name] = brukerDataset[name];
    });
    
    // Start at one, since the first entry is already there
    for(var i=1; i<sliceCount; ++i) {
        Object.keys(repeatedFields).forEach(function(name) {
            var value = repeatedFields[name];
            if(value !== undefined) {
                brukerDataset[name] = brukerDataset[name].concat(value);
            }
        });
    }
    
    // 4. Special case: position, depending on origin, dz and z
    for(var i=1; i<sliceCount; ++i) {
        var position = origin.map(function(currentValue, index, array) {
            return currentValue+i*dz*z[index];
        });
        brukerDataset['VisuCorePosition'] = 
            brukerDataset['VisuCorePosition'].concat(position);
    }
}
