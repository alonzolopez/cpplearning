#include <iostream>
#include <string>
#include <algorithm>
#include <limits>

void printArray(std::string* arrayptr, std::size_t len)
{

    for (std::size_t s{ }; s < len; ++s)
    {
        // recall, arrayptr[s] is equivalent to *(arrayptr + s)
        std::cout << arrayptr[s] << '\n'; 
    }
    // std::cout << "---\n";
}

void getNames(std::string* strarray, std::size_t number_names)
{
    // ignore the line feed that was left by std::cin
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // ask the user to enter each name
    for (std::size_t iii{}; iii < number_names; ++iii)
    {
        std::cout << "Enter name #" << iii + 1 << ": ";
        std::getline(std::cin >> std::ws, strarray[iii]);
    }
}

int main()
{
    // get the number of names from the user
    std::size_t number_names{};
    std::cout << "How many names would you like to enter? ";
    std::cin >> number_names;

    // dynamically allocate a std::string array
    auto* strarray{ new (std::nothrow) std::string[number_names]{} };

    // get the names
    getNames(strarray, number_names);

    // sort the names
    std::sort(strarray, strarray + number_names);

    // print the sorted list of names
    printArray(strarray, number_names);

    // delete the pointer to return the memory to the OS
    delete[] strarray;

    // set the pointer to nullptr
    // technically we don't need to b/c it's about to go out of scope
    // when the program ends
    strarray = nullptr; 

    return 0;
}