#include <iostream>

int main()
{
    constexpr int fibonacci[]{ 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 };

    for (int number : fibonacci) // iterate over array fibonacci
    {
        std::cout << number << ' ';
    }

    std::cout << '\n';

    // same thing but with the auto keyword

    for (auto number : fibonacci) // iterate over array fibonacci
    {
        std::cout << number << ' ';
    }

    std::cout << '\n';

    return 0;
}