#include <iostream>

bool isEqual(int x, int y)
{
    return (x==y);
}

int main()
{
    int x{};
    std::cout << "Enter an integer: ";
    std::cin >> x;

    int y{};
    std::cout << "Enter another integer: ";
    std::cin >> y;

    if (isEqual(x,y))
        std::cout << x << " and " << y << " are equal.\n";
    else
        std::cout << x << " and " << y << " are NOT equal.\n";
    
    return 0;
}