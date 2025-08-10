#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <Eigen/Dense>

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

int add(int i, int j) {
    return i + j;
}

namespace py = pybind11;

// EIGEN test
py::array_t<double> eigen_matmul(py::array_t<double, py::array::c_style | py::array::forcecast> a,
                           py::array_t<double, py::array::c_style | py::array::forcecast> b) {
    if (a.ndim() != 2 || b.ndim() != 2)
        throw std::runtime_error("Input must be two 2D arrays");
    if (a.shape(1) != b.shape(0))
        throw std::runtime_error("Matrix dimensions do not align for multiplication");

    using MatrixRm = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;
    Eigen::Map<const MatrixRm> A(a.data(), a.shape(0), a.shape(1));
    Eigen::Map<const MatrixRm> B(b.data(), b.shape(0), b.shape(1));
    MatrixRm C = A * B;

    // Create numpy array with correct strides (row major)
    return py::array_t<double>(
        {C.rows(), C.cols()},
        {sizeof(double) * C.cols(), sizeof(double)},
        C.data()
    );
}

PYBIND11_MODULE(cppcore, m) {
    m.doc() = R"pbdoc(
        Pybind11 example plugin
        -----------------------

        .. currentmodule:: cppcore

        .. autosummary::
           :toctree: _generate

           add
           subtract
    )pbdoc";

    m.def("add", &add, R"pbdoc(
        Add two numbers

        Some other explanation about the add function.
    )pbdoc");

    m.def("subtract", [](int i, int j) { return i - j; }, R"pbdoc(
        Subtract two numbers

        Some other explanation about the subtract function.
    )pbdoc");

    m.def("eigen_matmul", &eigen_matmul, "Matrix multiplication using Eigen");
}
