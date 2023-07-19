"""
MIT License
Copyright (c) Bill Chen 2023
All rights reserved.
"""

from setuptools import setup, find_packages
from pybind11.setup_helpers import Pybind11Extension, build_ext

ext_modules = [
    Pybind11Extension(
        "prj_quadtree",
        ["prj_plotter/src/quadtree_pybind.cpp", "prj_plotter/src/quadtree.cpp"],
        cxx_std=11,
    ),
]

with open("README.md", "r") as f:
    long_description = f.read()

version = {}
with open("prj_plotter/version.py") as fp:
    exec(fp.read(), version)

setup(
    name="prj_plotter",
    version = version["__version__"],
    url = "https://github.com/ybillchen/prj_plotter",
    license = "MIT",
    author = "Bill Chen",
    author_email = "ybchen@umich.edu",
    description="Number density projection plotter using quadtree",
    long_description = long_description,
    long_description_content_type = "text/markdown",
    ext_modules=ext_modules,
    cmdclass={"build_ext": build_ext},
    packages=find_packages(where="prj_plotter"),
    setup_requires = ["pybind11>=2.6.0"],
    install_requires = ["numpy", "matplotlib", "pybind11>=2.6.0"],
    classifiers = [
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: BSD License",
        "Operating System :: OS Independent",
    ],
)
