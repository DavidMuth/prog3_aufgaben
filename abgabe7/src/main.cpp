
#include <iostream>
#include <memory>
#include <ostream>
#include <vector>

// TODO: Define an interface `Shape` (with a pure virtual function `print`). The print function shall
// accept a reference to the type of `std::cout` (check the type of `std::cout` in cppreference).

struct Shape {
    virtual void print(std::ostream& str) const = 0;
    virtual ~Shape() = default;
};

// create two classes (not structs) `Circle` and `Line` implementing the interface `Shape`.
// You will also need a helper struct `Point`.

struct Point {
    int x;
    int y;
};

std::ostream& operator<<(std::ostream& str, const Point& p) {
    return str << '(' << p.x << ',' << p.y << ')';
}

class Line : public Shape {
public:
    constexpr Line(Point s, Point e) : start{ s }, end{ e } {}

    virtual void print(std::ostream& str) const {
        str << "Line " << start << "->" << end;
    }

    Point start;
    Point end;
};

class Circle : public Shape {
public:
    constexpr Circle(Point c, int r) : center{ c }, radius{ r } {}

    virtual void print(std::ostream& str) const {
        str << "Circle " << center << ", r=" << radius;
    }

    Point center;
    int radius;
};

std::ostream& operator<<(std::ostream& str, const Shape& shape) {
    shape.print(str);
    return str;
}

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(Point{ 1, 2 }, 3));
    shapes.push_back(std::make_unique<Circle>(Point{ -1, 0 }, 4));
    shapes.push_back(std::make_unique<Line>(Point{ -10, -10 }, Point{ 10, 10 }));

    for (auto& x : shapes) {
        // x->print(std::cout);
        std::cout << *x << '\n';
    }
    /* TODO, output:
      Circle (1,2), r=3
      Circle (-1,0), r=4
      Line (-10,-10)->(10,10)
    */
}
