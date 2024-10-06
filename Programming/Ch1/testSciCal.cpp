#include<iostream>
#include "SciCal.hpp"

#define PI 3.14159265358979323846

int main() {
    Function f("89*sin(0.2007))*sin(x)*cos(x)+89*cos(0.2007)*sin(x)*sin(x)-((49+0.5*55)*sin(0.2007)-0.5*55*tan(0.2007))*cos(x)-((49+0.5*55)*cos(0.2007)-0.5*55)*sin(x)");
    std::cout << f(8.5393e-06) << std::endl;
    return 0;
}