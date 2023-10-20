#include <iostream>
#include "headers/Figure.hpp"
#include "headers/Point.hpp"
#include "headers/Triangle.hpp"
#include "headers/Square.hpp"
#include "headers/Octagon.hpp"

int main() {
    Square s1(Point(-2, -2), Point(-2, 2), Point(2, 2), Point(2, -2));
    Square s2;
    s2 = s1;
    if (s2 == s1) {
        std::cout << "YES" << std::endl;
    }
    
    return 0;
}