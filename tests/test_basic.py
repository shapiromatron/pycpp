import demo
from demo import cppcore


def test_main():
    assert demo.__version__ == "0.0.1"
    assert cppcore.add(1, 2) == 3
    assert cppcore.subtract(1, 2) == -1
