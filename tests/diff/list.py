import itertools
import json
import pathlib
import subprocess
import sys

import diff

def main():
    root = pathlib.Path(__file__).parents[1]/"data"
    input_ = root/"input"
    baseline = root/"baseline"
    
    cases = itertools.chain(
        input_.glob("*"), 
        *[baseline.glob("*.dcm{}".format(suffix)) for suffix in ["", ".multi"]])
    
    for path in cases:
        print("Checking {}".format(path))
        data = subprocess.check_output([
            "dicomifier", "-v", "debug", "list", "--json", str(path)])
        case_output = json.loads(data.decode())
        case_baseline = json.loads((baseline/"{}.json".format(path.name)).read_text())
        differences = diff.diff(case_baseline, case_output)
        if differences:
            diff.print_differences(differences)

if __name__ == "__main__":
    sys.exit(main())
