#ifndef EQUATIONSOLVER
#define EQUATIONSOLVER

#include "SciCal.hpp"

class EquationSolver{
protected:
    Function F;
public:
    EquationSolver(const Function& F) : F(F) {}
    virtual double solve() = 0;
};

class Bisection_Method : public EquationSolver {
private:
    double a, b;
    double eps, delta;
    int Maxiter;
public:
    Bisection_Method(const Function &F, double a, double b, 
        double eps = 1e-7, double delta = 1e-6, int Maxiter = 100) :
        EquationSolver(F), a(a), b(b), eps(eps), delta(delta), Maxiter(Maxiter) {}
    
    double solve() {
        if (F(a) * F(b) > 0) {
            throw std::invalid_argument("Function must have opposite signs at endpoints a and b");
        }

        int iter = 0;
        double h=b-a;
        double u=F(a);
        while (std::abs(h)>delta && iter<Maxiter) {
            h/=2;
            double c=a+h;
            double v=F(c);
            if (std::abs(v) < eps) return c;
            if (u*v<=0) b=c;
            else {
                a=c;
                u=v;
            }
            iter++;
        }
        return (a+b)/2;
    }
};

class Newton_Method : public EquationSolver {
private:
    double x0;
    double eps;
    int Maxiter;
public:
    Newton_Method(const Function &F, double x0, 
        double eps = 1e-7, double Maxiter = 8) :
        EquationSolver(F), x0(x0), eps(eps), Maxiter(Maxiter) {}
    
    double solve() {
        while(Maxiter--) {
            double x1=x0-F(x0)/F.derivative(x0);
            if (fabs(x1-x0)<eps) return x1;
            x0=x1;
        }
        return x0;
    }
};

class Secant_Method : public EquationSolver {
private:
    double x0, x1;
    double delta,eps;
    int Maxiter;
public:
    Secant_Method(const Function &F, double x0, double x1, 
        double delta = 1e-6, double eps = 1e-7, double Maxiter = 8) :
        EquationSolver(F), x0(x0), x1(x1), delta(delta),eps(eps), Maxiter(Maxiter) {}
    
    double solve() {
        double u,v;
        u=F(x0); v=F(x1);
        while(Maxiter--) {
            double x2=x1-v*(x1-x0)/(v-u);
            if (fabs(x2-x1)<delta) return x2;
            x0=x1, x1=x2;
            u=v, v=F(x2);
            if(fabs(v)<eps) return x2;
        }
        return x1;
    }
};

#endif