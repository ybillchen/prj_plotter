/*
MIT License
Copyright (c) 2023 Bill Chen
All rights reserved.
*/

#include "quadtree.h"

Point::Point(double x, double y)
    : x(x), y(y) {}

Stroke::Stroke(double x1, double y1, double x2, double y2)
    : x1(x1), y1(y1), x2(x2), y2(y2) {}

AABB::AABB(double x, double y, double width, double height)
    : x(x), y(y), width(width), height(height) {}

bool AABB::contains_point(const Point& point) const {
    return point.x >= x && point.x <= x + width &&
           point.y >= y && point.y <= y + height;
}

bool AABB::intersects(const AABB& other) const {
    return x < other.x + other.width && x + width > other.x &&
           y < other.y + other.height && y + height > other.y;
}

Patch::Patch(double x, double y, double width, double height, double value)
    : x(x), y(y), width(width), height(height), value(value) {}

Node::Node(double x, double y, double width, double height, 
    int capacity, int max_level, int level)
    : boundary(x, y, width, height), 
    capacity(capacity), max_level(max_level), level(level) {}


bool Node::is_leaf() const {
    return nw == nullptr && ne == nullptr && sw == nullptr && se == nullptr;
}

void Node::subdivide() {
    double x2 = boundary.x + boundary.width/2;
    double y2 = boundary.y + boundary.height/2;
    
    nw.reset(new Node(boundary.x, boundary.y, 
        boundary.width/2, boundary.height/2, capacity, max_level, level+1));
    ne.reset(new Node(x2, boundary.y, 
        boundary.width/2, boundary.height/2, capacity, max_level, level+1));
    sw.reset(new Node(boundary.x, y2, 
        boundary.width/2, boundary.height/2, capacity, max_level, level+1));
    se.reset(new Node(x2, y2, 
        boundary.width/2, boundary.height/2, capacity, max_level, level+1));

    nw->insert_many(points);
    ne->insert_many(points);
    sw->insert_many(points);
    se->insert_many(points);

    points.clear();
}

bool Node::insert(const Point& point) {
    if (!boundary.contains_point(point)) {
        return false;
    }

    if (is_leaf() && points.size() < capacity) {
        points.push_back(point);
        return true;
    }

    if (is_leaf() && level == max_level) {
        points.push_back(point);
        return true;
    }

    if (is_leaf()) {
        subdivide();
    }

    return nw->insert(point) || ne->insert(point) || 
        sw->insert(point) || se->insert(point);
}

bool Node::insert_many(const std::vector<Point>& ps) {
    bool success = true;

    for (const auto& point : ps) {
        success = insert(point) && success;
    }

    return success;
}

std::vector<Point> Node::query(const AABB& area) const {
    std::vector<Point> result;

    if (!boundary.intersects(area)) {
        return result;
    }

    for (const auto& point : points) {
        if (area.contains_point(point)) {
            result.push_back(point);
        }
    }

    if (is_leaf()) {
        return result;
    }

    auto nw_result = nw->query(area);
    auto ne_result = ne->query(area);
    auto sw_result = sw->query(area);
    auto se_result = se->query(area);

    result.insert(result.end(), nw_result.begin(), nw_result.end());
    result.insert(result.end(), ne_result.begin(), ne_result.end());
    result.insert(result.end(), sw_result.begin(), sw_result.end());
    result.insert(result.end(), se_result.begin(), se_result.end());

    return result;
}

std::vector<Stroke> Node::plot_grid() const {
    Stroke low(boundary.x, boundary.y, 
        boundary.x+boundary.width, boundary.y);
    Stroke up(boundary.x, boundary.y+boundary.height, 
        boundary.x+boundary.width, boundary.y+boundary.height);
    Stroke left(boundary.x, boundary.y, 
        boundary.x, boundary.y+boundary.height);
    Stroke right(boundary.x+boundary.width, boundary.y, 
        boundary.x+boundary.width, boundary.y+boundary.height);

    std::vector<Stroke> strokes;
    strokes.push_back(low);
    strokes.push_back(up);
    strokes.push_back(left);
    strokes.push_back(right);

    _plot_grid(strokes);
    return strokes;
}

void Node::_plot_grid(std::vector<Stroke>& strokes) const {

    if (is_leaf()) {
        return;
    }

    Stroke h(boundary.x, boundary.y+boundary.height/2, 
        boundary.x+boundary.width, boundary.y+boundary.height/2); // horizontal
    Stroke v(boundary.x+boundary.width/2, boundary.y, 
        boundary.x+boundary.width/2, boundary.y+boundary.height); // vertical

    strokes.push_back(h);
    strokes.push_back(v);

    nw->_plot_grid(strokes);
    ne->_plot_grid(strokes);
    sw->_plot_grid(strokes);
    se->_plot_grid(strokes);
}

std::vector<Patch> Node::plot_density() const {
    std::vector<Patch> patches;
    _plot_density(patches);
    return patches;
}

void Node::_plot_density(std::vector<Patch>& patches) const {
    
    if (is_leaf()) {
        double dens = points.size() / (boundary.width * boundary.height);
        Patch leaf_patch(boundary.x, boundary.y, 
            boundary.width, boundary.height, dens);
        patches.push_back(leaf_patch);
        return;
    }

    nw->_plot_density(patches);
    ne->_plot_density(patches);
    sw->_plot_density(patches);
    se->_plot_density(patches);
}

Quadtree::Quadtree(double x, double y, double width, double height, 
    int capacity, int max_level)
    : root(new Node(x, y, width, height, capacity, max_level, 0)) {}

bool Quadtree::insert(const Point& point) {
    return root->insert(point);
}

bool Quadtree::insert(const double& x, const double& y) {
    Point point(x, y);
    return root->insert(point);
}

bool Quadtree::insert_many(const std::vector<Point>& ps) {
    return root->insert_many(ps);
}

bool Quadtree::insert_many(
    const std::vector<double>& x, const std::vector<double>& y) {
    assert(x.size() == y.size());

    std::vector<Point> ps;

    for (std::size_t i = 0; i < x.size(); ++i) {
        Point point(x[i], y[i]);
        ps.push_back(point);
    }

    return root->insert_many(ps);
}

std::vector<Point> Quadtree::query(
    double x, double y, double width, double height) const {
    AABB query_area(x, y, width, height);
    return root->query(query_area);
}

std::vector<Stroke> Quadtree::plot_grid() const {
    return root->plot_grid();
}

std::vector<Patch> Quadtree::plot_density() const {
    return root->plot_density();
}