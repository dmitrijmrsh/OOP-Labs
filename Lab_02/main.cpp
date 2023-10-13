#include <iostream>
#include "./header/Hex.hpp"

int main() {
    Hex a("1000000");
    Hex b("999000");
    a -= b;
    std::cout << a << ' ' << a.getsize() << std::endl;

    return 0;
}