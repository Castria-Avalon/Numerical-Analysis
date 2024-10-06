#include<iostream>
#include "SciCal.hpp"

#define PI 3.14159265358979323846

int main() {
    Function f("pow(2,-x)+exp(x)+2*cos(x)-6");
    std::cout << f(3) << std::endl;
    return 0;
}