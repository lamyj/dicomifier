import os
import subprocess
import sys
import sysconfig

workspace = os.environ["WORKSPACE"]
build_dir = os.environ.get("BUILD_DIR", os.path.join(workspace, "build"))
install_dir = os.environ.get("INSTALL_DIR", os.path.join(workspace, "install"))

bin_dir = os.path.join(install_dir, "bin")
lib_dir = os.path.join(install_dir, "lib")
python_lib_dir = os.path.join(
    install_dir,
    sysconfig.get_path(
        "purelib", {"posix":"posix_prefix", "nt":"nt"}[os.name], {"base": "."}))
python_tests_dir = os.path.join(workspace, "tests", "python")

# Set-up environment: C++ library, Python module and test data location.
for name in ["DYLD_LIBRARY_PATH", "LD_LIBRARY_PATH"]:
    os.environ[name] = os.pathsep.join([
        *os.environ.get(name, "").split(os.pathsep), lib_dir])
os.environ["PATH"] = os.pathsep.join([
    *os.environ.get("PATH", "").split(os.pathsep), bin_dir])
os.environ["PYTHONPATH"] = os.pathsep.join([
    *os.environ.get("PYTHONPATH", "").split(os.pathsep), python_lib_dir])
os.environ["DICOMIFIER_TEST_DATA"] = os.path.join(workspace, "tests", "data")

# Run C++ and Python tests even if the former fails, return non-zero if any
# failed.
return_code = 0
return_code = max(
    return_code,
    subprocess.call(["ctest"], cwd=build_dir, stderr=subprocess.STDOUT))
return_code = max(
    return_code,
    subprocess.call(
        [sys.executable, "-m", "unittest", "discover", "-s", python_tests_dir], 
        cwd=build_dir, stderr=subprocess.STDOUT))

sys.exit(return_code)
