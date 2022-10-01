import multiprocessing
import os
import re
import subprocess
import sys

workspace = os.environ["WORKSPACE"]
build_dir = os.environ.get("BUILD_DIR", os.path.join(workspace, "build"))
install_dir = os.environ.get("BUILD_DIR", os.path.join(workspace, "install"))

for dir in [build_dir, install_dir]:
    if not os.path.isdir(dir):
        os.makedirs(dir)

subprocess.check_call(
    [
        "cmake", 
        "-G", "Ninja",
        "-DPYTHON_EXECUTABLE={}".format(sys.executable),
        "-DCMAKE_INSTALL_PREFIX={}".format(install_dir), 
        workspace],
    cwd=build_dir)

subprocess.check_call(["ninja", "install"], cwd=build_dir)
