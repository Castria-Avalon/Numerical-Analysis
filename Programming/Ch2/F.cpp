#include<iostream>
#include<vector>
#include<cmath>
#include<fstream>
#include "Interpolation.hpp"

class Point{
public:
    double x,y;
    Point(double x, double y):x(x),y(y){}
    Point(){
        x=0;
        y=0;
    }
    
    Point operator*(double s) const{
        return Point(s*x,s*y);
    }
    friend Point operator*(double s, const Point& p){
        return p*s;
    }
    Point operator+(const Point& p)const{
        return Point(x+p.x,y+p.y);
    }
    Point operator-(const Point& p)const{
        return Point(x-p.x,y-p.y);
    }
    
};


double function(double x, double y){
    return x*x-(3/2*y-abs(x))*(3/2*y-abs(x))-3;
}

Point derivative(Point p, std::function<double(double,double)> f, double h=1e-5){
    Point prime;
    double x=p.x;
    double y=p.y;
    prime.x=(f(x+h,y)-f(x,y))/h;
    prime.y=(f(x,y+h)-f(x,y))/h;
    return prime;
}

Point bezier_curve(double t, Point a, Point b, std::function<double(double,double)> f){
    double u=1-t;
    Point q0=a;
    Point q1=1/3*derivative(a,f)+a;
    Point q2=b-1/3*derivative(b,f);
    Point q3=b;
    return (t*t*t)*q3+(3*t*t*u)*q2+(3*t*u*u)*q1+(u*u*u)*q0;
}

std::vector<Point> generate_point(std::function<double(double,double)> f, int m){
    std::vector<Point> points;
    double n=m/2;
    // y>0
    for(int i=0;i<n;i++){
        double x=-sqrt(3)+2*sqrt(3)*i/n;
        double y=(sqrt(3-x*x)+sqrt(fabs(x)))*2.0/3;
        points.push_back(Point(x,y));
    }
    // y<0
    for(int i=0;i<n;i++){
        double x=sqrt(3)-2*sqrt(3)*i/n;
        double y=(-sqrt(3-x*x)+sqrt(fabs(x)))*2.0/3;
        points.push_back(Point(x,y));
    }
    return points;
}

int main(){
    std::vector<int> m={10,40,160};
    std::vector<int>::iterator it;
    for(it=m.begin();it!=m.end();it++){
        std::vector<double> x_vals;
        std::vector<double> y_vals;
        for(int i=0;i<(*it);i++){
            Point B;
            std::vector<Point> points=generate_point(function,*it);
            Point p1=points[i];
            Point p2=points[i+1];
            B=bezier_curve(1/(*it)*i,p1,p2,function);
            x_vals.push_back(B.x);
            y_vals.push_back(B.y);
        }

        // To make the curve closed
        x_vals.push_back(x_vals[0]);
        y_vals.push_back(y_vals[0]);
        save_interpolated_data(x_vals,y_vals,"BezierCurve_"+std::to_string(*it)+".csv");
    }
}