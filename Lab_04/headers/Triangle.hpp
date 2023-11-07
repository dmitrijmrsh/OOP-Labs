#include "Figure.hpp"

template<Numeric T>
class Triangle : public Figure {
    private:
        Point<T> a;
        Point<T> b;
        Point<T> c;

        void check_constructor(const Figure<T>&) const override;
        void check_points(const Point<T>&, const Point<T>&, const Point<T>&) const;
    public:
        Triangle();
        Triangle(const Point<T>&, const Point<T>&, const Point<T>&);
        Triangle(const Triangle<T>&);

        virtual Point<T> Center() const override;
        virtual double Area() const override;

        explicit virtual operator double() const override;
        Triangle& operator = (const Triangle<T>&);
        Triangle& operator = (Triangle&&);
        bool operator == (const Figure<T>&) const override;
        friend std::ostream& operator << (std::ostream& out, Triangle<T>& obj);
        friend std::istream& operator >> (std::istream& in, Triangle<T>& obj);

        virtual ~Triangle() = default;
};

template<Numeric T>
void Triangle<T>::check_constructor(const Figure<T>& f) const {
    const Triangle<T>* temp = dynamic_cast<const Triangle<T>*>(&f);
    if (temp == nullptr) {
        throw std::logic_error("Bad cast");
    }
    std::vector<Point<T>> points(3);
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
            sides[i] = round(Point<T>::Distance(points[i], points[i + 1]) * 1000) / 1000;
            continue;
        }
        sides[i] = round(Point<T>::Distance(points[i], points[0]) * 1000) / 1000;
    }
    for (int i = 0; i < 2; ++i) {
        if (sides[i] != sides[i + 1]) {
            throw std::logic_error("Triangle isn't equilateral");
        }
    }
}

template<Numeric T>
void Triangle<T>::check_points(const Point<T>& a, const Point<T>& b, const Point<T>& c) const {
    std::vector<Point<T>> points(3);
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
            sides[i] = round(Point<T>::Distance(points[i], points[i + 1]) * 1000) / 1000;
            continue;
        }
        sides[i] = round(Point<T>::Distance(points[i], points[0]) * 1000) / 1000;
    }
    for (int i = 0; i < 2; ++i) {
        if (sides[i] != sides[i + 1]) {
            throw std::logic_error("Triangle isn't equilateral");
        }
    }
}

template<Numeric T>
Triangle<T>::Triangle() : Figure("Triangle") {};

template<Numeric T>
Triangle<T>::Triangle(const Point<T>& a, const Point<T>& b, const Point<T>& c) : Figure("Triangle") {
    this->a = a;
    this->b = b;
    this->c = c;
    check_constructor(*this);
}

template<Numeric T>
Triangle<T>::Triangle(const Triangle<T>& t) : Figure("Triangle") {
    a = t.a;
    b = t.b;
    c = t.c;
}

template<Numeric T>
Point<T> Triangle<T>::Center() const {
    T x_cent = (a.get_x_value() + b.get_x_value() + c.get_x_value()) / 3;
    T y_cent = (a.get_y_value() + b.get_y_value() + c.get_y_value()) / 3;
    Point<T> center(x_cent, y_cent);
    return center;
}

template<Numeric T>
double Triangle<T>::Area() const {
    T ab = Point<T>::Distance(a, b);
    return ab * ab * sqrt(3) * 0.25;
}

template<Numeric T>
Triangle<T>::operator double() const {
    return this->Area();
}

template<Numeric T>
std::ostream& operator << (std::ostream& out, Triangle<T> obj) {
    out << obj.a << '\n';
    out << obj.b << '\n';
    out << obj.c << '\n';
    return out;
}

template<Numeric T>
std::istream& operator >> (std::istream& in, Triangle<T> obj) {
    in >> obj.a;
    in >> obj.b;
    in >> obj.c;
    check_points(obj.a, obj.b, obj.c);
    return in;
}

template<Numeric T>
Triangle<T>& Triangle<T>::operator = (const Triangle<T>& t) {
    if (this != &t) {
        a = t.a;
        b = t.b;
        c = t.c;
    }
    return *this;
}

template<Numeric T>
Triangle<T>& Triangle<T>::operator = (Triangle&& t) {
    if (this != &t) {
        a = t.a;
        b = t.b;
        c = t.c;
    }
    return *this;
}

template<Numeric T>
bool Triangle<T>::operator == (const Figure<T>& f) const {
    if (name != f.getname()) {
        return false;
    }
    const Triangle<T>* temp = dynamic_cast<const Triangle<T>*>(&f);
    if (temp == nullptr) {
        throw std::logic_error("Bad cast");
    }
    if (this->Area() == temp->Area()) {
        return true;
    }
    return false;
}