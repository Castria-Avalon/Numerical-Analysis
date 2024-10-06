#include "SciCal.hpp"
#include "EquationSolver.hpp"
#include <iostream>
#include <cmath>

const double Pi = acos(-1.);

int main() {
    std::cout << "The answer of question B:" << std::endl;
    Function F1("1.0/x-tan(x)");
    Function F2("pow(x,-1)-pow(2,x)");
    Function F3("pow(2,-x)+exp(x)+2*cos(x)-6");
    Function F4("(pow(x,3)+4*pow(x,2)+3*x+5)/(2*pow(x,3)-9*pow(x,2)+18*x-2)");
    Bisection_Method solver_f1(F1, 0, Pi/2);
    Bisection_Method solver_f2(F2, 0, 1);
    Bisection_Method solver_f3(F3, 1, 3);
    Bisection_Method solver_f4(F4, 0, 4);
    std::cout << "Root of f1: " << solver_f1.solve() << std::endl;
    std::cout << "Root of f2: " << solver_f2.solve() << std::endl;
    std::cout << "Root of f3: " << solver_f3.solve() << std::endl;
    std::cout << "Root of f4: " << solver_f4.solve() << std::endl;
    std::cout << "The answer of question B is done." << std::endl;
    std::cout << "=============================================" << std::endl;
    return 0;
}