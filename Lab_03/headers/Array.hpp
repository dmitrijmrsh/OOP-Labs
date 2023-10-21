#include "Figure.hpp"
#include <iostream>
#include <string.h>

class Array {
    private:
        size_t size;
        size_t capacity;
        Figure** arr;

        void reallocate(size_t);
    public:
        Array();
        Array(size_t);

        void push_back(Figure*);
        void pop_back();
        void erase(size_t);
        Figure* operator[] (size_t);
        Point FigureCenter(size_t);
        double FigureArea(size_t);
        double CommonArea();
        size_t getsize();
        size_t getcapacity();

        ~Array();
};