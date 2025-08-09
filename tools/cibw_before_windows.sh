#!/bin/bash

set -eo pipefail

pip install pybind11==3.0.0 --target=$GITHUB_WORKSPACE/pybind11

pwd
ls

echo $GITHUB_WORKSPACE

ls -laht $GITHUB_WORKSPACE
ls -laht $GITHUB_WORKSPACE/pybind11
ls -laht $GITHUB_WORKSPACE/pybind11/pybind11
ls -laht $GITHUB_WORKSPACE/pybind11/pybind11/share
ls -laht $GITHUB_WORKSPACE/pybind11/pybind11/share/cmake
ls -laht $GITHUB_WORKSPACE/pybind11/pybind11/share/cmake/pybind11

