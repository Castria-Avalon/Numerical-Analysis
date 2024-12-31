#include<iostream>
#include <sys/stat.h>
#include <unistd.h>
#include "plotRW.hpp"

/*
* Class PlotRw: Read and write data to a file
*/

PlotRW::PlotRW(const std::string& filename): filename(filename) {
    file.open(filename, std::ios::out | std::ios::trunc);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file");
    }
}

void PlotRW::write(const std::vector<double>& x, const std::vector<double>& y) {
    if (x.size() != y.size()) {
        throw std::runtime_error("Size of x and y are not equal");
    }

    for (int i = 0; i < x.size(); i++) {
        file << x[i] << "," << y[i] << "\n";
    }
}

void PlotRW::write(const std::vector<double>& x, const std::vector<double>& y, const std::vector<double>& z) {
    if (x.size() != y.size() || x.size() != z.size()) {
        throw std::runtime_error("Size of x, y and z are not equal");
    }

    for (int i = 0; i < x.size(); i++) {
        file << x[i] << "," << y[i] << "," << z[i] << "\n";
    }
}

PlotRW::~PlotRW() {
    file.close();
}