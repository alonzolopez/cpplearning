#include <iostream>
#include <string>
#include <iomanip>

int main()
{
    std::cout << "Enter your full name: ";
    std::string name{};
    std::getline(std::cin >> std::ws, name);

    std::cout << "Enter your age: ";
    double age{};
    std::cin >> age;

    int letters{ static_cast<int>(name.length())};

    std::cout << "You've lived " << age/letters << " years for each letter in your name.\n"; 

    return 0;
}