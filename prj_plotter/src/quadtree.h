#pragma once

#include <vector>
#include <memory>
#include <cassert>

struct Point {
    double x, y;
    Point(double x=0, double y=0);
};

struct Stroke {
    double x1, y1, x2, y2;
    Stroke(double x1=0, double y1=0, double x2=0, double y2=0);
};

struct AABB {
    double x, y, width, height;
    AABB(double x=0, double y=0, double width=0, double height=0);
    bool contains_point(const Point& point) const;
    bool intersects(const AABB& other) const;
};

struct Patch {
    double x, y, width, height, value;
    Patch(double x=0, double y=0, double width=0, double height=0, 
        double value=0);
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
    bool insert_many(const std::vector<Point>& ps);
    std::vector<Point> query(const AABB& area) const;
    std::vector<Stroke> plot_grid() const;
    void _plot_grid(std::vector<Stroke>& strokes) const;
    std::vector<Patch> plot_density() const;
    void _plot_density(std::vector<Patch>& patches) const;
};

class Quadtree {
public:
    std::unique_ptr<Node> root;
    Quadtree(double x, double y, double width, double height, 
        int capacity, int max_level);
    bool insert(const Point& point);
    bool insert(const double& x, const double& y);
    bool insert_many(const std::vector<Point>& ps);
    bool insert_many(
        const std::vector<double>& x, const std::vector<double>& y);
    std::vector<Point> query(
        double x, double y, double width, double height) const;
    std::vector<Stroke> plot_grid() const;
    std::vector<Patch> plot_density() const;

private:
};
