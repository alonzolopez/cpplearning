#include <iostream>

int getUserInt()
{
    std::cout << "Enter an integer: ";
    int x{ 0 };
    std::cin >> x;
    return x;
}

bool isEven(int x)
{
    return (x % 2) == 0;
}

int main()
{
    int x{ 0 };
    x = getUserInt();
    if (isEven(x))
    {
        std::cout << x << " is even\n";
    }
    else
    {
        std::cout << x << " is odd\n";
    }

    return 0;
}