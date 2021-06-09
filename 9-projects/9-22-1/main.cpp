#include <iostream>
#include <array>
#include <algorithm>

void printArray(const std::array<double, 5> &arr)
{
    // pass arr by reference to avoid making a copy
    std::cout << "length: " << arr.size() << '\n';

    for (double element : arr)
    {
        // the for-each loop works with std::array because it doesn't decay to a pointer
        std::cout << element << ' ';
    }

    std::cout << '\n';
}

int main()
{
    std::array<double, 5> myArray{ 1.0, 5.7, 9.0, 2.0, 0.1 };

    std::sort(myArray.begin(), myArray.end());

    printArray(myArray);

    return 0;
}