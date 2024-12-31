#include<iostream>
#include "../plotRW.hpp"
#include "../Spline.hpp"

std::pair<double, double> Projection(std::vector<double> &a, double R){
    double x = a[0];
    double y = a[1];
    double z = a[2];
    std::pair<double, double> point;
    point.first = R * x / (R - z);
    point.second = R * y / (R - z);
    return point;
}

std::vector<double> Inverse_Projection(const std::pair<double, double> &a, double R){
    double x = a.first;
    double y = a.second;
    std::vector<double> point;
    point.push_back(2 * R * x / (R * R + (x * x + y * y)));
    point.push_back(2 * R * y / (R * R + (x * x + y * y)));
    point.push_back(R * ((x * x + y * y) - R * R) / (R * R + x * x + y * y));
    return point;
}

std::vector<double> curve_build(double R, double t){
    std::vector<double> point;
    double theta = t;
    double phi = M_PI / 4 * sin(t);

    double x = R * cos(theta) * cos(phi);
    double y = R * sin(theta) * cos(phi);
    double z = R * sin(phi);

    point.push_back(x);
    point.push_back(y);
    point.push_back(z);

    return point;
}


int main(){
    double R = 1;
    std::vector<double> BoundaryVal = {0.0, 0.0};
    int deg = 3;
    std::vector<double> t;
    std::vector<double> x;
    std::vector<double> y;
    std::vector<std::pair<double, double>> intervals;

    for(double i = 0; i < 2 * M_PI; i+=0.01){
        t.push_back(i);
        std::vector<double> point = curve_build(R, i);
        std::pair<double, double> proj_point = Projection(point, R);
        x.push_back(proj_point.first);
        y.push_back(proj_point.second);
        if(i != 0){
            intervals.push_back(std::make_pair(i - 1, i));
        }
    }

    SplineConfigParams X_param("B-form", deg, "periodic", BoundaryVal, t, x, intervals);
    SplineConfigParams Y_param("B-form", deg, "periodic", BoundaryVal, t, y, intervals);
    BSpline X_Spline(X_param);
    BSpline Y_Spline(Y_param);
    X_Spline.SplineConstructor();
    Y_Spline.SplineConstructor();

    std::vector<double> x_BS;
    std::vector<double> y_BS;
    std::vector<double> z_BS;
    for(double i = t[0]; i < t[t.size() - 1]; i+=0.01){
        std::vector<double> point = Inverse_Projection(std::make_pair(X_Spline(i), Y_Spline(i)), R);
        x_BS.push_back(point[0]);
        y_BS.push_back(point[1]);
        z_BS.push_back(point[2]);
    }

    PlotRW plot("plot_sphere.csv");
    plot.write(x_BS, y_BS, z_BS);

    return 0;

}