#include <iostream>

int main()
{
    // this is how to properly define a float from a literal
    float f{ 4.1f };
    std::cout << f << '\n';

    // the following will work because it casts the double as a float, 
    // but may result in a loss of precision
    float g{ 5.3 }; 
    std::cout << g << '\n';

    return 0;
}