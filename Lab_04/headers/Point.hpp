#pragma once

#include <iostream>
#include <string>
#include <exception>
#include <concepts>
#include <type_traits>
#include <math.h>
#include <vector>

#define EPS 0.187

template<typename T>
concept Numeric = std::is_arithmetic_v<T>;

template<Numeric T>
class Point {
    private:
        T x;
        T y;
    public:
        Point();
        Point(const T&, const T&);
        Point(const Point<T>&);

        T get_x_value() const;
        T get_y_value() const;

        bool operator != (const Point<T>&) const;
        bool operator == (const Point<T>&) const;
        Point<T>& operator = (const Point<T>&);
        Point<T>& operator = (Point<T>&&);

        static double Distance(const Point<T>&, const Point<T>&);

        friend std::ostream& operator << (std::ostream& out, const Point<T>& obj);
        friend std::istream& operator >> (std::istream& in, Point<T>& obj);

        ~Point() = default;
};

template<Numeric T>
Point<T>::Point() {
    x = 0;
    y = 0;
}

template<Numeric T>
Point<T>::Point(const T& x, const T& y) {
    this->x = x;
    this->y = y;
}

template<Numeric T> 
Point<T>::Point(const Point<T>& p) {
    x = p.x;
    y = p.y;
}

template<Numeric T>
T Point<T>::get_x_value() const {
    return x;
}

template<Numeric T>
T Point<T>::get_y_value() const {
    return y;
}

template<Numeric T>
double Point<T>::Distance(const Point<T>& left, const Point<T>& right) {
    return sqrt((left.x - right.x) * (left.x - right.x) + (left.y - right.y) * (left.y - right.y));
}

template<Numeric T>
bool Point<T>::operator == (const Point<T>& p) const {
    if (Distance(*this, p) <= 0.01) {
        return true;
    }
    return false;
}

template<Numeric T>
bool Point<T>::operator != (const Point<T>& p) const {
    return !(*this == p);
}

template<Numeric T>
Point<T>& Point<T>::operator = (const Point<T>& other) {
    if (this != other) {
        x = other.x;
        y = other.y;
    }
    return *this;
}

template<Numeric T>
Point<T>& Point<T>::operator = (Point&& other) {
    if (this != &p) {
        x = p.x;
        y = p.y;

        p.x = 0;
        p.y = 0;
    }
    return *this;
}

template<Numeric T>
std::ostream& operator << (std::ostream& out, const Point<T>& obj) {
    out << "x: " << obj.get_x_value() << "y: " << obj.get_y_value();
    return out;
}

template<Numeric T>
std::istream& operator >> (std::istream& in, Point<T>& obj) {
    in >> obj.x >> obj.y;
    return in;
}