#include<iostream>
#include "../plotRW.hpp"
#include "../Spline.hpp"

int main(){
    std::vector<double> t;
    std::vector<double> x;
    std::vector<double> y;
    int n = 50;
    for(int i = 0; i < n; i++){
        double j = i * (6.0 * M_PI / n);
        t.push_back(j);
        x.push_back(sin(j)+j*cos(j));
        y.push_back(cos(j)-j*sin(j));
    }

    SplineConfigParams X_param2("B-form", 3, "natural", {0, 0}, t, x, {});
    SplineConfigParams Y_param2("B-form", 3, "natural", {0, 0}, t, y, {});
    BSpline X_even(X_param2);
    BSpline Y_even(Y_param2);
    X_even.SplineConstructor();
    Y_even.SplineConstructor();

    std::vector<double> x_BS;
    std::vector<double> y_BS;
    for(double i = t[0]; i < t[t.size() - 1]; i+=0.01){
        x_BS.push_back(X_even(i));
        y_BS.push_back(Y_even(i));
    }

    PlotRW plot2_even("r2_even.csv");
    plot2_even.write(x_BS, y_BS);
    std::vector<double> t_ccl2 = {0};
    for(int i = 0; i < n  - 1; i++){
        t_ccl2.push_back(sqrt((x[i+1]-x[i])*(x[i+1]-x[i]) + (y[i+1]-y[i])*(y[i+1]-y[i])) + t_ccl2[i]);
    }
    for(int i = 0; i < n; i++){
        t_ccl2[i] = t_ccl2[i] / t_ccl2[n - 1] * 2 * M_PI;
    }
    SplineConfigParams param_x_ccl2("B-form", 3, "natural", {0, 0}, t_ccl2, x, {});
    SplineConfigParams param_y_ccl2("B-form", 3, "natural", {0, 0}, t_ccl2, y, {});
    BSpline S_x_ccl2(param_x_ccl2);
    BSpline S_y_ccl2(param_y_ccl2);
    S_x_ccl2.SplineConstructor();
    S_y_ccl2.SplineConstructor();
    std::vector<double> x_new_ccl2, y_new_ccl2;
    for(double i = 0.0; i <= 2 * M_PI; i += 0.01){
        x_new_ccl2.push_back(S_x_ccl2(i));
        y_new_ccl2.push_back(S_y_ccl2(i));
    }
    PlotRW plot_ccl2("r2_CCL.csv");
    plot_ccl2.write(x_new_ccl2, y_new_ccl2);

    t.clear(); x.clear(); y.clear();
    std::vector<double> z;
    for(int i = 0; i < n; i++){
        double j = i * (2.0 * M_PI / n);
        t.push_back(j);
        x.push_back(sin(cos(j))*cos(sin(j)));
        y.push_back(sin(cos(j))*sin(sin(j)));
        z.push_back(cos(cos(j)));
    }


    SplineConfigParams X_param3("B-form", 3, "natural", {0, 0}, t, x, {});
    SplineConfigParams Y_param3("B-form", 3, "natural", {0, 0}, t, y, {});
    SplineConfigParams Z_param3("B-form", 3, "natural", {0, 0}, t, z, {});
    BSpline X_3(X_param3);
    BSpline Y_3(Y_param3);
    BSpline Z_3(Z_param3);
    X_3.SplineConstructor();
    Y_3.SplineConstructor();
    Z_3.SplineConstructor();

    std::vector<double> x_BS3;
    std::vector<double> y_BS3;
    std::vector<double> z_BS3;
    for(double i = t[0]; i < t[t.size() - 1]; i+=0.01){
        x_BS3.push_back(X_3(i));
        y_BS3.push_back(Y_3(i));
        z_BS3.push_back(Z_3(i));
    }

    PlotRW plot("r3_even.csv");
    plot.write(x_BS3, y_BS3, z_BS3);
    std::vector<double> t_ccl = {0};
    for(int i = 0; i < n  - 1; i++){
        t_ccl.push_back(sqrt((x[i+1]-x[i])*(x[i+1]-x[i]) + (y[i+1]-y[i])*(y[i+1]-y[i]) + (z[i+1]-z[i])*(z[i+1]-z[i])) + t_ccl[i]);
    }
    for(int i = 0; i < n; i++){
        t_ccl[i] = t_ccl[i] / t_ccl[n - 1] * 2 * M_PI;
    }
    SplineConfigParams param_x_ccl("B-form", 3, "natural", {0, 0}, t_ccl, x, {});
    SplineConfigParams param_y_ccl("B-form", 3, "natural", {0, 0}, t_ccl, y, {});
    SplineConfigParams param_z_ccl("B-form", 3, "natural", {0, 0}, t_ccl, z, {});
    BSpline S_x_ccl(param_x_ccl);
    BSpline S_y_ccl(param_y_ccl);
    BSpline S_z_ccl(param_z_ccl);
    S_x_ccl.SplineConstructor();
    S_y_ccl.SplineConstructor();
    S_z_ccl.SplineConstructor();
    std::vector<double> x_new_ccl, y_new_ccl,z_new_ccl;
    for(double i = 0.0; i <= 2 * M_PI; i += 0.01){
        x_new_ccl.push_back(S_x_ccl(i));
        y_new_ccl.push_back(S_y_ccl(i));
        z_new_ccl.push_back(S_z_ccl(i));
    }
    PlotRW plot_ccl("r3_CCL.csv");
    plot_ccl.write(x_new_ccl, y_new_ccl,z_new_ccl);
}