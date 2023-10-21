#pragma once

#include "Point.hpp"
#include <string>
#include <iostream>
#include <algorithm>
#include <exception>
#include <math.h>

class Figure {
    protected:
        std::string name;

        virtual void print(std::ostream&) = 0;
        virtual void input(std::istream&) = 0;
        virtual void check_constructor(const Figure&) const = 0;
    public:
        Figure() = default;
        Figure(const std::string&);

        const std::string& getname() const;
        virtual Point Center() const = 0;
        virtual double Area() const = 0;

        virtual bool operator == (const Figure&) const = 0;
        explicit virtual operator double() const = 0;

        virtual ~Figure() = default;
};