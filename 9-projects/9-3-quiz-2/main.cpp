#include <iostream>
#include <limits>

int getUserInput()
{
    int x{};
    std::cout << "Enter input between 0 and 9 inclusive: ";
    while (true)
    {
        std::cin >> x;
        if (std::cin.fail())
        {
            std::cin.clear(); // reset any error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "That input is invalid. Please try again.\n";
        }
        else if ((x > 9) || (x < 0))
        {
            std::cout << "The input must be between 0 and 9 inclusive. Try again.\n";
        }
        else
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return x;
        }
    }
}

int main()
{
    // get validated user input
    int x = getUserInput();
    // std::cout << "Input: " << x;

    int index{ -1 };

    // print the array
    constexpr int array[]{ 4, 6, 7, 3, 8, 2, 1, 9, 5 };
    const int arrsize{ sizeof(array) / sizeof(array[0]) };

    for (int i{ 0 }; i < arrsize; ++i)
    {
        std::cout << array[i] << ' ';
        if (array[i] == x)
        {
            index = i;
        }
    }

    std::cout << '\n';
    std::cout << "The index of " << x << " is " << index << '\n';

    return 0;

}