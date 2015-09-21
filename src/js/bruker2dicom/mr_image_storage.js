require('bruker2dicom/frame_index_generator.js');
require('bruker2dicom/modules/patient.js');
require('bruker2dicom/modules/study.js');
require('bruker2dicom/modules/series.js');
require('bruker2dicom/modules/frame_of_reference.js');
require('bruker2dicom/modules/equipment.js');
require('bruker2dicom/modules/image.js');

var _module = namespace('dicomifier.bruker2dicom');

_module.MRImageStorage = function(brukerDataset) {
    var frameGroups = dicomifier.bruker2dicom.getFrameGroups(brukerDataset);
    var indexGenerator = 
        new dicomifier.bruker2dicom.FrameIndexGenerator(frameGroups);
    var pixelData = loadPixelData(brukerDataset, indexGenerator.countMax, 
                                  false);

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
        modules.ImagePixel(indexGenerator, dicomDataset, brukerDataset, 
                           pixelData[0]);
        modules.MRImage(indexGenerator, dicomDataset, brukerDataset);
        modules.SOPCommon(indexGenerator, dicomDataset, brukerDataset, 
                          '1.2.840.10008.5.1.4.1.1.4');

        output[indexGenerator.currentStep] = dicomDataset;

        indexGenerator.next();
    }

    return output;
};
