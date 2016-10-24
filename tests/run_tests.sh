#!/bin/sh

ctest --no-compress-output -T Test $@ || true

PYTHONPATH=../src/python
PYTHONPATH=${PYTHONPATH}:../build/src/python/dicomifier
PYTHONPATH=${PYTHONPATH}:../build/src/python/dicomifier/bruker
PYTHONPATH=${PYTHONPATH}:../build/src/python/dicomifier/nifti
export PYTHONPATH

nosetests-2.7 ../tests/python/dicomifier
