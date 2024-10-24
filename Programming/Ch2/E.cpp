#include<iostream>
#include<vector>
#include<cmath>
#include<fstream>
#include "Interpolation.hpp"


int main(){
    std::vector<double> x={0,6,10,13,17,20,28};
    std::vector<double> y1={6.67,17.3,42.7,37.3,30.1,29.3,28.7};
    std::vector<double> y2={6.67,16.1,18.9,15.0,10.6,9.44,8.89};
    NewtonInterpolation newton1(x,y1);
    NewtonInterpolation newton2(x,y2);
    std::vector<double> x_vals;
    std::vector<double> y1_vals;
    std::vector<double> y2_vals;
    for(double x_val=0;x_val<=28;x_val+=0.1){
        double y1_val=newton1.interpolate(x_val);
        double y2_val=newton2.interpolate(x_val);
        x_vals.push_back(x_val);
        y1_vals.push_back(y1_val);
        y2_vals.push_back(y2_val);
    }
    save_interpolated_data(x_vals, y1_vals, "AverageWeight1.csv");
    save_interpolated_data(x_vals, y2_vals, "AverageWeight2.csv");
    bool die1=false,die2=false;
    double x_val=29;
    while((!die1 || !die2) && x_val<=44){
        double y1_val=newton1.interpolate(x_val);
        double y2_val=newton2.interpolate(x_val);
        if(y1_val<=0){
            die1=true;
            std::cout << "The first die at " << x_val << " day" << std::endl;
        }
        if(y2_val<=0){
            die2=true;
            std::cout << "The second die at " << x_val << " day" << std::endl;
        }
        x_val++;
    }
    if(!die1){
        std::cout << "The first sample does not die" << std::endl;
    }
    if(!die2){
        std::cout << "The second sample does not die" << std::endl;
    }
}