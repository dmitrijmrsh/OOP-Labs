#include "../headers/Triangle.hpp"

void Triangle::check_constructor(const Figure& f) const {
    const Triangle* temp = dynamic_cast<const Triangle*>(&f);
    if (temp->a == temp->b || temp->a == temp->c || temp->b == temp->c) {
        throw std::logic_error("Some points of triangle are the same");
    }
    double ab = round(Point::Distance(temp->a, temp->b) * 1000) / 1000;
    double bc = round(Point::Distance(temp->b, temp->c) * 1000) / 1000;
    double ac = round(Point::Distance(temp->a, temp->c) * 1000) / 1000;
    if (ac == ab && ac == bc) {
        return;
    }
    throw std::logic_error("Triangle isn't equilateral");
}

void Triangle::check_points(const Point& a, const Point& b, const Point& c) {
    if (a == b || a == c || b == c) {
        throw std::logic_error("Some points of triangle are the same");
    }
    double ab = round(Point::Distance(a, b) * 1000) / 1000;
    double bc = round(Point::Distance(b, c) * 1000) / 1000;
    double ac = round(Point::Distance(a, c) * 1000) / 1000;
    if (ac == ab && ac == bc) {
        return;
    }
    throw std::logic_error("Triangle isn't equilateral");
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
    if (this->Area() == temp->Area()) {
        return true;
    }
    return false;
}