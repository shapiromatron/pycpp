# A Python Package with a C++ extension

Explorations in how to use Python, C++, and bindings between the two systems. Build compiled code in multiple environments via GitHub Actions. Key technologies used include [pybind11](https://pybind11.readthedocs.io/en/stable/), [vcpkg](https://github.com/microsoft/vcpkg), and [cibuildwheel](https://cibuildwheel.readthedocs.io/en/stable/).

The project does the following:

- Builds a simple C++ package
- Includes third party C++ packages installed via the vcpkg package manager
- Builds a python interface to the C++ package
- Has some tests to ensure the C++ package works correctly from python
- Automatically builds the packages on Mac, Linux, and Windows

## Quickstart

For this particular example, we install 3 scientific C++ packages: as dependencies for our library:

* [Eigen3](https://vcpkg.io/en/package/eigen3.html) (headers only template library)
* [GNU Scientific Library](https://vcpkg.io/en/package/gsl.html)
* [NLopt](https://vcpkg.io/en/package/nlopt.html)

Though you could customize this template as needed to install other packages from vcpkg.

### MacOS/Linux:

```bash
# check out a single commit from a git repository
mkdir vcpkg
cd vcpkg
git init
git remote add origin git@github.com:microsoft/vcpkg.git
git fetch --depth 1 origin c9c17dcea3016bc241df0422e82b8aea212dcb93
git checkout FETCH_HEAD
cd ..

# build static dependencies; use the appropriate triplet (e.g., x64-linux, arm64-osx)
export $VCPKG_HOST_TRIPLET="arm64-osx"
./vcpkg/bootstrap-vcpkg.sh
./vcpkg/vcpkg install --host-triplet=$VCPKG_HOST_TRIPLET

# install pybind11 at the root so for our build phase
uv pip install pybind11==3.0.0 --target=./pybind11

# set environment variables for building python extension
export $CMAKE_PREFIX_PATH=export foo="$(readlink -f ./pybind11/pybind11/share/cmake)"
export $CMAKE_BUILD_PARALLEL_LEVEL=$(nproc)

echo "$VCPKG_HOST_TRIPLET"
echo "$CMAKE_PREFIX_PATH"
echo "$CMAKE_BUILD_PARALLEL_LEVEL"

# create a new python virtual environment
uv venv --python=3.13
.venv/bin/activate

# compile and install the package
uv pip install -v -e .

# generate typing stubs for C++ file
stubgen -p demo.cppcore -o src

# test
pytest
```

### Windows:

On Windows, install Visual Studio (2019 or 2022) and the C++ build packages (this is not related to Visual Studio Code). All commands below must be run within a Developer PowerShell for VS environment in order to use the appropriate compiler toolchain.

We'll build static dependencies ([x64-windows-static-md](https://learn.microsoft.com/en-us/vcpkg/users/platforms/windows)) for C++ to make them easier to add to our custom Python module.

```ps1
# check out a single commit from a git repository
mkdir vcpkg
cd vcpkg
git init
git remote add origin git@github.com:microsoft/vcpkg.git
git fetch --depth 1 origin c9c17dcea3016bc241df0422e82b8aea212dcb93
git checkout FETCH_HEAD
cd ..

# build static dependencies
$env:VCPKG_HOST_TRIPLET="x64-windows-static-md"
.\vcpkg\bootstrap-vcpkg.bat
.\vcpkg\vcpkg install --host-triplet="$env:VCPKG_HOST_TRIPLET"

# install pybind11 at the root so for our build phase
uv pip install pybind11==3.0.0 --target=./pybind11

# set environment variables for building python extension
$env:CMAKE_PREFIX_PATH=Resolve-Path "./pybind11/pybind11/share/cmake" | Select-Object -ExpandProperty Path
$env:CMAKE_BUILD_PARALLEL_LEVEL=[Environment]::ProcessorCount

echo "$env:VCPKG_HOST_TRIPLET"
echo "$env:CMAKE_PREFIX_PATH"
echo "$env:CMAKE_BUILD_PARALLEL_LEVEL"

# create a new python virtual environment
uv venv --python=3.13
.venv/Scripts/activate

# compile and install the package
uv pip install -v -e .

# generate typing stubs for C++ file
stubgen -p demo.cppcore -o src

# test
pytest
```

## Distributable Python Wheels

See the GitHub Actions.
