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
    var pixelData = loadPixelData(brukerDataset, 
                                  indexGenerator.countMax, true);

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
    
    modules.ImagePixel(indexGenerator, dicomDataset, brukerDataset, 
                       pixelData[0]);
    modules.AcquisitionContext(indexGenerator, dicomDataset, brukerDataset);
    modules.EnhancedMRImage(indexGenerator, dicomDataset, brukerDataset);
    modules.MRPulseSequence(indexGenerator, dicomDataset, brukerDataset);
    modules.SOPCommon(indexGenerator, dicomDataset, brukerDataset, 
                      '1.2.840.10008.5.1.4.1.1.4.1');
    modules.MultiFrameFunctionalGroups(indexGenerator, dicomDataset, 
                                       brukerDataset, pixelData[1], 
                                       pixelData[2]);
    
    var output = [];
    output[0] = dicomDataset;
    return output;
};
