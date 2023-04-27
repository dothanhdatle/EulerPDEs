#include "edo.hpp"
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <functional>

using namespace ensiie;
// define function f
std::vector<double> f (double t, std::vector<double> y) {
    std::vector<double> res = 2 * y;
    return res;
}
int main() {
    //EXERCISE 1
    std::vector<double> y0 {1.2,1};
    edo<double> edo2(f, y0, 0.0, 1.0, 100000);
    std::vector<double> y_t = edo2(0.86);
    std::cout << y_t <<std::endl;
    //EXERCISE 2
}