#include "Figure.hpp"

template<Numeric T>
class Octagon : public Figure {
    private:
        Point<T> a;
        Point<T> b;
        Point<T> c;
        Point<T> d;
        Point<T> e;
        Point<T> f;
        Point<T> g;
        Point<T> h;

        void check_constructor(const Figure<T>&) const override;
        void check_points(const Point<T>&, const Point<T>&, const Point<T>&, const Point<T>&, const Point<T>&, const Point<T>&, const Point<T>&, const Point<T>&);
    public:
        Octagon();
        Octagon(const Point<T>&, const Point<T>&, const Point<T>&, const Point<T>&, const Point<T>&, const Point<T>&, const Point<T>&, const Point<T>&);
        Octagon(const Octagon&);

        virtual Point<T> Center() const override;
        virtual double Area() const override;

        explicit virtual operator double() const override;
        Octagon<T>& operator = (const Octagon<T>&);
        Octagon<T>& operator = (Octagon<T>&&);
        bool operator == (const Figure<T>&) const override;

        virtual ~Octagon() = default;
};

template<Numeric T>
void Octagon<T>::check_constructor(const Figure<T>& f) const {
    const Octagon<T>* temp = dynamic_cast<const Octagon*>(&f);
    if (temp == nullptr) {
        throw std::logic_error("Bad cast");
    }
    std::vector<Point<T>> points(8);
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
            sides[i] = round(Point<T>::Distance(points[i], points[i + 1]) * 1000) / 1000;
            continue;
        }
        sides[i] = round(Point<T>::Distance(points[i], points[0]) * 1000) / 1000;
    }
    for (int i = 0; i < 7; ++i) {
        if (sides[i] != sides[i + 1]) {
            throw std::logic_error("Octagon isn't equilateral");
        }
    }
    double diam = 2 * sides[0] / sqrt(2 - sqrt(2));
    double dist;
    for (int i = 0; i < 4; ++i) {
        dist = Point<T>::Distance(points[i],points[i + 4]);
        if (fabs(dist - diam) > EPS) {
            throw std::logic_error("Octagon angles are not the same");
        }
    }
}

template<Numeric T>
void Octagon<T>::check_points(const Point<T>& a, const Point<T>& b, const Point<T>& c, const Point<T>& d, const Point<T>& e, const Point<T>& f, const Point<T>& g, const Point<T>& h) {
    std::vector<Point<T>> points(8);
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
            sides[i] = round(Point<T>::Distance(points[i], points[i + 1]) * 1000) / 1000;
            continue;
        }
        sides[i] = round(Point<T>::Distance(points[i], points[0]) * 1000) / 1000;
    }
    for (int i = 0; i < 7; ++i) {
        if (sides[i] != sides[i + 1]) {
            throw std::logic_error("Octagon isn't equilateral");
        }
    }
    double diam = 2 * sides[0] / sqrt(2 - sqrt(2));
    double dist;
    for (int i = 0; i < 4; ++i) {
        dist = Point<T>::Distance(points[i],points[i + 4]);
        if (fabs(dist - diam) > EPS) {
            throw std::logic_error("Octagon angles are not the same");
        }
    }
}