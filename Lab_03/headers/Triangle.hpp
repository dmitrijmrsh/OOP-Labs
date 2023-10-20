#include "Figure.hpp"

class Triangle : public Figure {
    private:
        Point a;
        Point b;
        Point c;

        void print(std::ostream&) override;
        void input(std::istream&) override;
        void check(const Figure&) const override;
    public:
        Triangle();
        Triangle(const Point&, const Point&, const Point&);
        Triangle(const Triangle&);

        virtual Point Center() const override;
        virtual double Area() const override;

        explicit virtual operator double() const override;
        friend std::ostream& operator << (std::ostream&, Triangle&);
        friend std::istream& operator >> (std::istream&, Triangle&);
        Figure& operator = (const Figure&) override;
        Figure& operator = (Figure&&) override;
        bool operator == (const Figure&) const override;

        virtual ~Triangle() = default;
};