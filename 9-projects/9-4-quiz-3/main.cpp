#include <iostream>
#include <utility>

int main()
{
    int array[]{ 6, 3, 2, 9, 7, 1, 5, 4, 8 };
    const int length{ sizeof(array) / sizeof(array[0]) };
    bool sorted{ true };

    // sort smallest to largest
    for (int i{ 0 }; i < length; ++i)
    {
        for (int j{ 0 }; j < (length - i - 1); ++j)
        {
            if (array[j] > array[j + 1])
            {
                std::swap(array[j], array[j + 1]);
                sorted = false; // we made a swap, so it's not sorted
            }
        }
        if (sorted)
        {
            // no swap in this iteration, so its sorted
            std::cout << "Early termination on iteration " << i + 1 << '\n';
            break;
        }

        sorted = true; // reset the flag for the next iteration
    }

    // print
    for (int k{ 0 }; k < length; ++k)
    {
        std::cout << array[k] << ' ';
    }
    std::cout << '\n';

    return 0;
}