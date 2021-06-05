#include <iostream>

void printArray(int* arrayptr, std::size_t len)
{

    for (std::size_t s{ }; s < len; ++s)
    {
        // recall, arrayptr[s] is equivalent to *(arrayptr + s)
        std::cout << arrayptr[s] << '\n'; 
    }
    std::cout << "---\n";
}

int main()
{
    std::size_t length;
    std::cout << "Enter a length for the array greater than or equal to 5: ";
    std::cin >> length;
    
    int* array1{ new int[length]{9, 7, 5, 3, 1 } }; // initialize a dynamic array using list initialization
    printArray(array1, length);

    // we can also use the auto keyword to avoid writing the type twice
    auto* array2{ new int[length]{1, 3, 5, 7, 9}};
    printArray(array2, length);

    return 0;
}