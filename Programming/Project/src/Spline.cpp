#include "Spline.hpp"
#include <unistd.h>

//======================Functions for SplineConfigParams======================

// Constructor for reading from JSON file
SplineConfigParams::SplineConfigParams(const std::string& filePath){
    loadConfig(filePath);
}

// Constructor for manual input
SplineConfigParams::SplineConfigParams(std::string splineType, int degree, std::string BoundaryType, std::vector<double> BoundaryVal, std::vector<double> nodes, std::vector<double> values, std::vector<std::pair<double, double>> intervals){
    this->splineType = splineType;
    this->degree = degree;
    this->BoundaryType = BoundaryType;
    this->BoundaryVal = BoundaryVal;
    this->nodes = nodes;
    this->values = values;

    // If intervals are not passed, generate them based on nodes
    if (intervals.empty() && nodes.size() > 1) {
        for (size_t i = 0; i < nodes.size() - 1; ++i) {
            if(nodes[i] > nodes[i+1]){
                throw std::runtime_error("Nodes are not in ascending order");
            }
            intervals.emplace_back(nodes[i], nodes[i + 1]);
        }
    }
    this->intervals = intervals;
}

void SplineConfigParams::loadConfig(const std::string& filePath){
    // Pwd
    // char cwd[1024];
    // if (getcwd(cwd, sizeof(cwd)) != nullptr) {
    //     std::cout << "Current working directory: " << cwd << std::endl;
    // } else {
    //     perror("getcwd() error");
    // }

    Json::Value root;
    std::ifstream file(filePath, std::ifstream::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open JSON file: " + filePath);
    }
    file >> root;

    splineType = root["spline_type"].asString();
    degree = root["degree"].asInt();
    BoundaryType = root["boundary_conditions"]["type"].asString();
    if(BoundaryType == "complete"){
        BoundaryVal.push_back(root["boundary_conditions"]["bound_values"][0].asDouble());
        BoundaryVal.push_back(root["boundary_conditions"]["bound_values"][1].asDouble());
    }else{
        BoundaryVal.push_back(0);
        BoundaryVal.push_back(0);
    }

    // Read nodes and values
    for (const auto& node : root["nodes"]) {
        nodes.push_back(node.asDouble());
    }
    for (const auto& value : root["values"]) {
        values.push_back(value.asDouble());
    }

    // Read intervals
    if (root.isMember("intervals")) {
        for (const auto& interval : root["intervals"]) {
            double start = interval[0].asDouble();
            double end = interval[1].asDouble();
            intervals.emplace_back(start, end);
        }
    }

    // Read additional settings
}

std::string SplineConfigParams::getType() const{
    return splineType;
}

int SplineConfigParams::getDeg() const{
    return degree;
}

std::string SplineConfigParams::getCondType() const{
    return BoundaryType;
}

std::vector<double> SplineConfigParams::getCondVal() const{
    return BoundaryVal;
}

std::vector<double> SplineConfigParams::getNodes() const{
    return nodes;
}

std::vector<double> SplineConfigParams::getVal() const{
    return values;
}

std::vector<std::pair<double, double>> SplineConfigParams::getIntervals() const{
    return intervals;
}

void SplineConfigParams::printConfig() const {
    std::cout << "Spline Type: " << splineType << "\n";
    std::cout << "Degree: " << degree << "\n";
    std::cout << "Boundary Type: " << BoundaryType << "\n";
    if(BoundaryType == "complete"){
        std::cout << "Boundary Values: " << BoundaryVal[0] << " " << BoundaryVal[1] << "\n";
    }
    std::cout << "Nodes: ";
    for (const auto& node : nodes) {
        std::cout << node << " ";
    }
    std::cout << "\nValues: ";
    for (const auto& value : values) {
        std::cout << value << " ";
    }
    std::cout << "\nIntervals: ";
    for (const auto& interval : intervals) {
        std::cout << "[" << interval.first << ", " << interval.second << "] ";
    }
}

void SplineConfigParams::NodesChange(std::vector<double> newNodes){
    nodes = newNodes;
}

//======================Functions for pp-form Spline======================

// Evaluate spline at point x
double ppSpline::operator()(double x) const {
    if (coefs.empty()) {
        throw std::runtime_error("Spline are not constructed");
    }

    int i=-1;

    if(params.getDeg()==1){
        for (const auto& interval : params.getIntervals()) {
            i++;
            double x_j = interval.first;
            double x_jplus = interval.second;
            if (x >= x_j && x <= x_jplus) {
                return coefs[i][0] * (x_jplus - x) / (x_jplus - x_j) + coefs[i][1] * (x - x_j) / (x_jplus - x_j);
            }
        }
    }else if(params.getDeg()==3){
        for (const auto& interval : params.getIntervals()) {
            i++;
            double x_j = interval.first;
            double x_jplus = interval.second;
            if (x >= x_j && x <= x_jplus) {
                return coefs[i][0] * (x - x_j) + coefs[i][1] * (x_jplus - x) + coefs[i][2] * std::pow(x - x_j, 3) + coefs[i][3] * std::pow(x_jplus - x, 3);
            }
        }

    }

    return 0.0;

}

// 3 degree spline constructor
void ppSpline::SplineConstructor() {
    if (params.getNodes().size() != params.getVal().size()) {
        throw std::runtime_error("Number of nodes and values are not equal");
    }

    if (params.getNodes().size() < 2) {
        throw std::runtime_error("Number of nodes is less than 2");
    }

    if (params.getNodes().size() != params.getVal().size()) {
        throw std::runtime_error("Number of nodes and values are not equal");
    }

    if (params.getIntervals().empty()) {
        throw std::runtime_error("Intervals are not specified");
    }

    if (params.getIntervals().size() != params.getNodes().size() - 1) {
        throw std::runtime_error("Number of intervals is not equal to number of nodes - 1");
    }

    if (params.getDeg() < 1) {
        throw std::runtime_error("Degree of spline is less than 1");
    }

    if (params.getDeg() > 3) {
        throw std::runtime_error("Degree of spline is greater than 3");
    }

    if(params.getCondType() == "periodic" && params.getNodes()[0] != params.getNodes()[params.getNodes().size() - 1]){
        throw std::runtime_error("Periodic spline must have the same first and last nodes");
    }

    Eigen::MatrixXd A = MatrixConstructor();
    Eigen::VectorXd b = bConstructor();
    Eigen::VectorXd x = A.colPivHouseholderQr().solve(b);
    // Check for Matrix A, Vector b and Vector x
    // std::cout << "Matrix A: \n" << A << std::endl;
    // std::cout << "Vector b: \n" << b << std::endl;
    

    if(params.getCondType() == "periodic"){
        x.conservativeResize(x.size() + 1);
        for (int i = x.size() - 1; i > 0; --i) {
            x(i) = x(i - 1);
        }
        x(0) = x(x.size() - 1);
    }

    //std::cout << "Vector x: \n" << x << std::endl;

    coefs.clear();
    for (int i = 0; i < params.getNodes().size() - 1; i++) {
        std::vector<double> y = {params.getVal()[i], params.getVal()[i + 1]};
        double h = params.getNodes()[i + 1] - params.getNodes()[i];
        double a = (y[1] - x[i+1] * (h*h) / 6.0) / h;
        double b = (y[0] - x[i] * (h*h) / 6.0) / h;
        double c = x[i+1] / (6.0 * h);
        double d = x[i] / (6.0 * h);
        coefs.push_back({a, b, c, d});
    }

}

// Linear spline constructor
void ppSpline::LinearSplineConstructor(){
    if (params.getNodes().size() != params.getVal().size()) {
        throw std::runtime_error("Number of nodes and values are not equal");
    }

    if (params.getNodes().size() < 2) {
        throw std::runtime_error("Number of nodes is less than 2");
    }

    if (params.getNodes().size() != params.getVal().size()) {
        throw std::runtime_error("Number of nodes and values are not equal");
    }

    coefs.clear();
    for (int i = 0; i < params.getNodes().size() - 1; i++) {
        std::vector<double> y = {params.getVal()[i], params.getVal()[i + 1]};
        coefs.push_back({y[0], y[1], 0, 0});
    }
}

void ppSpline::printCoefs() const {
    for (int i = 0; i < coefs.size(); i++) {
        std::cout << "Interval " << i << ": ";
        for (const auto& coef : coefs[i]) {
            std::cout << coef << " ";
        }
        std::cout << "\n";
    }
}

void ppSpline::printParams() const {
    params.printConfig();
}

// Calculate divided difference
double ppSpline::diff3(int i) {
    if(i < 1 || i > params.getNodes().size() - 2){
        throw std::runtime_error("(Divided Difference)Index out of range");
    }
    double y1 = params.getVal()[i - 1];
    double y2 = params.getVal()[i];
    double y3 = params.getVal()[i + 1];
    double h1 = params.getNodes()[i] - params.getNodes()[i - 1];
    double h2 = params.getNodes()[i + 1] - params.getNodes()[i];
    return ((y3 - y2) / h2 - (y2 - y1) / h1) / (h1 + h2); 
}

Eigen::MatrixXd ppSpline::MatrixConstructor() {
    // Construct matrix A for different boundary conditions
    if(params.getCondType() == "periodic"){
        int n = params.getNodes().size() - 1;
        Eigen::MatrixXd A = Eigen::MatrixXd::Zero(n, n);

        A(0, 0) = 2;
        A(n-1, n-1) = 2;
        double h0 = params.getNodes()[1] - params.getNodes()[0];
        double h1 = params.getNodes()[2] - params.getNodes()[1];
        double hn = params.getNodes()[n] - params.getNodes()[n - 1];
        A(0, 1) = h1 / (h0 + h1);
        A(0, n-1) = 1 - A(0, 1);
        A(n - 1, 0) = h0 / (hn + h0);
        A(n - 1, n - 2) = 1 - A(n - 1, 0);


        for(int i = 1; i < n - 1; i++){
            double h1 = params.getNodes()[i + 1] - params.getNodes()[i];
            double h2 = params.getNodes()[i + 2] - params.getNodes()[i + 1];
            A(i, i - 1) = h1 / (h1 + h2);
            A(i, i) = 2;
            A(i, i + 1) = 1 - A(i, i - 1);
        }

        return A;
    }else{
        int n = params.getNodes().size();
        Eigen::MatrixXd A = Eigen::MatrixXd::Zero(n, n);

        if(params.getCondType() == "natural"){
            A(0, 0) = 2;
            A(n - 1, n - 1) = 2;
        }else if (params.getCondType() == "complete") {
            A(0, 0) = 2;
            A(0, 1) = 1;
            A(n - 1, n - 2) = 1;
            A(n - 1, n - 1) = 2;
        }else{
            throw std::runtime_error("Unknown boundary condition");
        }

        for(int i = 1; i < n - 1; i++){
            double h1 = params.getNodes()[i] - params.getNodes()[i - 1];
            double h2 = params.getNodes()[i + 1] - params.getNodes()[i];
            A(i, i - 1) = h1 / (h1 + h2);
            A(i, i) = 2;
            A(i, i + 1) = 1 - A(i, i - 1);
        }

        return A;
    } 
}

Eigen::VectorXd ppSpline::bConstructor() {
    if(params.getCondType() == "periodic"){
        int n = params.getNodes().size() - 1;
        Eigen::VectorXd b = Eigen::VectorXd::Zero(n);

        for(int i = 0; i < n - 1; i++){
            b(i) = 6 * diff3(i + 1);
        }
        double y1 = params.getVal()[0];
        double y2 = params.getVal()[1];
        double y3 = params.getVal()[n - 1];
        double y4 = params.getVal()[n];
        double h1 = params.getNodes()[1] - params.getNodes()[0];
        double h2 = params.getNodes()[n] - params.getNodes()[n - 1];
        b(n - 1) = 6 * ((y2 - y1)/h1 - (y4 - y3)/h2)/(h1 + h2);

        return b;
    }else{
        int n = params.getNodes().size();
        Eigen::VectorXd b = Eigen::VectorXd::Zero(n);

        if(params.getCondType() == "natural"){
            b(0) = 0;
            b(n - 1) = 0;
        }else if (params.getCondType() == "complete") {
            double h0 = params.getNodes()[1] - params.getNodes()[0];
            double hn = params.getNodes()[n - 1] - params.getNodes()[n - 2];
            b(0) = 6.0 / h0 * ((params.getVal()[1] - params.getVal()[0]) / h0 - params.getCondVal()[0]);
            b(n-1) = 6.0 / hn * (params.getCondVal()[1] - ((params.getVal()[n - 1] - params.getVal()[n - 2]) / hn));

        }else{
            throw std::runtime_error("Unknown boundary condition");
        }

        for(int i = 1; i < n - 1; i++){
            b(i) = 6 * diff3(i);
        }

        return b;
    }

}

//======================Functions for B-Spline======================

// Evaluate spline at point x
double BSpline::operator()(double x) const {
    if (coefs.empty()) {
        throw std::runtime_error("Spline are not constructed");
    }

    int n = params.getNodes().size();
    int p = params.getDeg();
    double sum = 0;
    for(int i = 0; i < n - p - 1; i++){
        double B = Base(p, i, x, params.getNodes());
        sum += coefs[i] * B;
    }

    return sum;
}

// Spline constructor for degree p <= 3
void BSpline::SplineConstructor() {
    if (params.getNodes().size() < 2) {
        throw std::runtime_error("Number of nodes is less than 2");
    }

    if (params.getDeg() != 2 && params.getNodes().size() != params.getVal().size()) {
        throw std::runtime_error("Number of nodes and values are not equal");
    }

    if (params.getIntervals().empty()) {
        throw std::runtime_error("Intervals are not specified");
    }

    if (params.getIntervals().size() != params.getNodes().size() - 1) {
        throw std::runtime_error("Number of intervals is not equal to number of nodes - 1");
    }

    if (params.getDeg() < 0) {
        throw std::runtime_error("Degree of spline is less than 0");
    }

    NodesExpand();
    Eigen::MatrixXd A = MatrixConstructor();
    Eigen::VectorXd b = bConstructor();
    Eigen::VectorXd x = A.colPivHouseholderQr().solve(b);

    coefs.clear();
    if(params.getDeg() == 2){
        coefs.push_back( 2*params.getVal()[0] -x(0));
        for(const auto& xi : x){
            coefs.push_back({xi});
        }
        coefs.push_back(2*params.getVal()[params.getVal().size() - 1] - x(x.size() - 1));
    }
    else{
        for(const auto& xi : x){
            coefs.push_back({xi});
        }
    }

}

Eigen::MatrixXd BSpline::MatrixConstructor() {
    int n = params.getNodes().size();
    int p = params.getDeg();
    if(p == 3){
        Eigen::MatrixXd A = Eigen::MatrixXd::Zero(n - 4, n - 4);

        double h0 = params.getNodes()[4] - params.getNodes()[3];
        double h1 = params.getNodes()[5] - params.getNodes()[4];
        double h2 = params.getNodes()[n - 5] - params.getNodes()[n - 6];
        double h3 = params.getNodes()[n - 4] - params.getNodes()[n - 5];

        if(params.getCondType() == "natural"){
            double B1 = Base(p - 2, 2, params.getNodes()[3], params.getNodes());
            double B2 = Base(p - 2, n - 5 , params.getNodes()[n - 4], params.getNodes());
            A(0, 0) = 6 * B1 / ((h0 + 1)*(h0 + 2));
            A(0, 1) = -6 * B1 / ((h0 + 1)*(h0 + 2)) - 6 * B1 / ((h0 + 1)*(h0 + h1 + 1));
            A(0, 2) = 6 * B1 / ((h0 + 1)*(h0 + h1 + 1));
            A(n - 5, n - 7) = 6 * B2 / ((h3 + 1)*(h3 + h2 + 1));
            A(n - 5, n - 6) = -6 * B2 / ((h3 + 1)*(h3 + h2 + 1)) - 6 * B2 / ((h3 + 1)*(h3 + 2));
            A(n - 5, n - 5) = 6 * B2 / ((h3 + 1)*(h3 + 2));
        }else if(params.getCondType() == "complete"){
            double B1 = Base(p - 1, 1, params.getNodes()[3], params.getNodes());
            double B2 = Base(p - 1, 2 , params.getNodes()[3], params.getNodes());
            double B3 = Base(p - 1, n - 6 , params.getNodes()[n - 4], params.getNodes());
            double B4 = Base(p - 1, n - 5 , params.getNodes()[n - 4], params.getNodes());
            A(0, 0) = -3 * B1 / (h0 + 2);
            A(0, 1) = -3 * B2 / (h0 + h1 + 1) + 3 * B1 / (h0 + 2) ;
            A(0, 2) = 3 * B2 / (h0 + h1 + 1);
            A(n - 5, n - 7) = -3 * B3 / (h3 + h2 + 1);
            A(n - 5, n - 6) = 3 * B3 / (h3 + h2 + 1) - 3 * B4 / (h3 + 2);
            A(n - 5, n - 5) = 3 * B4 / (h3 + 2);
        }else if(params.getCondType() == "periodic"){
            double B1 = Base(p - 2, 2, params.getNodes()[3], params.getNodes());
            double B2 = Base(p - 2, n - 5 , params.getNodes()[n - 4], params.getNodes());
            A(0, 0) = 6 * B1 / ((h0 + 1)*(h0 + 2));
            A(0, 1) = -6 * B1 / ((h0 + 1)*(h0 + 2)) - 6 * B1 / ((h0 + 1)*(h0 + h1 + 1));
            A(0, 2) = 6 * B1 / ((h0 + 1)*(h0 + h1 + 1));
            A(0, n - 7) = -6 * B2 / ((h3 + 1)*(h3 + h2 + 1));
            A(0, n - 6) = 6 * B2 / ((h3 + 1)*(h3 + h2 + 1)) + 6 * B2 / ((h3 + 1)*(h3 + 2));
            A(0, n - 5) = -6 * B2 / ((h3 + 1)*(h3 + 2));
            B1 = Base(p - 1, 1, params.getNodes()[3], params.getNodes());
            B2 = Base(p - 1, 2 , params.getNodes()[3], params.getNodes());
            double B3 = Base(p - 1, n - 6 , params.getNodes()[n - 4], params.getNodes());
            double B4 = Base(p - 1, n - 5 , params.getNodes()[n - 4], params.getNodes());
            A(n - 5, 0) = 3 * B1 / (h0 + 2);
            A(n - 5, 1) = 3 * B2 / (h0 + h1 + 1) - 3 * B1 / (h0 + 2) ;
            A(n - 5, 2) = -3 * B2 / (h0 + h1 + 1);
            A(n - 5, n - 7) = -3 * B3 / (h3 + h2 + 1);
            A(n - 5, n - 6) = 3 * B3 / (h3 + h2 + 1) - 3 * B4 / (h3 + 2);
            A(n - 5, n - 5) = 3 * B4 / (h3 + 2);
        }

        int i = 1;
        for(i; i < n -5 ; i++){
            A(i, i - 1) = Base(p, i - 1, params.getNodes()[i + 2], params.getNodes());
            A(i, i) = Base(p, i, params.getNodes()[i + 2], params.getNodes());
            A(i, i + 1) = Base(p, i + 1, params.getNodes()[i + 2], params.getNodes());
        }

        return A;
    }
    else if (p == 2){
        Eigen::MatrixXd A = Eigen::MatrixXd::Zero(n - 4, n - 4);
        A(0, 0) = 5;A(0, 1) = 1;
        A(n - 5, n - 6) = 1;A(n - 5, n - 5) = 5;
        for(int i = 1; i < n - 5; i++){
            A(i, i - 1) = 1;
            A(i, i) = 6;
            A(i, i + 1) = 1;
        }

        return A;
    }
    else if (p == 1){
        Eigen::MatrixXd A = Eigen::MatrixXd::Zero(n - 2, n - 2);

        for(int i = 0; i < n - 2; i++){
            A(i, i) = Base(p, i, params.getNodes()[i + 1], params.getNodes());
        }

        return A;
    }
    
}

Eigen::VectorXd BSpline::bConstructor() {
    int n = params.getNodes().size();
    if(params.getDeg() == 3){
        Eigen::VectorXd b = Eigen::VectorXd::Zero(n - 4);

        if(params.getCondType() == "periodic"){
            b(0) = 0;
            b(n - 5) = 0;

            int i = 1;
            for(const auto& val : params.getVal()){
                b(i) = val;
                i++;
            }

            b(n - 6) = params.getVal()[0];

            return b;
        }else {
            if(params.getCondType() == "natural" ){
                b(0) = 0;
                b(n - 5) = 0;
            }else if(params.getCondType() == "complete"){
                b(0) = params.getCondVal()[0];
                b(n - 5) = params.getCondVal()[1];
            }
            int i = 1;
            for(const auto& val : params.getVal()){
                b(i) = val;
                i++;
            }

            return b;
        }
    }
    else if (params.getDeg() == 2){
        Eigen::VectorXd b = Eigen::VectorXd::Zero(n - 4);

        b(0) = 8 * params.getVal()[1] - 2 * params.getVal()[0];
        b(n - 5) = 8 * params.getVal()[n - 4] - 2 * params.getVal()[n - 3];
        for(int i = 0; i < n - 4; i++){
            b(i) = params.getVal()[i + 1];
        }

        return b;
    }
    else if (params.getDeg() == 1){
        Eigen::VectorXd b = Eigen::VectorXd::Zero(n - 2);

        for(int i = 0; i < n - 2; i++){
            b(i) = params.getVal()[i];
        }

        return b;
    }
}

void BSpline::printParams() const {
    params.printConfig();
}

// Calculate B-Spline base function
double BSpline::Base(int n, int i, double t, const std::vector<double>& nodes) const{
    if (n == 0) {
        if (t > nodes[i] && t <= nodes[i + 1]) {
            return 1.0;
        } else {
            return 0.0;
        }
    } else {
        if(n + i >= nodes.size() - 1){
            throw std::runtime_error("Index out of range");
        }
        double a = (t - nodes[i]) / (nodes[i + n] - nodes[i]);
        double b = (nodes[i + n + 1] - t) / (nodes[i + n + 1] - nodes[i + 1]);
        return a * Base(n - 1, i, t, nodes) + b * Base(n - 1, i + 1, t, nodes);
    }
}

void BSpline::NodesExpand() {
    std::vector<double> nodes;
    int j = 0;
    int p = params.getDeg();
    for (int i = 0; i < p; i++) {
        nodes.push_back(params.getNodes()[0] - p + j);
        j++;
    }
    for (const auto& node : params.getNodes()) {
        nodes.push_back(node);
    }
    for (int i = 0; i < params.getDeg(); i++) {
        j--;
        nodes.push_back(params.getNodes()[params.getNodes().size() - 1] + p - j);
    }

    params.NodesChange(nodes);
}