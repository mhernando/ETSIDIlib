#include "Errors.h"

#include <cstdlib>

#include <iostream>


//Prints out an error message and exits 
void fatalError(std::string errorString) {
    std::cout << errorString << std::endl;
    std::cout << "Enter any key to quit...";
    int tmp;
    std::cin >> tmp;
    
    exit(69);
}