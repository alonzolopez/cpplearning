#include <iostream>

int doubleNumber(int x)
{
    return 2 * x;
}

int main()
{
    std::cout << "Enter an integer: ";
    int y{};
    std::cin >> y;

    std::cout << doubleNumber(y) << '\n';

    return 0;
}