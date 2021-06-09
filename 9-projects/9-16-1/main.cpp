#include <iostream>

int main()
{
    int value{ 5 };
    int& ref{ value };
    int& ref2{ value };

    std::cout << "Value is: " << value << '\n';

    value = 6;

    std::cout << "Value is: " << value << '\n';

    ref = 7;

    std::cout << "Value is: " << value << '\n';

    ref2 = 8;

    std::cout << "Value is: " << value << '\n';

    ++ref;

    std::cout << "Value is: " << value << '\n';

    std::cout << "The address of value is " << &value << '\n';
    std::cout << "The address of ref is " << &ref << '\n';
    std::cout << "The address of ref2 is " << &ref2 << '\n';

    return 0;
}