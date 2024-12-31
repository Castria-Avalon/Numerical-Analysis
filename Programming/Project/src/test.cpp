#include<iostream>
#include "Spline.hpp"
#include "plotRW.hpp"

int main(){
    SplineConfigParams params_pp("ConfigParams/ppform_test.json");
    SplineConfigParams params_B("ConfigParams/B_test.json");
    ppSpline S_pp(params_pp);
    BSpline S_B(params_B);
    S_pp.SplineConstructor();
    S_B.SplineConstructor();

    std::vector<double> x;
    std::vector<double> y_pp;
    std::vector<double> y_B;

    for(double i = params_pp.getNodes()[0]; i < params_pp.getNodes()[params_pp.getNodes().size() - 1]; i+=0.01){
        x.push_back(i);
        y_pp.push_back(S_pp(i));
        y_B.push_back(S_B(i));
    }
    PlotRW plot("plot_pp.csv");
    plot.write(x, y_pp);
    PlotRW plot2("plot_B.csv");
    plot2.write(x, y_B);

    return 0;
}