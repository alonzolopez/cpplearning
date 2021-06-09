#include <iostream>
#include <iterator>
#include <algorithm>

void printArray(int array[], int length)
{
    // note: you do not need to specify the size of the array in array[]
    // but you do need to pass length in 
    for (int iii{ 0 }; iii < length; ++iii)
    {
        std::cout << array[iii] << '\n';
    }
}
 
int main()
{
    int arr[]{ 2, 5, 4, 10, 8, 20, 16, 40 };

    int length{ sizeof(arr) / sizeof(arr[0]) };
    printArray(arr, length);
 
    return 0;
}