#include "../headers/Triangle.hpp"

void Triangle::check_constructor(const Figure& f) const {
    const Triangle* temp = dynamic_cast<const Triangle*>(&f);
    if (temp == nullptr) {
        throw std::logic_error("Bad cast");
    }
    std::vector<Point> points(3);
    points[0] = temp->a;
    points[1] = temp->b;
    points[2] = temp->c;
    for (int i = 0; i < 2; ++i) {
        if (points[i] == points[i + 1]) {
            throw std::logic_error("Some points of triangle are the same");
        }
    }
    std::vector<double> sides(3);
    for (int i = 0; i < 3; ++i) {
        if (i < 2) {
            sides[i] = round(Point::Distance(points[i], points[i + 1]) * 1000) / 1000;
            continue;
        }
        sides[i] = round(Point::Distance(points[i], points[0]) * 1000) / 1000;
    }
    for (int i = 0; i < 2; ++i) {
        if (sides[i] != sides[i + 1]) {
            throw std::logic_error("Triangle isn't equilateral");
        }
    }
}

void Triangle::check_points(const Point& a, const Point& b, const Point& c) {
    std::vector<Point> points(3);
    points[0] = a;
    points[1] = b;
    points[2] = c;
    for (int i = 0; i < 2; ++i) {
        if (points[i] == points[i + 1]) {
            throw std::logic_error("Some points of triangle are the same");
        }
    }
    std::vector<double> sides(3);
    for (int i = 0; i < 3; ++i) {
        if (i < 2) {
            sides[i] = round(Point::Distance(points[i], points[i + 1]) * 1000) / 1000;
            continue;
        }
        sides[i] = round(Point::Distance(points[i], points[0]) * 1000) / 1000;
    }
    for (int i = 0; i < 2; ++i) {
        if (sides[i] != sides[i + 1]) {
            throw std::logic_error("Triangle isn't equilateral");
        }
    }
}

Triangle::Triangle() : Figure("Triangle") {};

Triangle::Triangle(const Point& a, const Point& b, const Point& c) : Figure("Triangle") {
    this->a = a;
    this->b = b;
    this->c = c;
    check_constructor(*this);
}

Triangle::Triangle(const Triangle& t) : Figure("Triangle") {
    a = t.a;
    b = t.b;
    c = t.c;   
}

Point Triangle::Center() const {
    double x_cent = (a.get_x_value() + b.get_x_value() + c.get_x_value()) / 3;
    double y_cent = (a.get_y_value() + b.get_y_value() + c.get_y_value()) / 3;
    Point center(x_cent, y_cent);
    return center;
}

double Triangle::Area() const {
    double ab = Point::Distance(a, b);
    return ab * ab * sqrt(3) * 0.25;
}

Triangle::operator double() const {
    return this->Area();
}

void Triangle::print(std::ostream& out) {
    out << a << '\n';
    out << b << '\n';
    out << c << '\n';
}

void Triangle::input(std::istream& in) {
    in >> a;
    in >> b;
    in >> c;
    check_points(a, b, c);
}

std::ostream& operator << (std::ostream& out, Triangle& t) {
    t.print(out);
    return out;
}

std::istream& operator >> (std::istream& in, Triangle& t) {
    t.input(in);
    return in;
}

Triangle& Triangle::operator = (const Triangle& t) {
    if (this != &t) {
        a = t.a;
        b = t.b;
        c = t.c;
    }
    return *this;
}

Triangle& Triangle::operator = (Triangle&& t) {
    if (this != &t) {
        a = t.a;
        b = t.b;
        c = t.c;   
    }
    return *this;
}

bool Triangle::operator == (const Figure& f) const {
    if (name != f.getname()) {
        return false;
    }
    const Triangle* temp = dynamic_cast<const Triangle*>(&f);
    if (temp == nullptr) {
        throw std::logic_error("Bad cast");
    }
    if (this->Area() == temp->Area()) {
        return true;
    }
    return false;
}