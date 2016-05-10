import dateutil
import odil

vr_converters = {
    "DA": lambda x: dateutil.parser.parse(x.replace(",", ".")).strftime("%Y%m%d"),
    "DS": lambda x: float(x),
    "FD": lambda x: float(x),
    "FL": lambda x: float(x),
    "IS": lambda x: int(x),
    "PN": lambda x: {"Alphabetic": x},
    "TM": lambda x: dateutil.parser.parse(x.replace(",", ".")).strftime("%H%M%S"),
}

def convert_element(
        bruker_data_set, dicom_data_set, 
        bruker_name, dicom_name, type_, getter, setter,
        frame_index, generator, vr_finder):
    value = None
    if getter is not None:
        if isinstance(getter, basestring):
            value = getter
        else:
            value = getter(bruker_data_set, generator, frame_index)
    else:
        value = bruker_data_set.get(bruker_name)

    if bruker_name in generator.dependent_fields:
        group_index = [
            index for index, x in enumerate(generator.frame_groups) 
            if bruker_name in x[2]][0]
        value = [ value[frame_index[group_index]] ]

    tag = getattr(odil.registry, dicom_name)
    vr = str(vr_finder(tag))

    if value is None:
        if type_ == 1:
            raise Exception("{} must be present".format(dicom_name))
        elif type_ == 2:
            dicom_data_set[str(tag)] = {"vr": vr}
        elif type_ == 3:
            # May be absent
            pass
    else:
        dicom_data_set[str(tag)] = {"vr": vr}
        if isinstance(setter, dict):
            value = [setter[x] for x in value]
        elif setter is not None:
            value = setter(value)
        
        vr_converter = vr_converters.get(vr)
        if vr_converter is not None:
            value = [vr_converter(x) for x in value]
        
        if vr in ["OB", "OD", "OF", "OL", "OW"]:
            dicom_data_set[str(tag)]["InlineBinary"] = value[0]
        else:
            dicom_data_set[str(tag)]["Value"] = value
    
    return value
