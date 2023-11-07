#include "../headers/Octagon.hpp"

void Octagon::check_constructor(const Figure& f) const {
    const Octagon* temp = dynamic_cast<const Octagon*>(&f);
    if (temp == nullptr) {
        throw std::logic_error("Bad cast");
    }
    std::vector<Point> points(8);
    points[0] = temp->a;
    points[1] = temp->b;
    points[2] = temp->c;
    points[3] = temp->d;
    points[4] = temp->e;
    points[5] = temp->f;
    points[6] = temp->g;
    points[7] = temp->h;
    for (int i = 0; i < 7; ++i) {
        if (points[i] == points[i + 1]) {
            throw std::logic_error("Some points of octagon are the same");
        }
    }
    std::vector<double> sides(8);
    for (int i = 0; i < 8; ++i) {
        if (i < 7) {
            sides[i] = round(Point::Distance(points[i], points[i + 1]) * 1000) / 1000;
            continue;
        }
        sides[i] = round(Point::Distance(points[i], points[0]) * 1000) / 1000;
    }
    for (int i = 0; i < 7; ++i) {
        if (sides[i] != sides[i + 1]) {
            throw std::logic_error("Octagon isn't equilateral");
        }
    }
    double diam = 2 * sides[0] / sqrt(2 - sqrt(2));
    double dist;
    for (int i = 0; i < 4; ++i) {
        dist = Point::Distance(points[i],points[i + 4]);
        if (fabs(dist - diam) > EPS) {
            throw std::logic_error("Octagon angles are not the same");
        }
    }
}

void Octagon::check_points(const Point& a, const Point& b, const Point& c, const Point& d, const Point& e, const Point& f, const Point& g, const Point& h) {
    std::vector<Point> points(8);
    points[0] = a;
    points[1] = b;
    points[2] = c;
    points[3] = d;
    points[4] = e;
    points[5] = f;
    points[6] = g;
    points[7] = h;
    for (int i = 0; i < 7; ++i) {
        if (points[i] == points[i + 1]) {
            throw std::logic_error("Some points of octagon are the same");
        }
    }
    std::vector<double> sides(8);
    for (int i = 0; i < 8; ++i) {
        if (i < 7) {
            sides[i] = round(Point::Distance(points[i], points[i + 1]) * 1000) / 1000;
            continue;
        }
        sides[i] = round(Point::Distance(points[i], points[0]) * 1000) / 1000;
    }
    for (int i = 0; i < 7; ++i) {
        if (sides[i] != sides[i + 1]) {
            throw std::logic_error("Octagon isn't equilateral");
        }
    }
    double diam = 2 * sides[0] / sqrt(2 - sqrt(2));
    double dist;
    for (int i = 0; i < 4; ++i) {
        dist = Point::Distance(points[i],points[i + 4]);
        if (fabs(dist - diam) > EPS) {
            throw std::logic_error("Octagon angles are not the same");
        }
    }
}

Octagon::Octagon() : Figure("Octagon") {};

Octagon::Octagon(const Point& a, const Point& b, const Point& c, const Point& d, const Point& e, const Point& f, const Point& g, const Point& h) : Figure("Octagon") {
    this->a = a;
    this->b = b;
    this->c = c;
    this->d = d;
    this->e = e;
    this->f = f;
    this->g = g;
    this->h = h;
    check_constructor(*this);
}

Octagon::Octagon(const Octagon& t) : Figure("Octagon") {
    a = t.a;
    b = t.b;
    c = t.c; 
    d = t.d;
    e = t.e;
    f = t.f;  
    g = t.g;
    h = t.h;  
}

Point Octagon::Center() const {
    double x_cent = (a.get_x_value() + b.get_x_value() + c.get_x_value() + d.get_x_value() + e.get_x_value() + f.get_x_value() + g.get_x_value() + h.get_x_value()) / 8;
    double y_cent = (a.get_y_value() + b.get_y_value() + c.get_y_value() + d.get_y_value() + e.get_y_value() + f.get_y_value() + g.get_y_value() + h.get_y_value()) / 8;
    Point center(x_cent, y_cent);
    return center;
}

double Octagon::Area() const {
    double ab = Point::Distance(a, b);
    return 2 * ab * ab * (sqrt(2) + 1);
}

Octagon::operator double() const {
    return this->Area();
}

void Octagon::print(std::ostream& out) {
    out << a << '\n';
    out << b << '\n';
    out << c << '\n';
    out << d << '\n';
    out << e << '\n';
    out << f << '\n';
    out << g << '\n';
    out << h << '\n';
}

void Octagon::input(std::istream& in) {
    in >> a;
    in >> b;
    in >> c;
    in >> d;
    in >> e;
    in >> f;
    in >> g;
    in >> h;
    check_points(a, b, c, d, e, f, g, h);
}

std::ostream& operator << (std::ostream& out, Octagon& t) {
    t.print(out);
    return out;
}

std::istream& operator >> (std::istream& in, Octagon& t) {
    t.input(in);
    return in;
}

Octagon& Octagon::operator = (const Octagon& o) {
    if (this != &o) {
        a = o.a;
        b = o.b;
        c = o.c;
        d = o.d;
        e = o.e;
        f = o.f;
        g = o.g;
        h = o.h;
    }
    return *this;
}

Octagon& Octagon::operator = (Octagon&& o) {
    if (this != &o) {
        a = o.a;
        b = o.b;
        c = o.c;
        d = o.d;
        e = o.e;
        f = o.f;
        g = o.g;
        h = o.h;
    }
    return *this;
}

bool Octagon::operator == (const Figure& f) const {
    if (name != f.getname()) {
        return false;
    }
    const Octagon* temp = dynamic_cast<const Octagon*>(&f);
    if (temp == nullptr) {
        throw std::logic_error("Bad cast");
    }
    if (this->Area() == temp->Area()) {
        return true;
    }
    return false;
}