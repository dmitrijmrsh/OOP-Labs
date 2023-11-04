#include "../headers/Square.hpp"

void Square::check_constructor(const Figure& f) const {
    const Square* temp = dynamic_cast<const Square*>(&f);
    if (temp == nullptr) {
        throw std::logic_error("Bad cast");
    }
    std::vector<Point> points(4);
    points[0] = temp->a;
    points[1] = temp->b;
    points[2] = temp->c;
    points[3] = temp->d;
    for (int i = 0; i < 4; ++i) {
        if (points[i] == points[i + 1]) {
            throw std::logic_error("Some points of Square are the same");
        }
    }
    std::vector<double> sides(4);
    for (int i = 0; i < 4; ++i) {
        if (i < 3) {
            sides[i] = round(Point::Distance(points[i], points[i + 1]) * 1000) / 1000;
            continue;
        }
        sides[i] = round(Point::Distance(points[i], points[0]) * 1000) / 1000;
    }
    for (int i = 0; i < 3; ++i) {
        if (sides[i] != sides[i + 1]) {
            throw std::logic_error("This square has different sides");
        }
    }
    double ac = round(Point::Distance(points[0], points[2]) * 1000) / 1000;
    double ab = sides[0];
    double bc = sides[1];
    if (ac != round(sqrt(ab * ab + bc * bc) * 1000) / 1000) {
        throw std::logic_error("The angles of square are not 90 degrees");
    }
}

void Square::check_points(const Point& a, const Point& b, const Point& c, const Point& d) {
    std::vector<Point> points(4);
    points[0] = a;
    points[1] = b;
    points[2] = c;
    points[3] = d;
    for (int i = 0; i < 4; ++i) {
        if (points[i] == points[i + 1]) {
            throw std::logic_error("Some points of Square are the same");
        }
    }
    std::vector<double> sides(4);
    for (int i = 0; i < 4; ++i) {
        if (i < 3) {
            sides[i] = round(Point::Distance(points[i], points[i + 1]) * 1000) / 1000;
            continue;
        }
        sides[i] = round(Point::Distance(points[i], points[0]) * 1000) / 1000;
    }
    for (int i = 0; i < 3; ++i) {
        if (sides[i] != sides[i + 1]) {
            throw std::logic_error("This square has different sides");
        }
    }
    double ac = round(Point::Distance(points[0], points[2]) * 1000) / 1000;
    double ab = sides[0];
    double bc = sides[1];
    if (ac != round(sqrt(ab * ab + bc * bc) * 1000) / 1000) {
        throw std::logic_error("The angles of square are not 90 degrees");
    }
}

Square::Square() : Figure("Square") {};

Square::Square(const Point& a, const Point& b, const Point& c, const Point& d) : Figure("Square") {
    this->a = a;
    this->b = b;
    this->c = c;
    this->d = d;
    check_constructor(*this);
}

Square::Square(const Square& t) : Figure("Square") {
    a = t.a;
    b = t.b;
    c = t.c;
    d = t.d;
}

Point Square::Center() const {
    double x_cent = (a.get_x_value() + b.get_x_value() + c.get_x_value() + d.get_x_value()) / 4;
    double y_cent = (a.get_y_value() + b.get_y_value() + c.get_y_value() + d.get_y_value()) / 4;
    Point center(x_cent, y_cent);
    return center;
}

double Square::Area() const {
    double ab = Point::Distance(a, b);
    return ab * ab;
}

Square::operator double() const {
    return this->Area();
}

void Square::print(std::ostream& out) {
    out << a << '\n';
    out << b << '\n';
    out << c << '\n';
    out << d << '\n';
}

void Square::input(std::istream& in) {
    in >> a;
    in >> b;
    in >> c;
    in >> d;
    check_points(a, b, c, d);
}

std::ostream& operator << (std::ostream& out, Square& t) {
    t.print(out);
    return out;
}

std::istream& operator >> (std::istream& in, Square& t) {
    t.input(in);
    return in;
}

Square& Square::operator = (const Square& s) {
    if (this != &s) {
        a = s.a;
        b = s.b;
        c = s.c;
        d = s.d;
    }
   return *this;
}

Square& Square::operator = (Square&& s) {
    if (this != &s) {
        a = s.a;
        b = s.b;
        c = s.c;
        d = s.d;
    }
    return *this;
}

bool Square::operator == (const Figure& f) const {
    if (name != f.getname()) {
        return false;
    }
    const Square* temp = dynamic_cast<const Square*>(&f);
    if (temp == nullptr) {
        throw std::logic_error("Bad cast");
    }
    if (this->Area() == temp->Area()) {
        return true;
    }
    return false;
}