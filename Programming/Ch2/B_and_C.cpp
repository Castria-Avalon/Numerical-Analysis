#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include "Interpolation.hpp"

double function(double x){
    return 1/(1 + x*x);
}

double function2(double x){
    return 1/(1 + 25*x*x);
}

int main(){
    //Code for Problem B
    std::vector<int> n = {2, 4, 6, 8};
    std::vector<int>::iterator it;
    for(it = n.begin(); it != n.end(); it++){
        std::vector<double> x;
        std::vector<double> y;
        for(int i = 0; i <= *it; i++){
            x.push_back(-5 + 10*i/(*it));
            y.push_back(function(x[i]));
        }
        std::vector<double> x_vals;
        std::vector<double> y_vals;
        for(double i = -5; i <= 5; i += 0.1){
            x_vals.push_back(i);
            NewtonInterpolation newton(x, y);
            y_vals.push_back(newton.interpolate(i));
        }
        save_interpolated_data(x_vals, y_vals, "NewtonInterpolation_n_" + std::to_string(*it) + ".csv");
    }

    //Code for Problem C
    std::vector<int> n2 = {5, 10, 15, 20};
    std::vector<int>::iterator it2;
    for(it2 = n2.begin(); it2 != n2.end(); it2++){
        std::vector<double> x;
        std::vector<double> y;
        for(int i = 0; i <= *it2; i++){
            x.push_back(chebyshev_point(-1, 1, *it2, i));
            y.push_back(function2(x[i]));
        }
        std::vector<double> x_vals;
        std::vector<double> y_vals;
        for(double i = -1; i <= 1; i += 0.05){
            x_vals.push_back(i);
            NewtonInterpolation newton_for_chebyshev(x, y);
            y_vals.push_back(newton_for_chebyshev.interpolate(i));
        }
        save_interpolated_data(x_vals, y_vals, "NewtonInterpolation_Chebyshev_n_" + std::to_string(*it2) + ".csv");
    }
}