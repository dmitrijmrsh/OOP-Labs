#include <iostream>
#include <map>
#include <stdlib.h>
#include "headers/Vector.hpp"

int Factorial(int value) {
    int result = 1;

    for (int i = 1; i <= value; ++i) {
        result *= i;
    }

    return result;
}

int main() {
    std::map<int, int, std::less<int>, Allocator<std::pair<const int, int>, 5000>> test1;

    for (int i = 0; i < 10; ++i) {
        test1[i] = Factorial(i);
    }

    for (auto it = test1.begin(); it != test1.end(); ++it) {
        std::cout << it->first << " " << it->second << std::endl;
    }
    std::cout << std::endl;

    Vector<int, Allocator<int, 5000>> vec;
    for (int i = 0; i < 10; ++i) {
        vec.push_back(Factorial(i));
    }

    for (auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << std::endl;
    }

    const size_t allocated_blocks = 20000;
    std::map<int, int, std::less<int>, Allocator<std::pair<const int, int>, allocated_blocks>> test2;

    int count = rand() % allocated_blocks;
    if (count < 1000) {
        count = 1000;
    }

    int first_value, second_value, erase_value;
    for (int i = 0; i < count; ++i) {
        first_value = rand();
        second_value = rand();
        erase_value = rand();
        test2.emplace(first_value, second_value);

        auto it = test2.find(erase_value);
        if (it != test2.end()) {
            test2.erase(it);
        }
    }

    return 0;
}