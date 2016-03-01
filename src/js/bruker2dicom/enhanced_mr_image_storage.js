require('bruker2dicom/frame_index_generator.js');
require('bruker2dicom/modules/patient.js');
require('bruker2dicom/modules/study.js');
require('bruker2dicom/modules/series.js');
require('bruker2dicom/modules/frame_of_reference.js');
require('bruker2dicom/modules/equipment.js');
require('bruker2dicom/modules/image.js');

var _module = namespace('dicomifier.bruker2dicom');

_module.EnhancedMRImageStorage = function(brukerDataset) {
    var frameGroups = dicomifier.bruker2dicom.getFrameGroups(brukerDataset);
    var indexGenerator = 
            new dicomifier.bruker2dicom.FrameIndexGenerator(frameGroups);

    var conversionInfo = convertPixelDataToDicom(brukerDataset);
    var pixelData = conversionInfo[0];
    var resampled = conversionInfo[1];
    var rescaleSlope = conversionInfo[2];
    var rescaleIntercept = conversionInfo[3];

    var modules = dicomifier.bruker2dicom.modules;
    
    // TODO: use DCMTKPP dictionary instead of DCMTK dictionary
    // missing fields
    dicomifier.dictionary['FrameAcquisitonDateTime'] = [ "DT", "00189074" ];
    
    var dicomDataset = {};
    modules.Patient(indexGenerator, dicomDataset, brukerDataset);

    modules.GeneralStudy(indexGenerator, dicomDataset, brukerDataset);
    modules.PatientStudy(indexGenerator, dicomDataset, brukerDataset);
    
    modules.GeneralSeries(indexGenerator, dicomDataset, brukerDataset);
    
    modules.FrameOfReference(indexGenerator, dicomDataset, brukerDataset);
    
    modules.GeneralEquipment(indexGenerator, dicomDataset, brukerDataset);
    
    modules.ImagePixel(indexGenerator, dicomDataset, brukerDataset, pixelData);
    modules.AcquisitionContext(indexGenerator, dicomDataset, brukerDataset);
    modules.EnhancedMRImage(indexGenerator, dicomDataset, brukerDataset);
    modules.MRPulseSequence(indexGenerator, dicomDataset, brukerDataset);
    modules.SOPCommon(indexGenerator, dicomDataset, brukerDataset, 
                      '1.2.840.10008.5.1.4.1.1.4.1');
    modules.MultiFrameFunctionalGroups(
        indexGenerator, dicomDataset, brukerDataset,
        rescaleIntercept, rescaleSlope);
                                       
    // Sort PixelData by stacks
    var sliceNumbers = [];
    for (var index = 0; 
         index < dicomDataset[dicomifier.
            dictionary['PerFrameFunctionalGroupsSequence'][1]].Value.length; 
         ++index) {
        var item = dicomDataset[dicomifier.
            dictionary['PerFrameFunctionalGroupsSequence'][1]].
                Value[index][dicomifier.dictionary['FrameContentSequence'][1]].
                    Value[0];
        
        sliceNumbers.push(
            item[dicomifier.dictionary['DimensionIndexValues'][1]].Value);
    }
    var sortedSliceNumbers = {};
    for (var index = 0; index < sliceNumbers.length; ++index) {
        if (sortedSliceNumbers[String(sliceNumbers[index][0])] === undefined) {
            sortedSliceNumbers[String(sliceNumbers[index][0])] = [];
        }
        sortedSliceNumbers[String(sliceNumbers[index][0])].push(
            [sliceNumbers[index][1], index]);
    }
    
    var keys = Object.keys(sortedSliceNumbers);
    
    var sortedSlice = [];
    for (var index = 0; index < keys.length; ++index) {
        for (var i = 0; i < sortedSliceNumbers[keys[index]].length; ++i) {
            sortedSlice.push(sortedSliceNumbers[keys[index]][i][1]);
        }
    }
    
    dicomDataset[dicomifier.dictionary['PixelData'][1]].InlineBinary = 
        sortPixelData(brukerDataset, sortedSlice);
    
    var output = [];
    output[0] = dicomDataset;
    return output;
};
