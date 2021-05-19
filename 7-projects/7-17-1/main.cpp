#include <iostream>
#include <cmath>
#include <cassert>

double calculateTimeUntilObjectHitsGround(double initial_height, double gravity)
{
    assert(gravity > 0.0);  // RUNTIME ASSERTION

    if (initial_height <= 0.0)
    {
        return 0.0;
    }

    return std::sqrt((2.0 * initial_height) / gravity);
}

int main()
{
    std::cout << "Took " << calculateTimeUntilObjectHitsGround(100.0, -9.8) << " seconds\n";

    return 0;
}