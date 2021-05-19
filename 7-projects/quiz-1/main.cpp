#include <iostream>
#include <limits>
#include "constants.h"
 
void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

double getUserInput()
{
    while (true)
    {
        std::cout << "Enter the initial height of the tower in meters: ";
        double height;
        std::cin >> height;

        // check for failed extraction
        if (std::cin.fail())
        {
            std::cin.clear();   // put us back in normal operation mode
            ignoreLine();       // remove bad input
            std::cout << "That input is invalid. Please try again.\n";
        }
        else if (height < 0.0)
        {
            std::cout << "The height of the tower must be greater than zero. Please try again.\n";
        }
        
        else
        {
            ignoreLine();       // remove extraneous input
            return height;
        }
    }
}
 
int main()
{
    double height { getUserInput() };

    int time { 0 };

    while (height > 0.0)
    {
        std::cout << "At " << time << " seconds, the ball is at height: " << height << "\n";
        ++time;
        height -= myConstants::gravity / 2;
    }
	
    return 0;
}