#include "Figure.hpp"

class Square : public Figure {
    private:
        Point a;
        Point b;
        Point c;
        Point d;

        void print(std::ostream&) override;
        void input(std::istream&) override;
        void check(const Figure&) const override;
    public:
        Square();
        Square(const Point&, const Point&, const Point&, const Point&);
        Square(const Square&);

        virtual Point Center() const override;
        virtual double Area() const override;

        explicit virtual operator double() const override;
        friend std::ostream& operator << (std::ostream&, Square&);
        friend std::istream& operator >> (std::istream&, Square&);
        Figure& operator = (const Figure&) override;
        Figure& operator = (Figure&&) override;
        bool operator == (const Figure&) const override;

        virtual ~Square() = default;
};