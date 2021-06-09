#include <iostream>
#include <iterator>

// NOTE: you need to specify the array size in the function declaration
void printElements(int (&arr)[4])
{
    // we can now get the length of the array since it won't decay to a pointer when passed by ref
    int length{ static_cast<int>(sizeof(arr) / sizeof(arr[0])) };

    for (int i{ 0 }; i < length; ++i)
    {
        std::cout << arr[i] << '\n';
    }
}

int main()
{
    int arr[]{ 99, 20, 14, 80 };

    printElements(arr);

    return 0;
}