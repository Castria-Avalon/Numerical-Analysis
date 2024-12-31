#ifndef SPLINE_HPP
#define SPLINE_HPP

#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>
#include "include/json/json.h"
#include "include/eigen-3.4.0/Eigen/Dense"

class SplineConfigParams{
private:
    std::string splineType;
    int degree;
    std::string BoundaryType;
    std::vector<double> BoundaryVal;
    std::vector<double> nodes;
    std::vector<double> values;
    std::vector<std::pair<double, double>> intervals;

public:
    SplineConfigParams(const std::string& filePath);
    SplineConfigParams(std::string splineType, int degree, std::string BoundaryType, std::vector<double> BoundaryVal, std::vector<double> nodes, std::vector<double> values, std::vector<std::pair<double, double>> intervals);
    void loadConfig(const std::string& filePath);
    std::string getType() const;
    int getDeg() const;
    std::string getCondType() const;
    std::vector<double> getCondVal() const;
    std::vector<double> getNodes() const;
    std::vector<double> getVal() const;
    std::vector<std::pair<double, double>> getIntervals() const;
    void printConfig() const;
    void NodesChange(std::vector<double> newNodes);
};

class ppSpline{
protected:
    SplineConfigParams params;
    std::vector<std::array<double, 4>> coefs;
public:
    ppSpline()=default;
    ppSpline(const SplineConfigParams& params): params(params){}

    double operator()(double x) const;
    void SplineConstructor();
    void LinearSplineConstructor();
    void printCoefs() const;
    void printParams() const;
    double diff3(int i);
    Eigen::MatrixXd MatrixConstructor();
    Eigen::VectorXd bConstructor(); 
};

class BSpline{
protected:
    SplineConfigParams params;
    std::vector<double> coefs;

public:
    BSpline()=default;
    BSpline(const SplineConfigParams& params): params(params){}

    double operator()(double x) const;
    void SplineConstructor();
    Eigen::MatrixXd MatrixConstructor();
    Eigen::VectorXd bConstructor();
    void printParams() const;
    double Base(int n, int i, double t, const std::vector<double>& nodes)const;
    void NodesExpand();
};

#endif // SPLINE_HPP