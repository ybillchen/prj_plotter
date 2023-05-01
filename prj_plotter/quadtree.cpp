#include "quadtree.h"

Point::Point(double x, double y)
    : x(x), y(y) {}

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
    
    nw = std::make_unique<Node>(boundary.x, boundary.y, 
        boundary.width/2, boundary.height/2, capacity, max_level, level+1);
    ne = std::make_unique<Node>(x2, boundary.y, 
        boundary.width/2, boundary.height/2, capacity, max_level, level+1);
    sw = std::make_unique<Node>(boundary.x, y2, 
        boundary.width/2, boundary.height/2, capacity, max_level, level+1);
    se = std::make_unique<Node>(x2, y2, 
        boundary.width/2, boundary.height/2, capacity, max_level, level+1);
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

Quadtree::Quadtree(double x, double y, double width, double height, 
    int capacity, int max_level)
    : root(std::make_unique<Node>(x, y, width, height, 
        capacity, max_level, 0)) {}

bool Quadtree::insert(const Point& point) {
    return root->insert(point);
}

bool Quadtree::insert(const double& x, const double& y) {
    Point* point = new Point(x, y);
    bool success = root->insert(*point);
    delete point;
    return success;
}

bool Quadtree::insert_many(const std::vector<Point>& points) {
    bool success = true;

    for (const auto& point : points) {
        success = success && root->insert(point);
    }

    return success;
}

bool Quadtree::insert_many(
    const std::vector<double>& x, const std::vector<double>& y) {
    assert(x.size() == y.size());

    bool success = true;

    for (std::size_t i = 0; i < x.size(); ++i) {
        Point* point = new Point(x[i], y[i]);
        success = success && root->insert(*point);
        delete point;
    }

    return success;
}

std::vector<Point> Quadtree::query(
    double x, double y, double width, double height) const {
    AABB query_area(x, y, width, height);
    return root->query(query_area);
}
