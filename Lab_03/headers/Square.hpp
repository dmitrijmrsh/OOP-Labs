#include "Figure.hpp"

class Square : public Figure {
    private:
        Point a;
        Point b;
        Point c;
        Point d;

        void print(std::ostream&) override;
        void input(std::istream&) override;
        void check_constructor(const Figure&) const override;
        void check_points(const Point&, const Point&, const Point&, const Point&);
    public:
        Square();
        Square(const Point&, const Point&, const Point&, const Point&);
        Square(const Square&);

        virtual Point Center() const override;
        virtual double Area() const override;

        explicit virtual operator double() const override;
        friend std::ostream& operator << (std::ostream&, Square&);
        friend std::istream& operator >> (std::istream&, Square&);
        Square& operator = (const Square&);
        Square& operator = (Square&&);
        bool operator == (const Figure&) const override;

        virtual ~Square() = default;
};