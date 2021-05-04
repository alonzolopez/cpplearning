#include <iostream>

int getUserInput()
{
    int x{};
    std::cout << "Enter an integer: ";
    std::cin >> x;
    return x;
}

int main()
{
    int smaller = getUserInput();
    int larger = getUserInput();
  
    if (larger < smaller)
    {
        std::cout << "Swapping the values\n";
        int tmp{};
        tmp = larger;
        larger = smaller;
        smaller = tmp;
    }

    std::cout << "The smaller value is " << smaller << '\n';
    std::cout << "The larger value is " << larger << '\n';

    return 0;
}