#include <iostream>

int main()
{
    int arr[5] { 5, 4, 3, 2, 1};

    int* ptr { arr };

    std::cout << "The address of the array is " << &arr << '\n';
    std::cout << "The type of the array is " << typeid(arr).name() << '\n';
    std::cout << "The pointer is " << ptr << '\n';
    std::cout << "The type of the pointer is " << typeid(ptr).name() << '\n';

    return 0;
}