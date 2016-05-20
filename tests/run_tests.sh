#!/bin/sh

ctest --no-compress-output -T Test $@ || true
export PYTHONPATH=../src/python:../build/src/python/dicomifier:../build/src/python/dicomifier/bruker
nosetests-2.7 ../tests/python/dicomifier
