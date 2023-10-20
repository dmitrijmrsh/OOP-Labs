#include "../headers/Square.hpp"

void Square::check(const Figure& f) const {
    const Square* temp = dynamic_cast<const Square*>(&f);
    if (temp->a == temp->b || temp->a == temp->c || temp->a == temp->d ||
    temp->b == temp->c || temp->b == temp->d || temp->c == temp->d) {
        throw std::logic_error("Some points of Square are the same");
    }
    double ab = round(Point::Distance(temp->a, temp->b) * 1000) / 1000;
    double bc = round(Point::Distance(temp->b, temp->c) * 1000) / 1000;
    double cd = round(Point::Distance(temp->c, temp->d) * 1000) / 1000;
    double da = round(Point::Distance(temp->d, temp->a) * 1000) / 1000;
    if (ab == bc && ab == cd && ab == da) {
        return;
    }
    throw std::logic_error("That's not a square");
}

Square::Square() : Figure("Square") {};

Square::Square(const Point& a, const Point& b, const Point& c, const Point& d) {
    this->a = a;
    this->b = b;
    this->c = c;
    this->d = d;
    check(*this);
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
}

std::ostream& operator << (std::ostream& out, Square& t) {
    t.print(out);
    return out;
}

std::istream& operator >> (std::istream& in, Square& t) {
    t.input(in);
    return in;
}

Figure& Square::operator = (const Figure& f) {
    if (name != f.getname()) {
        throw std::logic_error("You're trying to copy different figures");
    }
    const Square* temp = dynamic_cast<const Square*>(&f);
    if (this != temp) {
        this->a = temp->a;
        this->b = temp->b;
        this->c = temp->c;
        this->d = temp->d;
    }
   return *this;
}

Figure& Square::operator = (Figure&& f) {
    if (name != f.getname()) {
        throw std::logic_error("You're trying to copy different figures");
    }
    const Square* temp = dynamic_cast<const Square*>(&f);
    if (this != temp) {
        this->a = temp->a;
        this->b = temp->b;
        this->c = temp->c;
        this->d = temp->d;

        delete temp;
        temp = nullptr;
    }
    return *this;
}

bool Square::operator == (const Figure& f) const {
    if (name != f.getname()) {
        return false;
    }
    const Square* temp = dynamic_cast<const Square*>(&f);
    if (this->Area() == temp->Area()) {
        return true;
    }
    return false;
}