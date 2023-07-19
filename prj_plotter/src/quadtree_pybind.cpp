/*
MIT License
Copyright (c) 2023 Bill Chen
All rights reserved.
*/

#include <vector>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "quadtree.h"

namespace py = pybind11;

PYBIND11_MODULE(prj_quadtree, m) {
    py::class_<Point>(m, "Point")
        .def(py::init<double, double>())
        .def_readwrite("x", &Point::x)
        .def_readwrite("y", &Point::y);

    py::class_<Stroke>(m, "Stroke")
        .def(py::init<double, double, double, double>())
        .def_readwrite("x1", &Stroke::x1)
        .def_readwrite("y1", &Stroke::y1)
        .def_readwrite("x2", &Stroke::x2)
        .def_readwrite("y2", &Stroke::y2);

    py::class_<AABB>(m, "AABB")
        .def(py::init<double, double, double, double>())
        .def_readwrite("x", &AABB::x)
        .def_readwrite("y", &AABB::y)
        .def_readwrite("width", &AABB::width)
        .def_readwrite("height", &AABB::height)
        .def("contains_point", &AABB::contains_point)
        .def("intersects", &AABB::intersects);

    py::class_<Patch>(m, "Patch")
        .def(py::init<double, double, double, double, double>())
        .def_readwrite("x", &Patch::x)
        .def_readwrite("y", &Patch::y)
        .def_readwrite("width", &Patch::width)
        .def_readwrite("height", &Patch::height)
        .def_readwrite("value", &Patch::value);

    py::class_<Node, std::shared_ptr<Node>>(m, "Node")
        .def(py::init<double, double, double, double, int, int, int>())
        .def_readwrite("boundary", &Node::boundary)
        .def_readwrite("capacity", &Node::capacity)
        .def_readwrite("max_level", &Node::max_level)
        .def_readwrite("level", &Node::level)
        .def_property("nw", [](const Node& n) { return n.nw.get(); }, 
            [](Node& n, Node* nw) { n.nw.reset(nw); })
        .def_property("ne", [](const Node& n) { return n.ne.get(); }, 
            [](Node& n, Node* ne) { n.ne.reset(ne); })
        .def_property("sw", [](const Node& n) { return n.sw.get(); }, 
            [](Node& n, Node* sw) { n.sw.reset(sw); })
        .def_property("se", [](const Node& n) { return n.se.get(); }, 
            [](Node& n, Node* se) { n.se.reset(se); })
        .def("is_leaf", &Node::is_leaf)
        .def("subdivide", &Node::subdivide)
        .def("insert", &Node::insert)
        .def("insert_many", &Node::insert_many)
        .def("query", &Node::query)
        .def("plot_grid", &Node::plot_grid)
        .def("plot_density", &Node::plot_density)
        .def_readwrite("points", &Node::points);

    py::class_<Quadtree>(m, "Quadtree")
        .def(py::init<double, double, double, double, int, int>())
        .def("insert", (bool (Quadtree::*)(const Point&)) &Quadtree::insert)
        .def("insert", (bool (Quadtree::*)(const double&, const double&)) 
            &Quadtree::insert)
        .def("insert_many", (bool (Quadtree::*)(const std::vector<Point>&)) 
            &Quadtree::insert_many)
        .def("insert_many", (bool (Quadtree::*)(const std::vector<double>&, 
            const std::vector<double>&)) &Quadtree::insert_many)
        .def("query", &Quadtree::query)
        .def("plot_grid", &Quadtree::plot_grid)
        .def("plot_density", &Quadtree::plot_density)
        .def_property("root", [](const Quadtree& q) { return q.root.get(); }, 
            [](Quadtree& q, Node* root) { q.root.reset(root); });
}
