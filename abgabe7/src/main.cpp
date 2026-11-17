
#include <iostream>
#include <memory>
#include <vector>

// TODO: Define an interface `Shape` (with a pure virtual function `print`). The print function shall
// accept a reference to the type of `std::cout` (check the type of `std::cout` in cppreference).
struct Shape {
    virtual void print(std::ostream& str) = 0;
    virtual ~Shape() = default;
};

// create two classes (not structs) `Circle` and `Line` implementing the interface `Shape`.
// You will also need a helper struct `Point`.
struct Point {
    int x, y;
};

class Circle : public Shape {
    Point center;
    int radius;

public:
    Circle(Point _p, int _r) : center(_p), radius(_r) {};
    void print(std::ostream& str) override {
        str << "Circle (" << center.x << ", " << center.y << "), r=" << radius << "\n";
    }
};

class Line : public Shape {
    Point start;
    Point end;

public:
    Line(Point _s, Point _e) : start(_s), end(_e) {};
    void print(std::ostream& str) override {
        str << "Line (" << start.x << ", " << start.y << ") -> (" << end.x << ", " << end.y << ")\n";
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
