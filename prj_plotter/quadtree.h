#pragma once

#include <vector>
#include <memory>
#include <cassert>

struct Point {
    double x, y;
    Point(double x=0, double y=0);
};

struct AABB {
    double x, y, width, height;
    AABB(double x=0, double y=0, double width=0, double height=0);
    bool contains_point(const Point& point) const;
    bool intersects(const AABB& other) const;
};

struct Node {
    AABB boundary;
    int capacity, max_level, level;
    std::unique_ptr<Node> nw, ne, sw, se;
    std::vector<Point> points;
    Node(double x, double y, double width, double height, 
        int capacity, int max_level, int level);
    bool is_leaf() const;
    void subdivide();
    bool insert(const Point& point);
    std::vector<Point> query(const AABB& area) const;
};

class Quadtree {
public:
    Quadtree(double x, double y, double width, double height, 
        int capacity, int max_level);
    bool insert(const Point& point);
    bool insert(const double& x, const double& y);
    bool insert_many(const std::vector<Point>& points);
    bool insert_many(
        const std::vector<double>& x, const std::vector<double>& y);
    std::vector<Point> query(
        double x, double y, double width, double height) const;

private:
    std::unique_ptr<Node> root;
};
