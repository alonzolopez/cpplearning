#include <iostream>

void printBinary(int input)
{
    if (input == 0)
    {
        return;
    }
    printBinary(input / 2);
    std::cout << input % 2;
}

void printBinaryUnsigned(unsigned int input)
{
    if (input > 1)
    {
        printBinaryUnsigned( input / 2 );
    }
    std::cout << input % 2 ;
}

int main()
{
    std::cout << "Enter an integer: ";
    int x{};
    std::cin >> x;
    if (x < 0)
    {
        printBinaryUnsigned( static_cast<unsigned int>(x) );
    }
    else
    {
        printBinary(x);
    }
    return 0;
}