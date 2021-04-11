#include <iostream>

int main()
{
    std::cout << true << '\n';
    std::cout << !true << '\n';

    bool b{false};
    std::cout << b << '\n';
    std::cout << !b << '\n';

    std::cout << std::boolalpha;

    std::cout << true << '\n';
    std::cout << false << '\n';

    std::cout << std::noboolalpha;

    std::cout << true << '\n';
    std::cout << false << '\n';

    bool b2{};
    std::cout << "Enter a boolean value 0/1: ";
    std::cin >> b2;
    std::cout << "You entered: " << b2 << '\n';

    std::cin >> std::boolalpha;
    std::cout << std::boolalpha;

    bool b3{};
    std::cout << "Enter another boolean value true/false: ";
    std::cin >> b3;
    std::cout << "You entered: " << b3 << '\n';

    return 0;
}