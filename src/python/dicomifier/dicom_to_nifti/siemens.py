#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

import re
import struct

def parse_csa(csa):
    """ Return a dictionary of (tag, items) of the CSA.
    """

    format = ("<"  # Little-endian
              "4s" # SV10
              "4s" # \x04\x03\x02\x01
              "I"  # Number of items
              "I"  # Unknown
        )
    size = struct.calcsize(format)

    version, _, number_of_elements, _ = struct.unpack(format, csa[:size])

    start = size
    content = {}
    for _ in range(number_of_elements) :
        (name, items), size = parse_element(csa, start)
        content[name] = items
        start += size

    return content

def parse_ascconv(mr_phoenix_protocol):
    """ Return the acquisition settings stored in the ASCCONV section of the
        MrPhoenixProtocol field stored in the CSA headers.
    """
    
    ascconv_data = re.search(
            b"### ASCCONV BEGIN(?:.+?)###\s*(.*?)\s*### ASCCONV END ###", 
            mr_phoenix_protocol, flags=re.DOTALL
        ).group(1)
    ascconv = re.findall(
        b"^(\S+)\s*=\s*(.+)$\s*", ascconv_data, flags=re.MULTILINE)
    
    def parse_value(value, name):
        
        if value.startswith(b"0x"):
            return int(value.split()[0], 16)
        elif value.startswith(b"\""):
            return re.findall(br'""(.*)""', value)[0].decode()
        else:
            int_match = re.match(br"^[+-]?\d+$", value)
            float_match = re.match(
                br"""[-+]?       # optional sign 
                    (?=\d|\.\d)    # followed by a number with at least one digit
                    \d*          # optional integer part
                    (\.\d*)?     # optional fractional part
                    (e[-+]?\d+)? # optional exponent
                """, value, flags=re.VERBOSE | re.IGNORECASE)
            if int_match:
                return int(value)
            elif float_match:
                return float(value)
            else:
                raise Exception("Cannot parse {}".format(value))
    
    data = {}
    for key, value in ascconv:
        key = key.decode()
        path = re.split(r"(\.)|\[(\d+)\]", key)
        
        object = data
        leaf = None
        for index in range(len(path)//3):
            child, dot, child_index = path[index*3:(index+1)*3]
            if dot and child:
                object = object.setdefault(child, {})
            elif child_index is not None:
                object = object.setdefault(child, {})
                
                child_index = int(child_index)
                if (index+1)*3 == len(path)-1:
                    leaf = child_index, child
                else:
                    object = object.setdefault(child_index, {})
        
        if leaf is not None:
            object[leaf[0]] = parse_value(value, leaf[1])
        else:
            object[path[-1]] = parse_value(value, path[-1])
    
    return data

def parse_element(csa, start):
    """ Return a pair (name, items), total_size
    """
    format = ("<"   # Little endian
              "64s" # Name
              "I"   # VM
              "2s"  # VR
              "2s"  # Unknown (end of VR ?)
              "I"   # Syngo datatype
              "I"   # Number of items
              "I"   # Unknown
        )
    size = struct.calcsize(format)

    name, vm, vr, _, syngo_datatype, number_of_items, _ = struct.unpack(
        format, csa[start:start+size])
    name = name.split(b"\x00")[0].decode()

    total_size = size
    start += size
    items = []
    for i in range(number_of_items) :
        item, size = parse_item(csa, start)
        if i < vm :
            if vr in [b"DS", b"FL", b"FD"] :
                item = float(item[:-1])
            elif vr in [b"IS", b"SS", b"US", b"SL", b"UL"] :
                item = int(item[:-1])
            items.append(item)
        start += size
        total_size += size

    return (name, items), total_size

def parse_item(csa, start):
    """ Return a pair content, size
    """
    format = ("<"  # Little endian
              "4I" # Length
             )
    header_size = struct.calcsize(format)

    length = struct.unpack(format, csa[start:start+header_size])

    format = ("<"    # Little endian
              "{0}s" # Content
              "{1}s" # Padding (?)
             ).format(length[1], (4-length[1]%4)%4)
    content_size = struct.calcsize(format)
    content, padding = struct.unpack(
        format, csa[start+header_size:start+header_size+content_size])

    return content, header_size+content_size

def parse_protocol(data):
    """ Parse (as a nested dictionary) the ASCII version of protocol data.
    """

    integer_types = [
        "c", "i", "l", "n", "s",
        "uc", "ui", "ul", "un", "us",
    ]
    floating_point_types = ["fl", "d"]
    types = integer_types+floating_point_types+["s", "b", "t"]

    def integer_parser(value):
        return int(value, 16 if value.startswith(b"0x") else 10)

    def floating_point_parser(value):
        return float(value)

    def string_parser(value):
        # Remove beginning and ending quotes
        if all(c==b'"' for c in value):
            return b""
        else:
            return re.match(br"\"*(.*[^\"])\"*", value).group(1)

    def value_parser(type_, value):
        if type_ == b"b":
            value = bool(integer_parser(value))
        elif type_ == b"t":
            value = string_parser(value)
        elif type_ in integer_types:
            value = integer_parser(value)
        elif type_ in floating_point_types:
            value = floating_point_parser(value)
        else:
            try:
                value = integer_parser(value)
            except ValueError:
                try:
                    value = floating_point_parser(value)
                except ValueError:
                    # Not a numerical value, do nothing
                    pass
        return value

    if isinstance(data, bytes):
        data = data.splitlines()

    protocol = {}
    for line in data:
        match = re.match(br"^(?P<key>[\w\[\]\.]+)\s+=\s+(?P<value>.*)$", line)
        key, value = match.groupdict()["key"], match.groupdict()["value"]
        
        entry = protocol
        for element in key.split(b"."):
            match = re.match(
                r"(a?)((?:{0})?)(\w+)(?:\[(\d+)\])?".format("|".join(types)).encode(), 
                element)
            is_array, type_, name, index = match.groups()
            
            full_name = "{}{}{}".format(is_array.decode(), type_.decode(), name.decode())
            
            is_array = (is_array == b"a")
            if index:
                index = int(index)
            
            if is_array:
                entry = entry.setdefault(full_name, [])

                if len(entry) <= index:
                    entry.extend((1+index-len(entry))*[None])
                if type_ not in (b"", b"s"):
                    entry[index] = value_parser(type_, value)
                else:
                    if entry[index] is None:
                        entry[index] = {}
                    entry = entry[index]
            elif type_ == b"s":
                entry = entry.setdefault(full_name, {})
            else:
                entry.setdefault(full_name, value_parser(type_, value))

    return protocol
