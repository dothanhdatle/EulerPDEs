#include "edo.hpp"
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <functional>

namespace ensiie {
    //EXERCISE 1
    template<typename T>
    edo<T>::edo(std::function<std::vector<T>(double, std::vector<T>)> f, std::set<double> mesh, std::vector<T> y0) : f_(f), mesh_(mesh), y0_(y0) {}
    template<typename T>
    edo<T>::edo(std::function<std::vector<T>(double, std::vector<T>)> f, std::vector<T> y0, double t0, double a, unsigned int N) {
        f_ = f;
        y0_ = y0;
        if (a <= 0) {
            throw "the length of the interval I must be positive.";
        }
        for (int i = 0; i <= N; i++){
            mesh_.insert(t0 + i*(a/N));
        }
    }
    template<typename T>
    std::vector<double> edo<T>::getMaillage() const {
        std::vector<double> mesh_vec(mesh_.begin(), mesh_.end());
        return mesh_vec;        
    }
    template<typename T>
    std::vector<std::vector<double>> edo<T>::getSolution() const {
        std::vector<std::vector<double>> res;
        std::vector<T> z = y0_;
        std::vector<T> z_next(z);
        res.push_back(y0_);
        std::vector<double> mesh = getMaillage();
        for(int i = 0; i < mesh.size()-1; i++) {
            for(int k = 0; k < y0_.size(); k++){
                z_next[k] = z[k] + (mesh[i+1]-mesh[i])*f_(mesh[i], z)[k];
            }
            res.push_back(z_next);
            std::swap(z, z_next);
        } 
        return res;       
    }
    template<typename T>
    std::vector<double> edo<T>::operator()(double t) const {
        std::vector<double> mesh = getMaillage();
        if (t < mesh[0] || t > mesh[mesh.size()-1]) {
            throw "This time point is not in the interval I.";
        } else {
            std::vector<std::vector<double>> solution = getSolution();
            std::vector<double>::iterator it = std::find(mesh.begin(), mesh.end(), t);
            if (it != mesh.end()) {
                int index = std::distance(mesh.begin(), it);
                std::vector<double> res = solution[index];
                return res;
            } else {
                std::vector<double> y1;
                std::vector<double> y2;
                double t1;
                double t2;
                for (int i = 0; i < mesh.size()-1; i++) {
                    if (t > mesh[i] && t < mesh[i+1]) {
                        break;
                    }
                    t1 = mesh[i];
                    t2 = mesh[i+1];
                    y1 = solution[i];
                    y2 = solution[i+1];
                }
                std::vector<double> res(y1.size(),0);
                for (int i = 0; i < y1.size(); i++) {
                    res[i] = y1[i] + (y2[i]-y1[i])*(t-t1)/(t2-t1);
                }
                return res;
            }
        }
    }
    template<typename T>
    std::vector<T> operator+(const std::vector<T> & v1, const std::vector<T> & v2) {
        if (v1.size() != v2.size()) {
            throw "Wrong size";
        } else {
            std::vector<T> res(v1.size(),0);
            for (int i = 0; i < v1.size(); i++) {
                res[i] = v1[i] + v2[i];
            }
            return res;
        }
    }
    template<typename T>
    std::vector<T> operator-(const std::vector<T> & v1, const std::vector<T> & v2){
        if (v1.size() != v2.size()) {
            throw "Wrong size";
        } else {
            std::vector<T> res(v1.size(),0);
            for (int i = 0; i < v1.size(); i++) {
                res[i] = v1[i] - v2[i];
            }
            return res;
        }
    }
    template<typename T>
    std::vector<T> operator*(double k, const std::vector<T> & v){
        std::vector<T> res(v.size(),0);
        for (int i = 0; i < v.size(); i++) {
            res[i] = k*v[i];
        }
        return res;
    }
    template<typename T>
    std::ostream & operator<<(std::ostream & os, const std::vector<T> & v){
        os << "(";
        for (int i = 0; i < v.size(); i++) {
            if (i != (v.size() - 1)) {
                os << v[i] << ", ";
            } else {
                os << v[i] << ")";
            }
        }
        return os;
    }
    //EXERCISE 2
    template class edo<double>;
    template std::vector<double> operator+(const std::vector<double> & v1, const std::vector<double> & v2);
    template std::vector<double> operator-(const std::vector<double> & v1, const std::vector<double> & v2);
    template std::vector<double> operator*(double k, const std::vector<double> & v);
    template std::ostream & operator<<(std::ostream & os, const std::vector<double> & v);
}

