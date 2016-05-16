#!/bin/sh

ctest --no-compress-output -T Test $@ || true
PYTHONPATH=../src/python:../build/src/python/dicomifier:../build/src/python/dicomifier/bruker
nosetests-2.7 ../tests/python/dicomifier
