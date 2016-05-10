GeneralSeries = [ #http://dicom.nema.org/medical/dicom/current/output/chtml/part03/sect_C.7.3.html#sect_C.7.3.1
    (None, "Modality", 1, lambda d,g,i: ["MR"], None),
    ("VisuUid", "SeriesInstanceUID", 1, None, None),
    (
        None, "SeriesNumber", 2, 
        lambda d,g,i: d.get("VisuExperimentNumber") or d.get("VisuSeriesNumber"),
        None
    ),
    ("VisuSeriesDate", "SeriesDate", 3, None, None),
    ("VisuSeriesDate", "SeriesTime", 3, None, None),
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
