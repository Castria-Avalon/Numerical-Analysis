#include "SciCal.hpp"
#include "EquationSolver.hpp"
#include <iostream>
#include <cmath>

const double Pi = acos(-1.);

int main() {
    std::cout << "The answer of question E:" << std::endl;
    Function F("12.4-(10*(0.5*acos(-1.)-asin(x)-x*pow(1-x*x,0.5)))");
    Bisection_Method solver_f1(F, 0.125, 0.2);
    Newton_Method solver_f2(F, 0.25);
    Secant_Method solver_f3(F, 0.25, 0.5);
    std::cout << "Root solved by the bisection method: " << solver_f1.solve() << std::endl;
    std::cout << "Root solved by the Netton's method: " << solver_f2.solve() << std::endl;
    std::cout << "Root solved by the secant method: " << solver_f3.solve() << std::endl;
    std::cout << "The answer of question E is done." << std::endl;
    std::cout << "=============================================" << std::endl;
    return 0;
}