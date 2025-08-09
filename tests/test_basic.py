import numpy as np

import demo
from demo import cppcore


def test_main():
    assert demo.__version__ == "0.0.1"
    assert cppcore.add(1, 2) == 3
    assert cppcore.subtract(1, 2) == -1


def test_eigen_matmul():
    a = np.array([[1.0, 2.0], [3.0, 4.0]])
    b = np.array([[5.0, 6.0], [7.0, 8.0]])
    result = cppcore.eigen_matmul(a, b)
    expected = np.matmul(a, b)
    np.testing.assert_allclose(result, expected)
