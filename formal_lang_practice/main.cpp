#include "regular.h"
#include <string>
#include <iostream>

int main() {
    std::string expr, patt;
    std::cout << "Enter your expression: \n";
    std::cin >> expr;
    std::cout << "Enter your string: \n" ;
    std::cin >> patt;
    regular current(expr, patt);
    std::cout << "Longest common suffix'es size: "<< current.longest_common_suffix();
    return 0;
}
