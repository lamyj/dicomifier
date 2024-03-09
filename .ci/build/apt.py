import os
import subprocess
import sys
import tempfile
import urllib.request

os.environ["DEBIAN_FRONTEND"] = "noninteractive"
subprocess.check_call([
    "apt-get", "-y", "--no-install-recommends", "install",
    "apt-transport-https", "curl", "gnupg", "software-properties-common",
    "unzip", "wget"])
codename = subprocess.check_output(["lsb_release", "-cs"]).strip().decode()

repository = "https://iris-packages.s3.unistra.fr"

try:
   urllib.request.urlopen("{}/apt/dists/{}/Release".format(repository, codename))
except urllib.request.HTTPError:
    pass
else:
    with tempfile.NamedTemporaryFile() as fd:
        fd.write(urllib.request.urlopen("{}/gpg.key".format(repository)).read())
        fd.flush()
        subprocess.check_call(["apt-key", "add", fd.name])
    subprocess.check_call([
        "add-apt-repository", "deb {}/apt {} main".format(repository, codename)])
    subprocess.check_call(["apt-get", "update"])

subprocess.check_call([
    "apt-get", "-y", "--no-install-recommends", "install",
    "build-essential", "cmake", "ninja-build", "pkg-config", "python3", 
    "libboost-dev", "libboost-date-time-dev", "libboost-exception-dev",
    "libboost-filesystem-dev", "libboost-regex-dev", "libboost-system-dev",
    "libodil-dev", "zlib1g-dev", "pybind11-dev", "python3-dev",
    "python3-dateutil", "python3-nibabel", "python3-numpy", "python3-odil",
    "python3-requests", "libboost-test-dev"])
