# cppcore for pybind11

MacOS installation:

```bash
uv pip install pybind11==3.0.0 --target=./pybind11
export CMAKE_PREFIX_PATH=/Users/andyshapiro/dev/pycpp/pybind11/pybind11/share/cmake
export CMAKE_BUILD_PARALLEL_LEVEL=$(nproc)
uv pip install -e .

mkdir vcpkg
cd vcpkg
git init
git remote add origin git@github.com:microsoft/vcpkg.git
git fetch --depth 1 origin c9c17dcea3016bc241df0422e82b8aea212dcb93
git checkout FETCH_HEAD
cd ..

export VCPKG_HOST_TRIPLET=x64-osx-dynamic
./vcpkg/bootstrap-vcpkg.sh
./vcpkg/vcpkg install --host-triplet=$VCPKG_HOST_TRIPLET
```
