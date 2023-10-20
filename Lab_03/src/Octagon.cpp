#include "../headers/Octagon.hpp"

void Octagon::check(const Figure& f) const {
    const Octagon* temp = dynamic_cast<const Octagon*>(&f);
    if (temp->a == temp->b || temp->a == temp->c || temp->a == temp->d || temp->a == temp->f || 
    temp->a == temp->f || temp->a == temp->g || temp->a == temp->h || temp->b == temp->c ||
    temp->b == temp->c || temp->b == temp->d || temp->b == temp->e || temp->b == temp->f ||
    temp->b == temp->g || temp->b == temp->h || temp->c == temp->d || temp->c == temp->d ||
    temp->c == temp->e || temp->c == temp->f || temp->c == temp->g || temp->c == temp->h ||
    temp->d == temp->e || temp->d == temp->f || temp->d == temp->g || temp->g == temp->h ||
    temp->e == temp->f || temp->e == temp->g || temp->e == temp->h || temp->f == temp->g ||
    temp->f == temp->h || temp->g == temp->h) {
        throw std::logic_error("Some points of octagon are the same");
    }
    double ab = round(Point::Distance(temp->a, temp->b) * 1000) / 1000;
    double bc = round(Point::Distance(temp->b, temp->c) * 1000) / 1000;
    double cd = round(Point::Distance(temp->c, temp->d) * 1000) / 1000;
    double de = round(Point::Distance(temp->d, temp->e) * 1000) / 1000;
    double ef = round(Point::Distance(temp->e, temp->f) * 1000) / 1000;
    double fg = round(Point::Distance(temp->f, temp->g) * 1000) / 1000;
    double gh = round(Point::Distance(temp->g, temp->h) * 1000) / 1000;
    if (ab == bc && ab == cd && ab == de && ab == ef && ab == fg && ab == gh) {
        return;
    }
    throw std::logic_error("Octagon isn't equilateral");
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
    check(*this);
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
}

std::ostream& operator << (std::ostream& out, Octagon& t) {
    t.print(out);
    return out;
}

std::istream& operator >> (std::istream& in, Octagon& t) {
    t.input(in);
    return in;
}

Figure& Octagon::operator = (const Figure& f) {
    if (name != f.getname()) {
        throw std::logic_error("You're trying to copy different figures");
    }
    const Octagon* temp = dynamic_cast<const Octagon*>(&f);
    if (this != temp) {
        this->a = temp->a;
        this->b = temp->b;
        this->c = temp->c;
    }
    return *this;
}

Figure& Octagon::operator = (Figure&& f) {
    if (name != f.getname()) {
        throw std::logic_error("You're trying to copy different figures");
    }
    const Octagon* temp = dynamic_cast<const Octagon*>(&f);

    if (this != temp) {
        this->a = temp->a;
        this->b = temp->b;
        this->c = temp->c;

        delete temp;
        temp = nullptr;
    }
    return *this;
}

bool Octagon::operator == (const Figure& f) const {
    if (name != f.getname()) {
        return false;
    }
    const Octagon* temp = dynamic_cast<const Octagon*>(&f);
    if (this->Area() == temp->Area()) {
        return true;
    }
    return false;
}