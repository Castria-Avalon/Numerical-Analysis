#ifndef _INTERPOLATION_HPP
#define _INTERPOLATION_HPP

#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <functional>

class Interpolation{
public:
    virtual double interpolate(double x_val) = 0; 
protected:
    std::vector<double> x;
    std::vector<double> y;

};

class NewtonInterpolation : public Interpolation{
public:
    NewtonInterpolation(std::vector<double> x, std::vector<double> y);
    double interpolate(double x_val) override;

private:    
    double divided_diff(int i, int j);

};

class HermiteInterpolation : public Interpolation{
public:
    HermiteInterpolation(std::vector<double> x, std::vector<double> y);
    double interpolate(double x_val) override;

private:
    double divided_diff(int i, int j);

};


double chebyshev_point(double a, double b, int n, int i);

void save_interpolated_data(const std::vector<double>& x_vals, const std::vector<double>& y_vals, const std::string& filename);

#endif // _INTERPOLATION_HPP