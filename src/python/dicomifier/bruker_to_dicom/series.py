#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

def _get_series_number(data_set, generator, index):
    if "VisuSeriesNumber" in data_set:
        series_number = int(data_set["VisuSeriesNumber"][0])
    else:
        # cf. ParaVision Parameters, 2.4.11.6
        experiment = int(data_set["VisuExperimentNumber"][0])
        processing = int(data_set["VisuProcessingNumber"][0])
        series_number = (experiment * 2**16)+processing
    
    return [series_number]

GeneralSeries = [ #http://dicom.nema.org/medical/dicom/current/output/chtml/part03/sect_C.7.3.html#sect_C.7.3.1
    (None, "Modality", 1, lambda d,g,i: ["MR"], None),
    ("VisuUid", "SeriesInstanceUID", 1, None, None),
    (None, "SeriesNumber", 2, _get_series_number, None),
    (
        None, "SeriesDate", 3,
        lambda d,g,i: d.get("VisuSeriesDate") or d.get("VisuAcqDate"),
        None
    ),
    (
        None, "SeriesTime", 3,
        lambda d,g,i: d.get("VisuSeriesDate") or d.get("VisuAcqDate"),
        None
    ),
    ("OWNER", "PerformingPhysicianName", 3, None, None),
    ("VisuAcquisitionProtocol", "ProtocolName", 3, None, None),
    ("VisuAcquisitionProtocol", "SeriesDescription", 3, None, None),
    (
        "VisuSubjectPosition", "PatientPosition", 2, None,
        {
            "Head_Supine": "HFS", "Head_Prone": "HFP",
            "Head_Left" : "HFDL", "Head_Right": "HFDR",
            "Foot_Supine": "FFS", "Foot_Prone": "FFP",
            "Foot_Left": "FFDL", "Foot_Right": "FFDR" 
        }
    ),
    ("VisuSubjectType", "AnatomicalOrientationType", 3, None, None),
]
