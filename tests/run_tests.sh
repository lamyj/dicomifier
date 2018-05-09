#!/bin/sh

# This program must be run from the build directory.

ctest --no-compress-output -T Test $@ || true

PYTHONPATH=${PYTHONPATH}:../src/python
PYTHONPATH=${PYTHONPATH}:./src/python/dicomifier
PYTHONPATH=${PYTHONPATH}:./src/python/dicomifier/bruker
export PYTHONPATH

nosetests-2.7 ../tests/python/dicomifier
