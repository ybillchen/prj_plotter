# prj_plotter

[![version](https://img.shields.io/badge/version-0.1-blue.svg)](https://github.com/ybillchen/prj_plotter)
[![license](https://img.shields.io/github/license/ybillchen/prj_plotter)](LICENSE)
<!-- [![workflows](https://img.shields.io/github/actions/workflow/status/ybillchen/GC_formation_model/build.yaml?logo=github)](https://github.com/ybillchen/GC_formation_model/actions/workflows/build.yaml) -->

Projection plotter for particle-based simulations using quadtree. The core implementation of quadtree is written in C++ for better computational performance.

The code is open source under an [MIT License](LICENSE), which allows you to redistribute and modify the code with moderate limitations.

## Intro

Coming soon.

## Install

We have tested `prj_plotter` on `python >= 3.6`. However, lower versions may also work. The prerequisites of this package are
```
numpy
matplotlib
pybind11 >= 2.6.0
```
 
Also, make sure some C++ compiler (e.g., GCC, Clang, MSVC, etc.) is properly installed. Your compiler should be up-to-date with the C++11 standard.

To download the package, `git clone` the source code from [GitHub](https://github.com/ybillchen/prj_plotter):
```shell
$ git clone https://github.com/ybillchen/prj_plotter.git
```
Next, `cd` the folder and use `pip` to install it:
```shell
$ cd prj_plotter/
$ pip install -e .
```
The `-e` command allows you to make changes to the Python code. You still need to re-install the package if you changed any of the C++ code.

<!-- ## Usage

To start with, let's run the model with default parameters
```python
>>> import prj_plotter as pp
```
You may want to use your own paramters. Then simply replace `params_example` with the name of your paramter file. -->


## Contribute

Feel free to dive in! [Raise an issue](https://github.com/ybillchen/prj_plotter/issues/new) or submit pull requests.

<!-- ### Pull request protocol

We recommend you to contribute code to `prj_plotter` following [GitHub flow](https://docs.github.com/en/get-started/quickstart/github-flow). To summarize, you submit a pull request via the following steps:

1. Clone the repository.
2. Create and checkout a new branch. For example, a new branch called `new_feature`.
3. Make changes on `new_feature` and never touch the `main` branch again until you are ready to merge.
4. When you feel ready, submit a pull request on GitHub.
5. There may be conflicts. If so, you need to 
	1. Checkout the `main` branch and pull from `origin`.
	2. Rebase `new_feature` on `main` and address the conflicts (recommended).
	3. Alternatively, you can compare `new_feature` with `main` and fix all conflicts.
	4. Your pull request will update automatically.
6. If your pull request is approved, we will squash and merge your commits. 
7. We will delete `new_feature` on GitHub when it's merged. You can choose to delete it loacally as well. 

**_NOTE:_** Any slight modification may entirely change the random number generation! To keep repeatability of the model, please construct a new random generator for the need of new random numbers -->

## Maintainers

- [@Yingtian (Bill) Chen](https://github.com/ybillchen)
