#include "Figure.hpp"

template<Numeric T>
class Square : public Figure {
    private:
        Point<T> a;
        Point<T> b;
        Point<T> c;
        Point<T> d;

        void check_constructor(const Figure<T>&) const override;
        void check_points(const Point<T>&, const Point<T>&, const Point<T>&, const Point<T>&) const;
    public:
        Square();
        Square(const Point<T>&, const Point<T>&, const Point<T>&, const Point<T>&);
        Square(const Square<T>&);

        virtual Point<T> Center() const override;
        virtual double Area() const override;

        explicit virtual operator double() const override;
        Square<T>& operator = (const Square<T>&);
        Square<T>& operator = (Square<T>&&);
        bool operator == (const Figure<T>&) const override;

        virtual ~Square() = default;
};

template<Numeric T>
void Square<T>::check_constructor(const Figure<T>& f) const  {
    const Square<T>* temp = dynamic_cast<const Square<T>*>(&f);
    if (temp == nullptr) {
        throw std::logic_error("Bad cast");
    }
    std::vector<Point<T>> points(4);
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
            sides[i] = round(Point<T>::Distance(points[i], points[i + 1]) * 1000) / 1000;
            continue;
        }
        sides[i] = round(Point<T>::Distance(points[i], points[0]) * 1000) / 1000;
    }
    for (int i = 0; i < 3; ++i) {
        if (sides[i] != sides[i + 1]) {
            throw std::logic_error("This square has different sides");
        }
    }
    double ac = round(Point<T>::Distance(points[0], points[2]) * 1000) / 1000;
    double ab = sides[0];
    double bc = sides[1];
    if (ac != round(sqrt(ab * ab + bc * bc) * 1000) / 1000) {
        throw std::logic_error("The angles of square are not 90 degrees");
    }
}

template<Numeric T>
void Square<T>::check_points(const Point<T>& a, const Point<T>& b, const Point<T>&, const Point<T>& d) const{
    std::vector<Point<T>> points(4);
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
            sides[i] = round(Point<T>::Distance(points[i], points[i + 1]) * 1000) / 1000;
            continue;
        }
        sides[i] = round(Point<T>::Distance(points[i], points[0]) * 1000) / 1000;
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

template<Numeric T>
Square<T>::Square() : Figure("Square") {};

template<Numeric T>
Square<T>::Square(const Point<T>& a, const Point<T>& b, const Point<T>& c, const Point<T>& d) : Figure("Square") {
    this->a = a;
    this->b = b;
    this->c = c;
    this->d = d;
    check_constructor(*this);
}

template<Numeric T>
Square<T>::Square(const Square<T>& s) : Figure("Square") {
    a = s.a;
    b = s.b;
    c = s.c;
    d = s.d;
}

template<Numeric T>
Point<T> Square<T>::Center() const {
    T x_cent = (a.get_x_value() + b.get_x_value() + c.get_x_value() + d.get_x_value()) / 4;
    T y_cent = (a.get_y_value() + b.get_y_value() + c.get_y_value() + d.get_y_value()) / 4;
    Point<T> center(x_cent, y_cent);
    return center;
}

template<Numeric T>
double Square<T>::Area() const {
    T ab = Point<T>::Distance(a, b);
    return ab * ab;
}

template<Numeric T>
Square<T>::operator double() const {
    return this->Area();
}

template<Numeric T>
std::ostream& operator << (std::ostream& out, Square<T>& s) {
    out << s.a << '\n';
    out << s.b << '\n';
    out << s.c << '\n';
    out << s.d << '\n';
    return out;
}

template<Numeric T>
std::istream& operator >> (std::istream& in, Square<T>& s) {
    in >> s.a;
    in >> s.b;
    in >> s.c;
    in >> s.d;
    return in;
}

template<Numeric T>
Square<T>& Square<T>::operator = (const Square<T>& s) {
    if (this != &s) {
        a = s.a;
        b = s.b;
        c = s.c;
        d = s.d;
    }
    return *this;
}

template<Numeric T>
bool Square<T>::operator == (const Figure<T>& f) const {
    if (name != f.getname()) {
        return false;
    }
    const Square<T>* temp = dynamic_cast<const Square<T>*>(&f); 
    if (temp == nullptr) {
        throw std::logic_error("Bad cast");
    }
    if (this->Area() == temp->Area()) {
        return true;
    }
    return false;
}