# [6.1 - Compound Statements (blocks)](https://www.learncpp.com/cpp-tutorial/compound-statements-blocks/)
A **compound statement** (a.k.a. **block** or **block statement**) is a group of *zero or more statements* that are treated by the compiler as if they were a single statement. Blocks begin with a { symbole and end with a }. For example,
```cpp
int main()
{ // start block
    int value {}; // this is initialization, not a block
    value = 4;

    return 0;
} // end block (no semicolon)
```

## Blocks Inside Other Blocks
Though functions can't be nested inside of other functions, blocks *CAN* be nested inside of other blocks:
```cpp
int add(int x, int y)
{
    return x + y;
}
int main()
{
    int value {};

    { // inner/nested block
        add(3, 4);
    } // end inner/nested block

    return 0;
}
```

## Using Blocks to Execute Multiple Statements Conditionally
One of the most common use cases for block statements is executing statements conditionally in `if else` blocks. For example,
```cpp
int main()
{
    std::cout << "Enter an integer: ";
    int value {};
    std::cin >> value;

    if (value >= 0)
    {
        std::cout << value << " is a positive integer (or zero)\n";
        std::cout << "Double this number is " << value * 2 << '\n';
    }
    else
    {
        std::cout << vtalue << " is a negative integer\n";
        std::cout << "The positive of this number is " << -value << '\n';
    }
}
```

## Block Nesting Levels
You can put blocks inside of blocks inside of blocks. For example,
```cpp
#include <iostream>

int main()
{
    std::cout << "Enter an integer: ";
    int value {};
    std::cin >> value;

    if (value > 0)
    {
        if ((value % 2) == 0)
        {
            std::cout << value << " is a positive and even\n";
        }
        else
        {
            std::cout << value << " is positive and odd\n";
        }
    }

    return 0;
}
```

The **nesting level** (a.k.a. **nesting depth**) of a function is the maximum number of nested blocks the program experiences (including the outer block). In the above example, the nesting depth is 3 even though there are 4 total blocks.

**Best practice:** keep the nesting level of your functions to 3 levels or less. If your function needs more levels, consider refactoring your function into sub-functions.

# [6.2 - User-defined Namespace](https://www.learncpp.com/cpp-tutorial/user-defined-namespaces/)
As a refresher, naming collisions occur when two identical identifiers are introduced in the same scope and the compiler can't disambiguate which one to use. This becomes more of a problem as programs get larger (more files and more functions).

To avoid this, put your functions inside your own namespaces. For this reason, the standard library was moved into the `std` namespace.

## Defining Your Own Namespaces
C++ provides namespaces (e.g. `global`) and libraries do as well (e.g. `std`), but you can create your own **user-defined namespaces**. For example, we can define a function `doSomething()` in namespace `foo` and `goo`:

foo.h
```cpp
namespace foo
{
    int doSomething(int x, int y);
}
```
foo.cpp
```cpp
#include "foo.h"

namespace foo
{
    int doSomething(int x, int y)
    {
        return x + y;
    }
}
```
goo.h
```cpp
namespace goo
{
    int doSomething(int x, int y);
}
```
goo.cpp
```cpp
#include "goo.h"

namespace goo
{
    int doSomething(int x, int y)
    {
        return x - y;
    }
}
```

And we can tell the compiler to look in a particular namespace for the right function using the **scope resolution operator** (::). main.cpp then looks like:
```cpp
#include <iostream>
#include "goo.h"
#include "foo.h"

int main()
{
    std::cout << foo::doSomething(4, 3) << '\n';
    std::cout << goo::doSomething(4, 3) << '\n';
    return 0;
}
```

## Using the Scope Resolution Operator with No Name Prefix