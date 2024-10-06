#include "SciCal.hpp"
#include "EquationSolver.hpp"
#include <iostream>
#include <cmath>

const double Pi = acos(-1.);

int main() {
    std::cout << "The answer of question C:" << std::endl;
    Function F("x-tan(x)");
    Newton_Method solver_f1(F, 7.7);
    Newton_Method solver_f2(F, 4.5);
    std::cout << "Root of f: " << solver_f1.solve() << std::endl;
    std::cout << "Root of f: " << solver_f2.solve() << std::endl;
    std::cout << "The answer of question C is done." << std::endl;
    std::cout << "=============================================" << std::endl;
    return 0;
}