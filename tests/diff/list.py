import itertools
import json
import pathlib
import subprocess
import sys

import diff

def main():
    root = pathlib.Path(__file__).parents[1]/"data"
    if root.is_absolute():
        root = root.relative_to(pathlib.Path.cwd())
    input_ = root/"input"
    baseline = root/"baseline"
    
    cases = itertools.chain(
        input_.glob("*"), 
        *[baseline.glob(f"*.dcm{suffix}") for suffix in ["", ".multi"]])
    
    for path in cases:
        print(f"Checking {path}")
        data = subprocess.check_output([
            "dicomifier", 
            # "-v", "debug", 
            "list", "--json", str(path)])
        case_output = json.loads(data.decode())
        case_baseline = json.loads((baseline/f"{path.name}.json").read_text())
        
        differences = diff.diff(case_baseline, case_output)
        if differences:
            diff.print_differences(differences)

if __name__ == "__main__":
    sys.exit(main())
