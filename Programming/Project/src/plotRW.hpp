#ifndef PLOTRW_HPP
#define PLOTRW_HPP

#include <iostream>
#include <fstream>
#include <vector>

class PlotRW {
private:
    std::string filename;
    std::ofstream file;

public:
    PlotRW(const std::string& filename);

    void write(const std::vector<double>& x, const std::vector<double>& y);
    void write(const std::vector<double>& x, const std::vector<double>& y, const std::vector<double>& z);

    ~PlotRW();
};


#endif // PLOTRW_HPP