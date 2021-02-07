#include <iostream>

int main()
{
    // ask the user for the first integer and store it
    std::cout << "Enter an integer: ";
    int firstNum{};
    std::cin >> firstNum;

    // ask the user for the second integer and store it
    std::cout << "Enter another integer: ";
    int secondNum{};
    std::cin >> secondNum;

    // output the math
    std::cout << firstNum << " + " << secondNum << " is " << firstNum + secondNum << ".\n";
    std::cout << firstNum << " - " << secondNum << " is " << firstNum - secondNum << ".\n";

    return 0;
}