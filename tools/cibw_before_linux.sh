#!/bin/bash

yum install zip

set -eo pipefail

pip install pybind11==3.0.0 --target=./pybind11

echo $VCPKG_HOST_TRIPLET
./vcpkg/bootstrap-vcpkg.sh
./vcpkg/vcpkg.exe install --host-triplet=$VCPKG_HOST_TRIPLET
