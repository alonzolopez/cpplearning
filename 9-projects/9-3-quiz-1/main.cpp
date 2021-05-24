#include <iostream>

int main()
{
    constexpr int array[]{ 4, 6, 7, 3, 8, 2, 1, 9, 5 };
    const int arrsize{ sizeof(array) / sizeof(array[0]) };

    for (int i{ 0 }; i < arrsize; ++i)
    {
        std::cout << array[i] << ' ';
    }

    std::cout << '\n';

    return 0;

}