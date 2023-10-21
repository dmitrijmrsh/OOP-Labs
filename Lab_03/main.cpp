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
    std::cout << '\n';
    Point center;
    double area;
    for (size_t i = 0; i < arr.getsize(); ++i) {
        std::cout << arr[i]->getname() << " ";
        center = arr.FigureCenter(i);
        std::cout << "center: " << center << " ";
        area = arr.FigureArea(i);
        std::cout << "area: " << area << '\n';
    }
    std::cout << "common area: " << arr.CommonArea() << '\n';
    arr.erase(1);
    for (size_t i = 0; i < arr.getsize(); ++i) {
        std::cout << arr[i]->getname() << " ";
        center = arr.FigureCenter(i);
        std::cout << "center: " << center << " ";
        area = arr.FigureArea(i);
        std::cout << "area: " << area << '\n';;
    }
    std::cout << "common area: " << arr.CommonArea() << '\n';
    arr.pop_back();
    for (size_t i = 0; i < arr.getsize(); ++i) {
        std::cout << arr[i]->getname() << " ";
        center = arr.FigureCenter(i);
        std::cout << "center: " << center << " ";
        area = arr.FigureArea(i);
        std::cout << "area: " << area << '\n';
    }
    std::cout << "common area: " << arr.CommonArea() << '\n';
    
    return 0;
}