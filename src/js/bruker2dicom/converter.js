require("common.js");
require("bruker2dicom/common.js");
require("bruker2dicom/mr_image_storage.js");
require("bruker2dicom/enhanced_mr_image_storage.js");

var _module = namespace('dicomifier.bruker2dicom');

_module.convert = function(brukerDirectory, studyNumber, seriesNumber, SOPClassUID, outputdir) {
    var brukerDataset = readBrukerDirectory(brukerDirectory, seriesNumber);
    
    var dicomList = [];
    
    // MR Image Storage
    if (SOPClassUID === '1.2.840.10008.5.1.4.1.1.4') {
        dicomList = _module.MRImageStorage(brukerDataset);
    }
    // Enhanced MR Image Storage
    else if (SOPClassUID === '1.2.840.10008.5.1.4.1.1.4.1') {
        dicomList = _module.EnhancedMRImageStorage(brukerDataset);
    }
    else {
        throw new dicomifier.Exception("Unkown SOP Class UID '" + SOPClassUID + "'");
    }
    
    for (var index = 0; index < dicomList.length; ++index) {
        var filename = _module.getFileName(dicomList[index], studyNumber, 
                                           seriesNumber, outputdir, 
                                           SOPClassUID === '1.2.840.10008.5.1.4.1.1.4');
        
        writeDICOM(JSON.stringify(dicomList[index]), filename, '1.2.840.10008.1.2.1');
    }
}
