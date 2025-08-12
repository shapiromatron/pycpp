#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <gsl/gsl_sf_bessel.h>
#include <Eigen/Dense>
#include <nlopt.h>

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

// GSL test
double gsl_bessel(double x) {
    return gsl_sf_bessel_J0(x);
}

// NLOPT test
double objfunc(unsigned n, const double* x, double* grad, void*) {
    if (grad) {
        grad[0] = 2 * (x[0] - 1);
        grad[1] = 2 * (x[1] - 2);
    }
    return (x[0] - 1) * (x[0] - 1) + (x[1] - 2) * (x[1] - 2);
}
std::vector<double> nlopt_demo(const std::vector<double>& lower_bounds,
                              const std::vector<double>& upper_bounds) {
    if (lower_bounds.size() != 2 || upper_bounds.size() != 2)
        throw std::invalid_argument("Bounds must have size 2");

    nlopt_opt opt = nlopt_create(NLOPT_LN_NELDERMEAD, 2);
    nlopt_set_lower_bounds(opt, lower_bounds.data());
    nlopt_set_upper_bounds(opt, upper_bounds.data());
    nlopt_set_min_objective(opt, objfunc, nullptr);

    double x[2] = {0.0, 0.0};
    double minf;
    int result = nlopt_optimize(opt, x, &minf);
    nlopt_destroy(opt);
    if (result < 0) throw std::runtime_error("nlopt failed");
    return {x[0], x[1]};
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
    m.def("gsl_bessel", &gsl_bessel, "Bessel function using GSL");
    m.def("nlopt_optimize", &nlopt_demo,
        py::arg("lower_bounds"), py::arg("upper_bounds"),
        "Run NLOPT optimization with specified bounds");
}
