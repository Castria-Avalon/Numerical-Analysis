// Interpolation.cpp
#include <iostream>
#include <vector>
#include "Interpolation.hpp"

NewtonInterpolation::NewtonInterpolation(std::vector<double> x, std::vector<double> y)
{
    this->x = x;
    this->y = y;
}

double NewtonInterpolation::divided_diff(int i, int j)
{
    if (i == j)
    {
        return y[i];
    }
    if (i + 1 == j)
    {
        return (y[j] - y[i]) / (x[j] - x[i]);
    }
    return (divided_diff(i + 1, j) - divided_diff(i, j - 1)) / (x[j] - x[i]);
}

double NewtonInterpolation::interpolate(double x_val)
{
    double result = 0;
    for (int i = 0; i < x.size(); i++)
    {
        double term = divided_diff(0, i);
        for (int j = 0; j < i; j++)
        {
            term *= (x_val - x[j]);
        }
        result += term;
    }
    return result;
}

HermiteInterpolation::HermiteInterpolation(std::vector<double> x, std::vector<double> y)
{
    this->x = x;
    this->y = y;
}

double HermiteInterpolation::divided_diff(int i, int j)
{
    if (i == j)
    {
        if(i>0 && x[i]==x[i-1]){
            return y[i-1];
        }else{
            return y[i];
        }
    }
    else if (x[i] == x[j])
    {
        return y[j];
    }
    else
    {
        return (divided_diff(i + 1, j) - divided_diff(i, j - 1)) / (x[j] - x[i]);
    }
}

double HermiteInterpolation::interpolate(double x_val)
{
    double result = 0;
    for (int i = 0; i < x.size(); i++)
    {
        double term = divided_diff(0, i);
        for (int j = 0; j < i; j++)
        {
            term *= (x_val - x[j]);
        }
        result += term;
    }
    return result;
}

double chebyshev_point(double a, double b, int n, int i)
{
    return 0.5 * (a + b) + 0.5 * (b - a) * cos((2 * i + 1) * M_PI / (2 * n + 2));
}

void save_interpolated_data(const std::vector<double>& x_vals, const std::vector<double>& y_vals, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (size_t i = 0; i < x_vals.size(); ++i) {
            file << x_vals[i] << "," << y_vals[i] << "\n";  // Writing data as CSV
        }
        file.close();
    }
}