#!/bin/bash

set -eo pipefail

ls
pwd
pip install pybind11==3.0.0 --target=pybind11
ls
