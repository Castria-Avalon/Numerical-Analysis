#include<iostream>
#include "../plotRW.hpp"
#include "../Spline.hpp"

double f(double x){
    return 1 / (1 + x * x);
}

double diff(double x){
    return -2 * x / ((1 + x * x) * (1 + x * x));
}

std::vector<double> NodeGenerator(double a, double b){
    std::vector<double> nodes;
    for(int i = 0; i < b - a + 1; i++){
        nodes.push_back(a + i);
    }
    return nodes;
}

int main(){
    std::vector<double> Node1 = NodeGenerator(-5.0, 5.0);
    std::vector<double> Node2 = NodeGenerator(-4.5, 4.5);
    std::vector<double> values1;
    std::vector<double> values2;
    for (const auto& node : Node1) {
        values1.push_back(f(node));
    }
    values2.push_back(f(Node2[0]-0.5));
    for (const auto& node : Node2) {
        values2.push_back(f(node));
    }
    values2.push_back(f(Node2[Node2.size() - 1]+0.5));
    std::vector<double> boundval1 = {diff(Node1[0]), diff(Node1[Node1.size() - 1])};
    std::vector<double> boundval2 = {diff(Node2[0]), diff(Node2[Node2.size() - 1])};
    SplineConfigParams params1("B-form", 3, "complete", boundval1, Node1, values1, {});
    SplineConfigParams params2("B-form", 2, "complete", boundval2, Node2, values2, {});
    SplineConfigParams params3("pp-form", 3, "complete", boundval1, Node1, values1, {});
    BSpline S1(params1);
    BSpline S2(params2);
    ppSpline S3(params3);
    S1.SplineConstructor();
    S2.SplineConstructor();
    S3.SplineConstructor();
    std::vector<double> x, y1, y2, y3;
    for(double i = -5.0; i <= 5.0; i += 0.01){
        x.push_back(i);
        y1.push_back(S1(i));
        y2.push_back(S2(i));
        y3.push_back(S3(i));
    }
    PlotRW plot1("Results_357.csv");
    PlotRW plot2("Results_358.csv");
    PlotRW plot3("Results_pp.csv");
    plot1.write(x, y1);
    plot2.write(x, y2);
    plot3.write(x, y3);

    std::vector<double> t = {-3.5, -3.0, -0.5, 0.0, 0.5, 3.0, 3.5};
    for(const auto& ti : t){
        std::cout << "Error at t = " << ti << " for 3.57: " << fabs(f(ti) - S1(ti)) << std::endl;
        std::cout << "Error at t = " << ti << " for 3.58: " << fabs(f(ti) - S2(ti)) << std::endl;
    }
}

