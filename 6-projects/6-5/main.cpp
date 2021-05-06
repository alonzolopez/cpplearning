#include <iostream>

int value { 5 }; // global var

void foo()
{
    // global value not shadowed here; this refers to the global value
    std::cout << "global variable value: " << value << '\n'; 
}

int main()
{
    // hides the global variable value WITHIN the block
    // UNTIL the end of the block
    int value { 7 };    

    ++value;    // increments local, not global value

    std::cout << "local variable value: " << value << '\n';

    // we can access the global value with ::
    std::cout << "global variable value: " << ::value << '\n';

    foo();

    return 0;
}   // local value destroyed