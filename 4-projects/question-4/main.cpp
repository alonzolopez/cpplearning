#include "constants.h"
#include <iostream>

double getHeight()
{
    std::cout << "Enter the height of the tower in meters: ";
    double height{};
    std::cin >> height;
    return height;
}

double calculateHeight(double initialHeight, int secElapsed)
{
    return initialHeight - constants::gravity * secElapsed * secElapsed / 2.0;
}

void calculateAndPrintHeight(double initialHeight, int secElapsed)
{
    double height = calculateHeight(initialHeight, secElapsed);
    if (height > 0)
        std::cout << "At " << secElapsed << " seconds, the ball is at height: " << height << " meters.\n";
    else    
        std::cout << "At " << secElapsed << " seconds, the ball is on the ground.\n";

}

int main()
{
    const double height = getHeight();

    // the following can be improved by a for loop, but it works for now
    calculateAndPrintHeight(height, 0);
    calculateAndPrintHeight(height, 1);
    calculateAndPrintHeight(height, 2);
    calculateAndPrintHeight(height, 3);
    calculateAndPrintHeight(height, 4);
    calculateAndPrintHeight(height, 5);

    return 0;
}