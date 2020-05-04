import numpy

class Differences(object):
    def __init__(self):
        self.insert = {}
        self.remove = {}
        self.update = {}

def diff(v1, v2, exclusions=None):
    result = None
    if type(v1) != type(v2):
        raise NotImplementedError("TODO")
    elif isinstance(v1, dict):
        differences = diff_mappings(v1, v2, exclusions)
        if differences:
            result = differences
    elif isinstance(v1, list):
        differences = diff_sequences(v1, v2, exclusions)
        if differences:
            result = differences
    else:
        result = diff_scalars(v1, v2)
    
    return result

def diff_mappings(m1, m2, exclusions=None):
    result = Differences()
    
    keys = set(m1.keys()) | set(m2.keys())
    for key in keys:
        if key in (exclusions or set()):
            continue
        if key not in m1:
            result.insert[key] = m2[key]
        elif key not in m2:
            result.remove[key] = m1[key]
        else:
            differences = diff(m1[key], m2[key], exclusions)
            if differences is not None:
                result.update[key] = differences
    
    return result if any([result.insert, result.remove, result.update]) else None

def diff_sequences(s1, s2, exclusions=set()):
    result = Differences()
    
    length = min(len(s1), len(s2))
    for index in range(length):
        differences = diff(s1[index], s2[index], exclusions)
        if differences is not None:
            result.update[index] = differences
    
    if length == len(s1):
        for index in range(length, len(s2)):
            result.insert[index] = s2[idx]
    else:
        for index in range(length, len(s1)):
            result.remove[index] = s1[idx]
    
    return result if any([result.insert, result.remove, result.update]) else None

def diff_scalars(s1, s2):
    if isinstance(s1, float):
        if not numpy.isclose(s1, s2):
            return s2
        else:
            return None
    elif s1 != s2:
        return s2
    else:
        return None

def print_differences(differences, indent=0):
    if isinstance(differences, Differences):
        for action in ["insert", "remove", "update"]:
            if not getattr(differences, action):
                continue
            print(f"{indent*'  '}{action}")
            print_differences(getattr(differences, action), 1+indent)
    elif isinstance(differences, dict):
        for key in sorted(differences):
            print(f"{indent*'  '}{key}")
            print_differences(differences[key], 1+indent)
    else: 
        print(f"{indent*'  '}{differences}")
