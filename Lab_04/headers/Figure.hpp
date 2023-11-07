#pragma once

#include "Point.hpp"

template<Numeric T>
class Figure {
    protected:
        std::string name;

        virtual void check_constructor(const Figure<T>&) const = 0;
    public:
        Figure() = default;
        Figure(const std::string&);

        const std::string& getname() const;
        virtual Point<T> Center() const = 0;
        virtual double Area() const = 0;

        virtual bool operator == (const Figure<T>&) const = 0;
        explicit virtual operator double() const = 0;

        virtual ~Figure() = default;
};

template<Numeric T>
Figure<T>::Figure(const std::string& name) {
    this->name = name;
}

template<Numeric T>
const std::string& Figure<T>::getname()  const {
    return name;
}