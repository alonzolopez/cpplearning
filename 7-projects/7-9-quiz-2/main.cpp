#include <iostream>

int sumTo(int value)
{
    int sum{ 0 };
    for (int i{ 0 }; i <= value; ++i)
    {
        sum += i;
    }
    return sum;
}

int main()
{
    int x = sumTo(10);

    std::cout << x << '\n';

    return 0;
}