#include <iostream>
#include <string>

int main()
{
    std::string names[]{ "Alex", "Betty", "Caroline", "Dave", "Emily", "Fred", "Greg", "Holly"};

    std::string input_name{};
    std::cout << "Enter a name: ";
    std::getline(std::cin >> std::ws, input_name);

    bool found_name{ false };

    for (auto name : names)
    {
        if (input_name == name)
        {
            std::cout << input_name << " was found.\n";
            found_name = true;
            break;
        }
    }

    if (!found_name)
    {
        std::cout << input_name << " was not found.\n";
    }



    return 0;
}