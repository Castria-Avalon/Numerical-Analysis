#include<iostream>
#include "../plotRW.hpp"
#include "../Spline.hpp"



int main(){
    std::vector<int> N = {10, 40, 160};
    std::vector<double> t, x, y;
    for(const auto& n : N){
        t.clear();
        x.clear();
        y.clear();
        for(int j = 0; j < n; j++){
            double i = j *((2.0 * M_PI) / n);
            t.push_back(i);
            x.push_back(sqrt(3) * cos(i));
            y.push_back(2.0 / 3.0 * (sqrt(3)*sin(i) + sqrt(fabs(sqrt(3)*cos(i)))));
        }
        std::cout << std::endl;
        std::cout << std::endl;
        SplineConfigParams param_x("B-form", 3, "natural", {0, 0}, t, x, {});
        SplineConfigParams param_y("B-form", 3, "natural", {0, 0}, t, y, {});
        BSpline S_x(param_x);
        BSpline S_y(param_y);
        S_x.SplineConstructor();
        S_y.SplineConstructor();
        std::vector<double> x_new, y_new;
        for(double i = 0.0; i <= 2 * M_PI; i += 0.01){
            x_new.push_back(S_x(i));
            y_new.push_back(S_y(i));
        }
        std::string filename = "HeartCurve_" + std::to_string(n) + ".csv";
        PlotRW plot(filename);
        plot.write(x_new, y_new);
        std::vector<double> t_ccl = {0};
        for(int i = 0; i < n  - 1; i++){
            t_ccl.push_back(sqrt((x[i+1]-x[i])*(x[i+1]-x[i]) + (y[i+1]-y[i])*(y[i+1]-y[i])) + t_ccl[i]);
        }
        for(int i = 0; i < n; i++){
            t_ccl[i] = t_ccl[i] / t_ccl[n - 1] * 2 * M_PI;
        }
        SplineConfigParams param_x_ccl("B-form", 3, "natural", {0, 0}, t_ccl, x, {});
        SplineConfigParams param_y_ccl("B-form", 3, "natural", {0, 0}, t_ccl, y, {});
        BSpline S_x_ccl(param_x_ccl);
        BSpline S_y_ccl(param_y_ccl);
        S_x_ccl.SplineConstructor();
        S_y_ccl.SplineConstructor();
        std::vector<double> x_new_ccl, y_new_ccl;
        for(double i = 0.0; i <= 2 * M_PI; i += 0.01){
            x_new_ccl.push_back(S_x_ccl(i));
            y_new_ccl.push_back(S_y_ccl(i));
        }
        std::string filename_ccl = "HeartCurve_CCL_" + std::to_string(n) + ".csv";

        PlotRW plot_ccl(filename_ccl);
        plot_ccl.write(x_new_ccl, y_new_ccl);
    }
}