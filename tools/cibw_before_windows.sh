#!/bin/bash

set -eo pipefail

pip install pybind11==3.0.0 --target=$GITHUB_WORKSPACE/pybind11

echo $VCPKG_HOST_TRIPLET
./vcpkg/bootstrap-vcpkg.sh
./vcpkg/vcpkg install --host-triplet=$VCPKG_HOST_TRIPLET

echo $GITHUB_WORKSPACE
