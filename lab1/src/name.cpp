#include "name.hpp"

std::string getName() {
    std::string name;
    std::cout << "Please enter your name: ";
    std::getline(std::cin, name);
    return name;
}