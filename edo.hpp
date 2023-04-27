#ifndef EDO_H
#define EDO_H

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <functional>

namespace ensiie {
    template<typename T>
    class edo {
        private:
            std::set<double> mesh_;
            std::vector<T> y0_;
            std::function<std::vector<T>(double, std::vector<T>)> f_;
        public:
            edo(std::function<std::vector<T>(double, std::vector<T>)> f, std::set<double> mesh, std::vector<T> y0);
            edo(std::function<std::vector<T>(double, std::vector<T>)> f, std::vector<T> y0, double t0 = 0.0, double a = 1.0, unsigned int N = 1000);
            std::vector<double> getMaillage() const;
            std::vector<std::vector<double>> getSolution() const;
            std::vector<double> operator()(double t) const;
    };
    template<typename T>
    std::vector<T> operator+(const std::vector<T> & v1, const std::vector<T> & v2);
    template<typename T>
    std::vector<T> operator-(const std::vector<T> & v1, const std::vector<T> & v2);
    template<typename T>
    std::vector<T> operator*(double k, const std::vector<T> & v);
    template<typename T>
    std::ostream & operator<<(std::ostream & os, const std::vector<T> & v);
    template<typename T>
    class 
}

#endif