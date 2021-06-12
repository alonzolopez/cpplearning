#include <iostream>

void swapValues(int &a, int &b)
{
    // initialize a temporary variable to a's value
    int tmp{ a };

    a = b;
    b = tmp;
}

int main()
{
    int a{ 6 };
    int b{ 9 };

    std::cout << "a is " << a << '\n';
    std::cout << "b is " << b << '\n';
    
    swapValues(a, b);

    std::cout << "a is " << a << '\n';
    std::cout << "b is " << b << '\n';

    return 0;
}