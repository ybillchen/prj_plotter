from setuptools import setup, find_packages
from pybind11.setup_helpers import Pybind11Extension, build_ext

ext_modules = [
    Pybind11Extension(
        "prj_quadtree",
        ["prj_plotter/src/quadtree_pybind.cpp", "prj_plotter/src/quadtree.cpp"],
        cxx_std=14,
    ),
]

setup(
    name="prj_plotter",
    version="0.1",
    description="Quadtree implementation in C++ with Python bindings",
    ext_modules=ext_modules,
    cmdclass={"build_ext": build_ext},
    packages=find_packages(where="prj_plotter"),
)
