#include <vector>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "quadtree.h"

namespace py = pybind11;

PYBIND11_MODULE(quadtree_py, m) {
    py::class_<Point>(m, "Point")
        .def(py::init<double, double>())
        .def_readwrite("x", &Point::x)
        .def_readwrite("y", &Point::y);

    py::class_<Quadtree>(m, "Quadtree")
        .def(py::init<double, double, double, double, int, int>())
        .def("insert", (bool (Quadtree::*)(const Point&)) &Quadtree::insert)
        .def("insert", (bool (Quadtree::*)(const double&, const double&)) 
            &Quadtree::insert)
        .def("insert_many", (bool (Quadtree::*)(const std::vector<Point>&)) 
            &Quadtree::insert_many)
        .def("insert_many", (bool (Quadtree::*)(const std::vector<double>&, 
            const std::vector<double>&)) &Quadtree::insert_many)
        .def("query", &Quadtree::query);
}
