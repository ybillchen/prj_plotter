from setuptools import setup, Extension
from pybind11.setup_helpers import Pybind11Extension

ext_modules = [
    Pybind11Extension(
        "quadtree_py",
        ["quadtree_pybind.cpp", "quadtree.cpp"],
        cxx_std=14,
    ),
]

setup(
    name="quadtree",
    version="0.1",
    description="Quadtree implementation in C++ with Python bindings",
    ext_modules=ext_modules,
)
