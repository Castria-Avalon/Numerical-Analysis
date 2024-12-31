#include<iostream>
#include<cmath>
#include "../plotRW.hpp"

double truncatedPower(double t, double x, int n) {
    return t > x ? pow(t - x, n) : 0.0;
}

double dividedDifference(const std::vector<double>& knots, int n, double x, int i, int j) {
    if (i == j) return truncatedPower(knots[i], x, n); // Base case
    return (dividedDifference(knots, n, x, i + 1, j) - dividedDifference(knots, n, x, i, j - 1)) / (knots[j] - knots[i]);
}

std::vector<double> generateKnots(int n) {
    std::vector<double> knots = {0.0};
    for (int i = 1.0; i <= n + 1; i++) {
        double t = 0.0 + i;
        knots.push_back(t);
    }
    return knots;
}

void dividedDifferenceTable(const std::vector<double>& knots, int n, int i, int j) {
    std::vector<double> x_vals;
    std::vector<double> y_vals;
    for(double x = -1.0; x <= knots[n + 1]; x += 0.05){
        x_vals.push_back(x);
        y_vals.push_back(dividedDifference(knots, n, x, i, j));
    }
    std::string filename = "TruncatedPower_" + std::to_string(n) + "_" + std::to_string(i) + "_" + std::to_string(j) + ".csv";
    PlotRW plot(filename);
    plot.write(x_vals, y_vals);
}

int main(){
    std::vector<int> n_vals = {1, 2};
    for(const auto& n : n_vals){
        std::vector<double> knots = generateKnots(n);
        for(int i = 0; i <= n + 1; i++){
            for(int j = i; j <= n + 1; j++){
                dividedDifferenceTable(knots, n, i, j);
            }
        }
    }
    
    return 0;
}