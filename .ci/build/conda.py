import subprocess

subprocess.check_call([
    "conda", "install", "--yes", "-c", "conda-forge",
    "boost", "cmake", "nibabel", "ninja", "numpy", "odil", "pkg-config",
    "pybind11", "python-dateutil", "requests"])
