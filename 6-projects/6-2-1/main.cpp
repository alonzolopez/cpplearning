#include <iostream>
#include "goo.h"
#include "foo.h"

int main()
{
    std::cout << foo::doSomething(4, 3) << '\n';
    std::cout << goo::doSomething(4, 3) << '\n';
    return 0;
}