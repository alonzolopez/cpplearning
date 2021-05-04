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
Using the scope resolution operator looks in the global namespace. For example,
```cpp
#include <iostream>

void print()
{
    std::cout << "Hello."; 
}
int main()
{
    ::print();

    return 0;
}
```

## Identifier Resolution from within a Namespace
If an identifier is used within a namespace and no scope resolution is provided, the compiler first tries to resolve the identifier in the active namespace, then if no matching identifier is found the compiler checks each containing namespace in sequence ending with the global namespace. For example,
```cpp
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
```

## Multiple namespace blocks are allowed
It's legal to declare namespace blocks in multiple locations (e.g. across multiple header/source files or multiple places within the same file). For an example of namespaces declared across multiple header and source files then used in the `main.cpp`, see [foo.h](../6-projects/6-2-1/foo.h), [foo.cpp](../6-projects/6-2-1/foo.cpp), [goo.h](../6-projects/6-2-1/goo.h), [goo.cpp](../6-projects/6-2-1/goo.cpp), [main.cpp](../6-projects/6-2-1/main.cpp)

## Nested Namespaces
Namespaces can be nested and accessed like
```cpp
#include <iostream>

namespace foo
{
    namespace goo
    {
        int add(int x, int y)
        {
            return x + y;
        }
    }
}

int main()
{
    std::cout << foo::goo::add(1, 2) << '\n';
    return 0;
}
```

Since C++17, you can also nest namespaces as
```cpp
#include <iostream>

namespace foo::goo
{
    int add(int x, int y)
    {
        return x + y;
    }
}

int main()
{
    std::cout << foo::goo::add(1, 2) << '\n';
    return 0;
}
```

## Namespace aliases
You can also define aliases for full namespaces. For example,
```cpp
int main()
{
    namespace boo = foo:goo;
    std::cout << boo::add(1, 2);    // equivalent to foo::goo::add()
    return 0;
}   // the boo alias ends here
```

## When you should use namespaces
- namespaces can be used to separate application-specific code from code that might be reusable later
- when writing a library to distribute to others, always place your code inside a namespace

# [6.3 - Local Variables](https://www.learncpp.com/cpp-tutorial/local-variables/)
As a refresher, **scope** determines where an identifier can be accessed within the source code. It's a compile-time property. When an identifier can be accessed, we say it is in scope. When it cannot be accessed, we say it is out of scope.

## Local variables have block scope
Local variables have **block scope**, meaning they are *in scope* from the point of their definition and go out of scope at the end of the block they are defined in. That includes function parameters.
```cpp
int max(int x, int y)   // x and y enter scope here
{
    int max{ (x > y) ? x : y};  // max enters scope here
    return max;
}   // x, y, and max go out of scope here

int main()
{
    int i { 5 };        // i enters scope here
    double d { 4.0 };   // d enters scope here

    return 0;
}   // i and d go out of scope here
```

**Note:** all variable names must be unique within a given scope.

## Local variables have automatic storage duration
A variable's **storage duration** (a.k.a. **duration**) determines what rules govern when and how a variable will be created and destroyed. In most cases, a variable's storage duration directly determines its `lifetime`.

Local vars have automatic storage duration, which means they are created at the point of definition and destroyed at the end of the block they are defined in.

## Local variables in nested blocks
Local variables defined inside nested blocks go out of scope at the end of the block. On the other hand, nested blocks are considered part of the scope of the block in which they are nested in, so variables defined in the outer block *can* be seen inside the nested block.

```cpp
#include <iostream>

int main()
{
    int x { 5 };        // x enters scope here

    {
        int y { 7 };    // y enters scope here
        std::cout << x << " + " << y << " = " << x + y << '\n';
    }                   // y goes out of scope and is destroyed here

    return 0;
}                       // x goes out of scope and is destroyed here
```

## Local variables have no linkage
Identifiers have a property called `linkage`. An identifier's **linkage** determines whether other declarations of that name refer to the same object or not. 

Local variables have no linkage, which means that each declaration refers to a unique object. For example,

```cpp
int main()
{
    int x { 2 };        // local variable, no linkage

    {
        int x { 3 };    // this identifier refers to a different object than the previous x
    }
}
```
This concept will come up again in the subsequent lessons.

## Variables should be defined in the most limited scope
**Best practice:** define variables in the most limited existing scope (by limiting the scope, you reduce the number of active variables and the complexity of the program). Avoid creating new blocks whose only purpose is to limit the scope of variables.

## Scope vs duration vs lifetime
A variable's scope determines where the variable is accessible. Duration defines the rules that govern when a variable is created and destroyed. A variable's lifetime is the actual time between its creation and destruction.

Local variables have block scope, which means they can be accessed inside the block in which they are defined.

Local variables have automatic duration, which means they are created at the point of definition and destroyed at the end of the block in which they are defined.
