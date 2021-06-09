#include <iostream>

int main()
{
    int array[]{ 1, 3, 5, 7, 9 };

    for (auto& element : array)
    {
        element = element + 1;
    }

    for (const auto& element: array)
    {
        std::cout << element << ' ';
    }

    std::cout << '\n';

    return 0;
}