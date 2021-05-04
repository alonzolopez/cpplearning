#include <iostream>

void print()
{
    std::cout << " there\n";
}

namespace foo
{
    void print()
    {
        std::cout << "Hello";
    }

    void printHelloThere()
    {
        print();    // no (::), calls print() in foo namespace
        ::print();  // calls print in global namespace
    }
}

int main()
{
    foo::printHelloThere();

    return 0;
}