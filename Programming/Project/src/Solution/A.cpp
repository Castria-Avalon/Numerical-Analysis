#include<iostream>
#include "../plotRW.hpp"
#include "../Spline.hpp"

double f(double x){
    return 1 / (1 + 25 * x * x);
}

std::vector<double> NodeGenerator(int n, double a, double b){
    std::vector<double> nodes;
    for(int i = 0; i < n; i++){
        nodes.push_back(a + i * (b - a) / (n - 1));
    }
    return nodes;
}

double MaxError(const ppSpline& spline, const std::function<double(double)>& f, const std::vector<double> nodes , double a, double b){
    double maxError = 0.0;
    int n = nodes.size();
    for (int i = 0; i < n - 1; ++i) {
        double x_mid = (nodes[i] + nodes[i + 1]) / 2.0;
        double error = fabs(f(x_mid) - spline(x_mid));
        maxError = std::max(maxError, error);
    }
    return maxError;
}

int main(){
    std::vector<int> N_values = {6, 11, 21, 41, 81};  
    double a = -1.0, b = 1.0;                   
    std::vector<double> errors;
    std::vector<double> rates;
    for (int N : N_values) {
        std::vector<double> nodes = NodeGenerator(N, a, b);
        std::vector<double> values;
        for (const auto& node : nodes) {
            values.push_back(f(node));
        }
        SplineConfigParams params("pp-form", 3, "natural", {0, 0}, nodes, values, {});
        ppSpline S(params);
        S.SplineConstructor();
        double error = MaxError(S, f, nodes, a, b);
        errors.push_back(error);

        std::vector<double> x, y;
        for(double i = a; i <= b; i += 0.01){
            x.push_back(i);
            y.push_back(S(i));
        }
        std::string filename = "CubicPlot_N" + std::to_string(N) + ".csv";
        PlotRW plot(filename);
        plot.write(x, y);
    }

    // Calculate convergence rates
    for (size_t i = 1; i < errors.size(); ++i) {
        double rate = std::log(errors[i] / errors[i - 1]) / std::log(double(N_values[i - 1]) / N_values[i]);
        rates.push_back(rate);
    }

    std::cout << "N\tError\t\tRate" << std::endl;
    for (size_t i = 0; i < errors.size(); ++i) {
        std::cout << N_values[i] << "\t" << errors[i];
        if (i > 0) {
            std::cout << "\t" << rates[i - 1];
        }
        std::cout << std::endl;
    }
}