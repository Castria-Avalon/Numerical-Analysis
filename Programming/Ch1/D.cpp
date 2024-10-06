#include "SciCal.hpp"
#include "EquationSolver.hpp"
#include <iostream>
#include <cmath>

const double Pi = acos(-1.);

int main() {
    std::cout << "The answer of question D:" << std::endl;
    Function F1("sin(x/2)-1");
    Function F2("exp(x)-tan(x)");
    Function F3("pow(x,3)-12*pow(x,2)+3*x+1");
    Secant_Method solver_f1(F1, 0, Pi/2);
    Secant_Method solver_f1_(F1, 0, Pi);
    Secant_Method solver_f2(F2, 1, 1.4);
    Secant_Method solver_f2_(F2, 0.5, 1);
    Secant_Method solver_f3(F3, 0, -0.5);
    Secant_Method solver_f3_(F3, 0, -1);
    std::cout << "Root of f1: " << solver_f1.solve() << std::endl;
    std::cout << "Root of f1(another initial value): " << solver_f1_.solve() << std::endl;
    std::cout << "Root of f2: " << solver_f2.solve() << std::endl;
    std::cout << "Root of f2(another initial value): " << solver_f2_.solve() << std::endl;
    std::cout << "Root of f3: " << solver_f3.solve() << std::endl;
    std::cout << "Root of f3(another initial value): " << solver_f3_.solve() << std::endl;
    std::cout << "The answer of question D is done." << std::endl;
    std::cout << "=============================================" << std::endl;
    return 0;
}