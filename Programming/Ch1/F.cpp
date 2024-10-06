#include "SciCal.hpp"
#include "EquationSolver.hpp"
#include <iostream>
#include <cmath>

int main() {
    std::cout << "The answer of question F:" << std::endl;
    Function F_a("89*sin(11.5/180*acos(-1))*sin(x)*cos(x)+89*cos(11.5/180*acos(-1))*sin(x)*sin(x)-((49+0.5*30)*sin(11.5/180*acos(-1))-0.5*30*tan(11.5/180*acos(-1)))*cos(x)-((49+0.5*30)*cos(11.5/180*acos(-1))-0.5*30)*sin(x)");
    Newton_Method solver_f1(F_a, 0.57596);
    Function F_b("89*sin(11.5/180*acos(-1))*sin(x)*cos(x)+89*cos(11.5/180*acos(-1))*sin(x)*sin(x)-((49+0.5*30)*sin(11.5/180*acos(-1))-0.5*30*tan(11.5/180*acos(-1)))*cos(x)-((49+0.5*30)*cos(11.5/180*acos(-1))-0.5*30)*sin(x)");
    Newton_Method solver_f2(F_b, 0.57596);
    Secant_Method solver_f3(F_b, 0.57596, 3.14159);
    Secant_Method solver_f4(F_b, 0.57596, 5);
    Secant_Method solver_f5(F_b, 0.57596, 6);
    std::cout << "Root of a: " << solver_f1.solve() << std::endl;
    std::cout << "Root of b: " << solver_f2.solve() << std::endl;
    std::cout << "Root of c: " << solver_f3.solve() << std::endl;
    std::cout << "Root of c(anther initial value): " << solver_f4.solve() << std::endl;
    std::cout << "Root of c(anther initial value): " << solver_f5.solve() << std::endl;
    std::cout << "The answer of question F is done." << std::endl;
    std::cout << "=============================================" << std::endl;
    return 0;
}