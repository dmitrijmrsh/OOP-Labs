#include <iostream>
#include "Hex.hpp"

int main() {
    std::string a = "";
    std::string b = "123";
    if (b < a) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }

    return 0;
}