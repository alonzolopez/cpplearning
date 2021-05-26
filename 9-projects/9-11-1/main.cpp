#include <iostream>

int main()
{
    int array[]{ 9, 7, 6, 5, 3};

    // print the memory address of array element 1
    std::cout << &array[1] << '\n';
    // print the memory address of array pointer + 1
    std::cout << array + 1 << '\n';

    // print the value of array element 1
    std::cout << array[1] << '\n';
    // print the value at the memory address (pointer + 1)
    std::cout << *(array + 1) << '\n';
}
