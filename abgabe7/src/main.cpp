#include <iostream>
#include <memory>
#include <ostream>
#include <vector>

// TODO: Define an interface `Shape` (with a pure virtual function `print`). The print function shall
// accept a reference to the type of `std::cout` (check the type of `std::cout` in cppreference).
struct Shape {
    virtual ~Shape() = default;
    virtual void print(std::ostream& s) = 0;
};

// create two classes (not structs) `Circle` and `Line` implementing the interface `Shape`.
// You will also need a helper struct `Point`.

struct Point {
    int x;
    int y;
    Point(int x, int y) : x(x), y(y) {};
};

class Circle : public Shape {
    Point center;
    int r;

public:
    Circle(Point p, int r) : center(p), r(r) {};
    void print(std::ostream& s) override {
        s << "Circle (" << center.x << "," << center.y << "), r=" << r << '\n';
    }
};

class Line : public Shape {
    Point p1;
    Point p2;

public:
    Line(Point p1, Point p2) : p1(p1), p2(p2) {};
    void print(std::ostream& s) override {
        s << "Line (" << p1.x << "," << p1.y << ")->(" << p2.x << "," << p2.y << ")\n";
    }
};

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(Point{ 1, 2 }, 3));
    shapes.push_back(std::make_unique<Circle>(Point{ -1, 0 }, 4));
    shapes.push_back(std::make_unique<Line>(Point{ -10, -10 }, Point{ 10, 10 }));

    for (auto& x : shapes) {
        x->print(std::cout);
    }
    /* TODO, output:
      Circle (1,2), r=3
      Circle (-1,0), r=4
      Line (-10,-10)->(10,10)
    */
}
