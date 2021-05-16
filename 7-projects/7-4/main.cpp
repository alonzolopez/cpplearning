#include <iostream>

void printDigitName(int x)
{
    switch(x)
    {
        case 1:
            std::cout << "One\n";
            break;
        case 2:
            std::cout << "Two\n";
            break;
        case 3:
            std::cout << "Three\n";
            break;
        default:
            std::cout << "Unknown\n";
            break;
    }

    std::cout << "Still executing!\n";
}

int main()
{
    printDigitName(3);

    return 0;
}