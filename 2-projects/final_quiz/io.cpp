#include "io.h"
#include <iostream>

int readNumber()
{
    int x;
    std::cout << "Input a number: ";
    std::cin >> x;
    return x;
}

void writeAnswer(int answer)
{
    std::cout << "The answer is " << answer << "\n";
}