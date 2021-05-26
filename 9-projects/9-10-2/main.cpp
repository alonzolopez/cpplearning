#include <iostream>

void printArray(int arr[5], const int length)
{
    // print function for the array
    for (int i{ 0 }; i < length; ++i)
    {
        std::cout << arr[i] << ' ';
    }
    std::cout << '\n';
}

void modifyAndPrint(int arr[5], const int length)
{
    printArray(arr, length);
    arr[3] = 100;
    printArray(arr, length);
}

int main()
{
    constexpr int length{ 5 }; // array length
    int array[] { 5, 4, 3, 2, 1 }; // initialize array

    modifyAndPrint(array, length);
    
    return 0;
}