#include <iostream>
#include "Hex.hpp"

int main() {
    Hex a("1000000");
    Hex b{'9','9','9','0','0','0'};
    a = a - b;
    std::cout << a << std::endl;

    return 0;
}