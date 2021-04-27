#include <cmath> // for std::abs()
#include <algorithm> // for std::max()
#include <iostream>

bool approximatelyEqual(double a, double b, double epsilon)
{
    return std::abs(a - b) <= epsilon;
}

bool approximatelyEqualRel(double a, double b, double epsilon)
{
    return (std::abs(a - b) <= std::max(std::abs(a), std::abs(b)) * epsilon);
}

bool approximatelyEqualAbsRel(double a, double b, double absEpsilon, double relEpsilon)
{
    double diff{ std::abs(a - b) };
    // if the numbers are really close in the absolute sense, return true
    if (diff <= absEpsilon)
        return true;
    // otherwise, check the relative proximity using Knuth's algorithm
    return (std::abs(a - b) <= std::max(std::abs(a), std::abs(b)) * relEpsilon);
}

int main()
{
    double a = 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1;
    std::cout << approximatelyEqualRel(a - 1.0, 0.0, 1e-8) << '\n';
    return 0;
}