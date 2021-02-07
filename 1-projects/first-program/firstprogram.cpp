#include <iostream>

int main()
{
    std::cout << "Enter an integer: ";

    int num{ 0 };       // define variable num as an integer variable
    std::cin >> num;    // get integer value from user's keyboard

    std::cout << "Double "<< num << " is " << num * 2 << "\n";
    std::cout << "Tripe " << num << " is " << num * 3 << "\n";
    return 0;
}