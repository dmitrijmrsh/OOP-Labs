#include <iostream>
#include "Hex.hpp"

int main() {
    Hex a{};
    Hex b("12345");
    a -= b;
    std::cout << a.getvalue() << std::endl;

    return 0;
}