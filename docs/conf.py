import os
import re

project = "Dicomifier"
copyright = "2014-2024, Université de Strasbourg-CNRS"
author = "Julien Lamy"

# The short X.Y version
here = os.path.abspath(os.path.dirname(__file__))
with open(os.path.join(here, "..", "CMakeLists.txt")) as fd:
    version = re.search(r"set\(dicomifier_VERSION (.+?)\)", fd.read())
if not version:
    raise Exception("Could not get version from CMakeLists.txt")
version = version.group(1)
# The full version, including alpha/beta/rc tags
release = version

extensions = ["sphinx.ext.autodoc", "sphinx.ext.doctest", "sphinx.ext.mathjax"]

templates_path = ["_templates"]
exclude_patterns = ["_build", "Thumbs.db", ".DS_Store"]

html_theme = "furo"
html_static_path = ["_static"]
html_css_files = ["css/style.css"]
html_title = project

mathjax3_config = {
    "HTML-CSS": {"scale": 95},
}
