#include "headers/Figure.hpp"
#include "headers/Point.hpp"
#include "headers/Triangle.hpp"
#include "headers/Square.hpp"
#include "headers/Octagon.hpp"
#include "headers/Array.hpp"


int main() {
    Array arr(0);
    Octagon o;
    Triangle t;
    Square s;
    std::cin >> s;
    arr.push_back(&s);
    std::cin >> t;
    arr.push_back(&t);
    std::cin >> o;
    arr.push_back(&o);
    std::cout << arr;
    std::cout << "common area: " << arr.CommonArea() << '\n';
    std::cout << '\n';
    arr.erase(1);
    std::cout << arr;
    std::cout << "common area: " << arr.CommonArea() << '\n';
    std::cout << '\n';
    arr.pop_back();
    std::cout << arr;
    std::cout << "common area: " << arr.CommonArea() << '\n';
    
    return 0;
}