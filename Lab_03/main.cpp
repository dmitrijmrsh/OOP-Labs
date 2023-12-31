#include "headers/Figure.hpp"
#include "headers/Point.hpp"
#include "headers/Triangle.hpp"
#include "headers/Square.hpp"
#include "headers/Octagon.hpp"
#include "headers/Array.hpp"


int main() {
    std::cout.precision(3);
    std::cout << std::fixed;
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
    std::cout << "Square area: " << s.Area() << " center: " << s.Center() << '\n';
    std::cout << "Triangle area: " << t.Area() << " center: " << t.Center() << '\n';
    std::cout << "Octagon area: " << o.Area() << " center: " << o.Center() << '\n';
    std::cout << '\n';
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