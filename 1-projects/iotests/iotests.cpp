#include <iostream>

int main()
{
    // std::cout << "Hi!\nMy name is Alonzo.\n";

    std::cout << "Enter a number: ";    // ask the user for a number
    int x{};    // define a variable to hold the user input and zero-initialize it
    std::cin >> x;  // get a number from the keyboard and store it in variable x
    std::cout << "You entered: " << x << '\n';
    return 0;
}