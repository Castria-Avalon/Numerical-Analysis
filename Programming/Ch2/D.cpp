#include<iostream>
#include<vector>
#include<cmath>
#include<fstream>
#include"Interpolation.hpp"

#define MAX_V 81

double derivative(double x, HermiteInterpolation& hermite, double h=1e-5){
    return (hermite.interpolate(x+h)-hermite.interpolate(x))/h;
}

int main(){
    std::vector<double> x={0,0,3,3,5,5,8,8,13,13};
    std::vector<double> y={0,75,225,77,383,80,623,74,993,72};
    HermiteInterpolation hermite(x,y);
    
    std::cout << "When t=10s, the car's position:" << hermite.interpolate(10) << std::endl;
    std::cout << "When t=10s, the car's speed:" << derivative(10, hermite) << std::endl;

    for(double x_val=0;x_val<=13;x_val+=0.1){
        double v=derivative(x_val,hermite);
        if(v>MAX_V){
            std::cout << "The car's speed exceeds the maximum speed at t=" << x_val << "s" << std::endl;
        }
    }
}
