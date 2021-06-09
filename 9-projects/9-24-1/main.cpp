#include <array>
#include <iterator>
#include <iostream>

int main()
{
    std::array<int, 3> array{ 1, 2, 3 };

    // begin point
    auto begin{ array.begin() };      // container function
    auto begin2{ std::begin(array) }; // standard library generic function

    std::cout << begin << '\n';
    std::cout << begin2 << '\n';

    // end point
    auto end{ array.end() };    // container function
    auto end2{ std::end(array)}; // standard libary generic function

    std::cout << end << '\n';
    std::cout << end << '\n';

    return 0;
}