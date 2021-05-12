#include <iostream>

namespace constants
{
    extern const double gravity { 9.8 };
}

double getGravity()
{
    return constants::gravity;
}

double instantVelocity(int time, double gravity)
{
    return gravity * time;
}

int main()
{
    std::cout << instantVelocity(5, constants::gravity) << '\n';
}