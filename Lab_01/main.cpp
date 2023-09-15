#include <iostream>
#include "gcd.h"

int main() {
    int a, b, result;
    std::cout << "Enter the first number" << '\n';
    std::cin >> a;
    std::cout << "Enter the second number" << '\n';
    std::cin >> b;
    result = gcd(a, b);
    std::cout << "The value of gcd is: " << result << '\n';

    return 0;
}