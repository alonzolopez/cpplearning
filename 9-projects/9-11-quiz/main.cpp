#include <iostream>
#include <iterator>
#include <algorithm>
 
bool isEqual(int element)
{
    return element == 20;
}

int* find(int* beginning, int* end, int value)
{
    for (int* curr_addr{ beginning }; curr_addr != end; ++curr_addr)
    {
        if (*curr_addr == value)
        {
            return curr_addr;
        }
    }
    return end;
}
 
int main()
{
    int arr[]{ 2, 5, 4, 10, 8, 20, 16, 40 };
 
    // Search for the first element with value 20.
    int* found{ find(std::begin(arr), std::end(arr), 20) };
    // Alternatively, use the built-in std::find
    auto found2{ std::find(std::begin(arr), std::end(arr), 20) };
 
    // If an element with value 20 was found, print it.
    if (found != std::end(arr))
    {
        std::cout << *found << '\n';
        std::cout << *found2 << '\n';
    }
 
    return 0;
}