#include "Figure.hpp"

class Octagon : public Figure {
    private:
        Point a;
        Point b;
        Point c;
        Point d;
        Point e;
        Point f;
        Point g;
        Point h;
    
        void print(std::ostream&) override;
        void input(std::istream&) override;
        void check_constructor(const Figure&) const override;
        void check_points(const Point&, const Point&, const Point&, const Point&, const Point&, const Point&, const Point&, const Point&);
    public:
        Octagon();
        Octagon(const Point&, const Point&, const Point&, const Point&, const Point&, const Point&, const Point&, const Point&);
        Octagon(const Octagon&);

        virtual Point Center() const override;
        virtual double Area() const override;

        explicit virtual operator double() const override;
        friend std::ostream& operator << (std::ostream&, Octagon&);
        friend std::istream& operator >> (std::istream&, Octagon&);
        Octagon& operator = (const Octagon&);
        Octagon& operator = (Octagon&&);
        bool operator == (const Figure&) const override;

        virtual ~Octagon() = default;
};