#!/bin/sh

export NOSE=${NOSE:?}

# This program must be run from the build directory.

ctest --no-compress-output -T Test $@
${NOSE} ../tests/python/dicomifier
