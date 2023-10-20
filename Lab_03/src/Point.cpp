#include "../headers/Point.hpp"

Point::Point() {
    x = 0;
    y = 0;
}

Point::Point(double x, double y) {
    this->x = x;
    this->y = y;
}

Point::Point(const Point& p) {
    x = p.x;
    y = p.y;
}

double Point::get_x_value() const {
    return x;
}

double Point::get_y_value() const {
    return y;
}

bool Point::operator != (const Point& p) const {
    return !(*this == p);
}

bool Point::operator == (const Point& p) const {
    if (Distance(*this, p) <= 0.01) {
        return true;
    }
    return false;
}

Point& Point::operator = (const Point& p) {
    if (this != &p) {
        x = p.x;
        y = p.y;
    }
    return *this;
}

Point& Point::operator = (Point&& p) {
    if (this != &p) {
        x = p.x;
        y = p.y;

        p.x = 0;
        p.y = 0;
    }
    return *this;
}

std::ostream& operator << (std::ostream& out, const Point& obj) {
    out << "x: " << obj.get_x_value() << " y: " << obj.get_y_value();
    return out;
}

std::istream& operator >> (std::istream& in, Point& obj) {
    in >> obj.x >> obj.y;
    return in;
}

double Point::Distance(const Point& left, const Point& right) {
    return sqrt((left.x - right.x) * (left.x - right.x) + (left.y - right.y) * (left.y - right.y));
}