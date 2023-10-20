#include "../headers/Figure.hpp"

Figure::Figure(const std::string& name) {
    this->name = name;
}

const std::string& Figure::getname() const {
    return name;
}