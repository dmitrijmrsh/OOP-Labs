#pragma once

#include <string>
#include <iostream>
#include <algorithm>
#include <exception>
#include <math.h>

#define EPS 0.01

class Point {
    private:
        double x;
        double y;
    public:
        Point();
        Point(double, double);
        Point(const Point&);
        ~Point() = default;

        double get_x_value() const;
        double get_y_value() const;
        
        bool operator != (const Point&) const;
        bool operator == (const Point&) const;
        Point& operator = (const Point&);
        Point& operator = (Point&&);

        friend std::ostream& operator << (std::ostream& out, const Point& obj);
        friend std::istream& operator >> (std::istream& in, Point& obj);

        static double Distance(const Point&, const Point&);
};