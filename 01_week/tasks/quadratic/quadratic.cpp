#include <iostream>
#include <cmath>


void SolveQuadratic(int a, int b, int c) {
    auto print = [](double x) {
        if (std::abs(x) < 1e-9) x = 0; 
        if (std::abs(x - std::round(x)) < 1e-9) {
            std::cout << static_cast<long long>(std::round(x));
        } else {
            x = std::round(x * 1e6) / 1e6; //округление (тест)
            std::cout << x;}
    };
    if (a == 0) { 
        if (b == 0) {
            if (c == 0) std::cout << "infinite solutions";
            else std::cout << "no solutions";
        } else {
            double x = -static_cast<double>(c) / b;
            print(x);}
        return;}
    double D = static_cast<double>(b) * b - 4.0 * a * c;
    if (D < 0) {
        std::cout << "no solutions";
    } else if (D == 0) {
        double x = -static_cast<double>(b) / (2.0 * a);
        print(x);
    } else {
        double sqrtD = std::sqrt(D);
        double x1 = (-b - sqrtD) / (2.0 * a);
        double x2 = (-b + sqrtD) / (2.0 * a);
        if (x1 > x2) {
            double temp = x1;
            x1 = x2;
            x2 = temp;}
        print(x1);
        std::cout << " ";
        print(x2);}
}