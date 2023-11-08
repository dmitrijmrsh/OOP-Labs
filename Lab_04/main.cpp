#include "headers/Figure.hpp"
#include "headers/Square.hpp"
#include "headers/Triangle.hpp"
#include "headers/Octagon.hpp"
#include "headers/Array.hpp"

int main() {
    std::cout.precision(3);
    std::cout << std::fixed;
    Array<Figure<double>*> arr(0);
    Octagon<double> o;
    Triangle<double> t;
    Square<double> s;
    std::cin >> s;
    arr.push_back(&s);
    std::cin >> t;
    arr.push_back(&t);
    std::cin >> o;
    arr.push_back(&o);
    for (int i = 0; i < arr.getsize(); ++i) {
        std::cout << arr[i]->getname() << " area: " << arr[i]->Area() << " center: " << arr[i]->Center() << '\n'; 
    }
    std::cout << '\n';
    arr.erase(1);
    for (int i = 0; i < arr.getsize(); ++i) {
        std::cout << arr[i]->getname() << " area: " << arr[i]->Area() << " center: " << arr[i]->Center() << '\n'; 
    }
    std::cout << '\n';
    arr.pop_back();
    for (int i = 0; i < arr.getsize(); ++i) {
        std::cout << arr[i]->getname() << " area: " << arr[i]->Area() << " center: " << arr[i]->Center() << '\n'; 
    }
    std::cout << '\n';

    Array<Figure<int>*> other_arr;
    Square<int> other_s;
    std::cin >> other_s;
    other_arr.push_back(&other_s);
    for (int i = 0; i < other_arr.getsize(); ++i) {
        std::cout << other_arr[i]->getname() << " area: " << other_arr[i]->Area() << " center: " << other_arr[i]->Center() << '\n'; 
    }
    std::cout << '\n';

    return 0;
}