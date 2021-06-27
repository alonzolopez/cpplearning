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

# [6.4 - Introduction to Global Variables](https://www.learncpp.com/cpp-tutorial/introduction-to-global-variables/)

## Declaring and naming global variables
By convention, global variables are named at the top of a file, below the includes but above any code.

**Best practice:** consider using a "g" or "g_" prefix for global variables to help differentiate them from local variables.

## Global variables have file scope and static duration
Global variables have **file scope** (a.k.a. **global scope** or **global namespace scope**) meaning they are visible from the point of declaration until the end of the file in which they are declared. Once declared, they can be used anywhere inside that file.

Global variables are part of the global namespace scope.

Global variables are created when the program starts and destroyed when it ends. This is called **static duration**. Variables with static duration are sometimes called **static variables**.

Unlike local variables, global variables are zero-initialized by default.

## Global variable initialization
Non-constant global variables can be optionally initialized.

```cpp
int g_x;        // zero-initialized by default
int g_x {};     // zero-initialized
int g_x { 1 };  // initialized with value
```

## Constant global variables
Constant global variables must be initialized
```cpp
#include <iostream>

const int g_x;      // error: not initialized
constexpr int g_w;  // error: not initialized

const int g_y { 1 };
constexpr int g_z { 2 };
```

**Warning:** Avoid using non-constant global variables.

## Quick Summary
```cpp
// non-constant global variables
int g_x;        // zero-initialized by default
int g_x {};     // zero-initialized
int g_x { 1 };  // initialized with value

// const global variables
const int g_x;          // error: not initialized
const int g_y { 1 };    // good

// constexpr global variables
constexpr int g_w;          // error: not initialized
constexpr int g_z { 2 };    // good
```

# [6.5 - Variable Shadowing (name hiding)](https://www.learncpp.com/cpp-tutorial/variable-shadowing-name-hiding/)

When a variable inside a nested block has the same identifier as a variable in an outer block, it "hides" the outer variable when they are both in scope (i.e. in the block where the inner variable is defined). This is called **name hiding** or **shadowing**.

```cpp
#include <iostream>

int main()
{   // outer block

    int apples { 5 };   // the outer block apples

    {   // nested block
        // apples here refers to the outer block apples
        std::cout << apples << '\n';    // print value of outer block apples

        int apples{};   // define apples in the scope of the nested block

        // apples now refers to the nested block apples
        // the outer block apples is temporarily hidden

        apples = 10;    //  assigns the value to nested block apples

        std::cout << apples << '\n';    // print value of nested block apples
    }   // nested block apples destroyed

    std::cout << apples << '\n';    // print outer block apples

    return 0;
}   // outer block apples destroyed
```

## Shadowing of global variables
Similar to how nested variables can shadow local variables in an outer block, local variables can shadow global variables when the local variable is in scope:
```cpp
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
```

## Avoid variable shadowing
**Best practice:** avoid variable shadowing. This is easy if you use the "g_" prefix for global variables.

# [6.6 - Internal Linkage](https://www.learncpp.com/cpp-tutorial/internal-linkage/)

An identifier with **internal linkage** can be seen and used within a single file, but is not accessible from other files (i.e. it's not exposed to the linker). If two files have identically named identifiers with internal linkage, those identifiers will be treated as independent.

## Global variables with internal linkage

Global variables with internal linkage are sometimes called **internal variables**

To make a non-constant global variable internal, we use the `static` keyword.

`const` and `constexpr` global variables have internal linkage by default (i.e. don't need the `static` keyword).

Because internal linkage means identical identifiers across files will be treated as independent, `g_x` is independent across two files:
a.cpp:
```cpp
constexp int g_x { 2 };
```

main.cpp:
```cpp
#include <iostream>

static int g_x { 3 };

int main()
{
    std::cout << g_x '\n';

    return 0;
}
```

## The one-definition rule and internal linkage
Because internal objects (and functions) defined in different files are considered independent, they do not violate the one definition rule.

## Functions with internal linkage
Internal linkage applies to *identifiers* including functions.

In the following example, the call to `add()` in main.cpp WILL NOT link:
a.cpp:
```cpp
// static declaration means only usable within this file
// attempts to access it from another file via forward declaration will fail
static add(int x, int y)
{
    return x + y;
}
```

main.cpp:
```cpp
#include <iostream>

int add(int x, int y);  // forward declaration

int main()
{
    std::cout << add(3, 4) << '\n';

    return 0;
}
```

# [6.7 - External Linkage](https://www.learncpp.com/cpp-tutorial/external-linkage/)
An identifier with **external linkage** can be seen and used both from the file in which it is defined and externally from other code files via a forward declaration.

Functions have external linkage by default. In order to call a function defined in another file, you can forward declare it in your file (or use an include) to satisfy the compiler, and the linker will take care of linking the function call to the function definition. For example,

a.cpp:
```cpp
#include <iostream>

// fnxn definition with external linkage (can be seen in main.cpp)
void sayHi()
{
    std::cout << "Hi!";
}
```

main.cpp:
```cpp
// forward declaration to satisfy the compiler
void sayHi();   

int main()
{
    // call to fnxn defined in another file
    // the linker will connect this fnxn call to the definition in a.cpp
    sayHi();    

    return 0;
}
```

## Global variables with external linkage
Non-const global variables are external by default. On the other hand, to make const global variables **external variables**, use the `extern` keyword.

```cpp
int g_x { 2 };  // non-const vars external by default

extern const int g_y { 3 };     // use extern to make const var external
extern constexpr int g_z { 3 }; // use extern to make constexpr var external

int main()
{
    return 0;
}
```

## Variable forward declarations via the extern keyword
To use the external global var in another file, you must place a forward declaration for that variable in that other file using the extern keyword. There are a few notes to consider:

**Warning:** if you want to define an uninitialized non-const global variable, don't use the extern keyword, otherwise C++ will think you're trying to make a forward declaration for that var.

**Warning:** constexpr vars cannot be forward declared, so there is no point/value to giving them external linkage.

With that in mind, here is an example of using external vars externally:

a.cpp:
```cpp
// global var definitions
int g_x { 2 };  // non-const global vars have external linkage by default
extern const int g_y { 3 }; // give g_y external linkage
```

main.cpp:
```cpp
#include <iostream>

extern int g_x;         // forward declaration for non-const global
extern const int g_y;   // forward declaration for const global

int main()
{
    std::cout << g_x;

    return 0;
}
```

## File scope vs global scope

There is some confusion between these terms due to their informal use.

**File scope** is more often applied to global vars with internal linkage (i.e. can be seen within the file).

**Global scope** is more often applied to global vars with external linkage (i.e. can be used across the whole program assuming they have the appropriate forward declarations).

## The initialization order problem of global variables

**Warning:** dynamic initialization of global variables causes a lot of problems in C++. Avoid it whenever possible, i.e. don't make the initialization of variables dependent on other variables.

## Quick Summary

```cpp
// External global var definitions
int g_x;    // non-const global var external and zero-initialized by default
extern const int g_x{ 1 };      // const external global var
extern constexpr int g_x{ 2 };  // constexpr external global var

// Forward declarations
extern int g_y;             // forward declaration of global var
extern const int g_y;       // forward declaration of const global var
extern constexpr int g_y;   // not allowed: constexpr vars can't be forward declared
```

# [6.8 - Global constants and inline variables](https://www.learncpp.com/cpp-tutorial/global-constants-and-inline-variables/)

This section discusses strategies to define and use global constants (e.g. gravity or friction params) that are used across multiple files. Define them in one place so if you need to change them, you don't have to change them everywhere.

## Global constants as internal variables

Pre-C++17, the easiest way to do this is:
1. Create a header file to hold these constants
2. Define a namespace in this header file
3. Add all your constants inside this namespace as *constexpr*
4. #include the file wherever you need it; use the scope resolution operator to use the constants (::)

For an example of this, see [constants.h](../6-projects/6-8-1/constants.h) and [main.cpp](../6-projects/6-8-1/main.cpp).

## Global constants as external variables
Whie global constants as *internal* variables is good for small programs, it has some downsides for large programs:

1. Changing a single constant will require recompiling every file that includes the constant header, which may lead to long rebuild times for large projects.
2. If the constants are large in size and can't be optimized away, this can use a lot of memory.

As an alternative, turn these constants into external variables so it is initalized once inside a source file and shared across all files.

**Note:** use `const` instead of `constexpr` in this method because `constexpr` can't be forward declared.

Now the symbolic constants will get initiated only once (in `constants.cpp`) instead of in each code file where `constants.h` is included. All uses of constants will be linked to `constants.cpp` and changes will only require recompiling `constants.cpp`

HOWEVER, there are a couple of downsides to this.
1. Constants are now considered compile-time constants only within the file they are actually defined in (`constants.cpp`). In other files, the compiler will only see the forward declaration which doesn't define a constant value and must be resolved by the linker. This means they will be treated as *runtime* constant values in other files, and not usable wherever a compile-time constant is required.
2. Because compile-time constants can typically be optimized more than runtime constants, the compiler may not be able to optimize as much.

See an example of global constants as extern variables with [main.cpp](../6-projects/6-8-2/main.cpp), [constants.h](../6-projects/6-8-2/constants.h), and [constants.cpp](../6-projects/6-8-2/constants.cpp)

## Global constants as inline variables
If your compiler is C++17 capable, use `inline constexpr` global variable in a header file.

For an example, see [main.cpp](../6-projects/6-8-3/main.cpp) and [constants.h](../6-projects/6-8-3/constants.h).

# [6.9 - Why Global Variables Are Evil](https://www.learncpp.com/cpp-tutorial/why-global-variables-are-evil/)
**Best practice:** Avoid using non-const global variables.

If you do need to use non-const global variables, try implementing the following tips:
1. Define them in namespaces.
2. Instead of allowing direct access to the global var, "encapsulate" the var in an "access fnxn" 
3. Instead of using global vars directly in functions that do work, pass them in as function arguments to keep the function modular (i.e. not dependent on the global var).

For an example of all these in action, see [main.cpp](../6-projects/6-9/main.cpp)

# [6.10 - Static Local Variables](https://www.learncpp.com/cpp-tutorial/static-local-variables/)
Using the `static` keyword on a local variable changes its duration from automatic to static duration, meaning it is now created at the start of the program and destroyed at then end of the program (just like a local var). However, unlike global vars, they are limited to block scope, meaning they cannot be tampered with by other fnxns.

A common use-case for static variables is generating unique IDs.

## Overusing static local variables
**Best practice:** avoid `static` local variables unless the variable never needs to be reset (e.g. unique IDs). `static` local variables decrease reusability and make functions harder to reason about. They may introduce an internal state that alters the function's performance.

## Quiz
Using the `static` keyword on a global variable gives the variable internal linkage (the variable cannot be exported to other files).

Using the `static` keyword on a local variable gives it static duration, meaning *it will only be created once*, and it will not be destroyed until the end of the program.

# [6.11 - Scope, duration, and linkage summary](https://www.learncpp.com/cpp-tutorial/scope-duration-and-linkage-summary/)
Good summary on scope, duration, and linkage.

# [6.12 - Using declarations and using directives](https://www.learncpp.com/cpp-tutorial/using-declarations-and-using-directives/)
A **qualified name** is a name that includes an associated scope, most often using the scope resolution operator. For example,
```cpp
std::cout // identifier cout is qualified by namespace std
::foo // identifier foo is qualified by the global namespace

class C;

C::s_member; // s_member is qualified by Class C
obj.x; // x is qualified by class object obj
ptr->y; // y is qualified by pointer to class object ptr
```

An **unqualified name** does not include a scoping qualifier. For example,
```cpp
cout;
x;
```

## Using declarations
A **using declaration** is okay to use inside a function. It allows us to use an unqualified name (with no scope) as an alias for a qualified name. For example,
```cpp
#include <iostream>

int main()
{
    // tells the compiler to resolve cout to std::cout
    using std::cout; 
    cout << "Hello world!";

    return 0;
}
```
Note that if there is a naming conflict between `std::cout` and `cout`, `std::cout` will be preferred.


## Using directives
**using directives** are NOT okay to use. Avoid using them. The import *all* of the names from a namespace, significantly increasing the possibility for namespace collissions. They look like this:
```cpp
#include <iostream>

namespace a
{
    int x{ 10 };
}

namespace b
{
    int x{ 20 };
}

int main()
{
    using namespace a;
    using namespace b;

    std::cout << x << '\n';

    return 0;
}
```

Notice the naming collision in the above example. That's one reason why we don't use `using directives`.

## The scope of using declarations and directives
`using declaration` and `using directive` have block scope if used in a block.

If used in the global namespace, they have file scope.

## Cancelling or replacing a using statement
You can't cancel or replace a using statement. The best you can do is limit its scope using block scoping rules, or even better, use the scope resolution operator to avoid all this.

## Best practices for using statements
**Best practice:** prefer explicit namespaces over `using statements`. Avoid `using directives` altogether. Using `declarations` are okay to use inside blocks.

# [6.13 - Typedefs and type aliases](https://www.learncpp.com/cpp-tutorial/typedefs-and-type-aliases/)

**Typedefs** allow the programmer to create an *alias* for a data type (not a new type).

```cpp
int main()
{
    typedef double distance_t;

    // the following two are equivalent
    double howFar;
    distance_t howFar;

    // two more
    typedef long miles_t;
    typedef long speed_t;

    miles_t distance { 5 };
    speed_t mhz { 3200 };

    // because they are the same type, you can do this:
    distance = mhz;
}
```
There are a couple cons to the typedef above:
1. The order of the syntax is easily forgettable.
2. The syntax for typedefs gets ugly with more complex types, especially function pointers.

## Type Aliases
Instead, use the syntax for **type alias**. Given the following typedef:
```cpp
typedef double distanct_t;
```
instead use the following type alias:
```cpp
using distance_t = double; // define distance_t as an alias for type double
```

Note that this has nothing to do with the `using statements` from the previous lesson. It's fine to use this.

## Using type aliases for legibility
Using type aliases, we can identify what *purpose* a return value serves. For example,

```cpp
using testScore_t = int;
testScore_t GradeTest();
```

The above makes it obvious that the function returns a type representing the test score.

## Using type aliases for easier code maintenance
If you need to change the type of a family of objects that all use the same type alias, it's pretty straightforward. Change:
```cpp
using studentID_t = short;
```
to 
```cpp
using studentID_t = long;
```

However, you still need to be careful when changing types (e.g. integer to floating point value).

## Using type aliases for platform independent coding
Type aliases can be used to hide platform-specific details. For example, on some platforms `int` is 2 bytes, on others 4 bytes. Because `char`, `short`, `int`, and `long` give no indication of their size, we can use type aliases to define aliases that include the type's size in bits. For example,

```cpp
#ifdef INT_2_BYTES
using int8_t = char;
using int16_t = int;
using int32_t = long;
#else
using int8_t = char;
using int16_t = short;
using int32_t = int;
#endif
```

This will use the right combo of char, short, int, and long for the platform. This is exactly how fixed-width integers like `std::int8_t` are defined.

## Using type aliases to make complex types simple
Using type aliases, we can turn something that's hard to read like 
```cpp
std::vector<std::pair<std::string, int> > pairlist;
```
into 
```cpp
using pairlist_t = std::vector<std::pair<std::string, int> >; // make pairlist_t an alias for this crazy type
```

**Best practice:** favor type aliases over typedefs, and use them liberally to document the meaning of your types.

## Quiz
Turn 
```cpp
int printData();
```
to
```cpp
using error_t = int;
error_t printData();
```

# [6.14 - The Auto Keyword](https://www.learncpp.com/cpp-tutorial/the-auto-keyword/)
## Type inference for initialized variables

The `auto` keyword may be used to perform **type inference** (a.k.a. **type deduction**) to tell the compiler to infer the variable's type from the initializer's type. For example,
```cpp
auto d{ 5.0 };
auto i{ 1 + 2 };

// this also works with the return values from functions
int add(int x, int y)
{
    return x + y;
}

int main()
{
    auto sum { add(5,6) };
    return 0;
}
```

## Type inference for functions
**Best practice:** AVOID USING TYPE INFERENCE FOR FUNCTIONS.

If you do, it looks like this:
```cpp
auto add(int x, int y)
{
    return x + y;
}
```

Note that all return statements must return the same type, otherwise an error will result.

## Trailing return type syntax
The `auto` keyword can also be used to declare functions using a **trailing return syntax**. For example, the following function
```cpp
int add(int x, int y)
{
    return (x + y);
}
```
Using `auto`, this could be written as
```cpp
auto add(int x, int y) -> int
{
    return (x + y);
}
```
The traditional function syntax is recommended over this, but this will come up again later in lesson 10.15.

## Type inference for function parameter types
The following only works in C++20
```cpp
#include <iostream>

void addAndPrint(auto x, auto y)
{
    std::cout << x + y;
}

int main()
{
    addAndPrint(2, 3);      // int
    addAndPrint(4.5, 6.7);  // double
}
```
Prior to C++20, if you want to create generic functions that work with a variety of types, use `function templates`.

# [6.15 - Implicit type conversion (coercion)](https://www.learncpp.com/cpp-tutorial/implicit-type-conversion-coercion/)

The process of converting a value from one data type to another is called **type conversion**. These can happen in many different cases:
1. When assigning to or initializing a variable with a value of a different data type.
    ```cpp
    double d{ 3 };
    ```
2. When passing a value to a function where the function parameter is of a different data type.
    ```cpp
    void doSomething(long l)
    {
        ...
    }
    doSomething(3); // pass integer 3 into fnxn expecting a long
    ```
3. When returning a value from a function where the function return type is of a different data type.
    ```cpp
    float doSomething()
    {
        return 3.0; // 3.0 is a double; it gets converted to float
    }
    ```
4. Using a binary operator with operands of different types.
    ```cpp
    double division{ 4.0 / 3 };
    ```

There are two types of type conversion:
1. `implicite type conversion` where the compiler automatically transforms one data type into another.
2. `explicit type conversion` where the developer uses a casting operator to direct the conversion.

Within `implicit type conversion`, there are two basic types: `promotions` and `conversions`.

## Numeric promotion
Converting one fundamental data type to another *larger* fundamental data type from the same family is called **numeric promotion**. These are always safe and no data loss will result. 

"Numeric promotion" covers any type of promotion, and under that there are two types to call out:
1. **integral promotion**: converting an integer type narrower than int (e.g. bool, char, unsigned char, signed char, unsigned short, signed short) to an int or an unsigned int.
2. **floating point promotion** converting float to a double

## Numeric conversions
**Numeric conversion** is converting a value from a larger type to a similar smaller type or between different types. 

```cpp
double d{ 3 };  // convert int to double (b/w diff types)
short s{ 2 };   // convert int to short (larger to smaller type w/in same family)
```

Conversions may or may not result in a loss of data.

Converting a value into a type that doesn't have a large enough range to support the value will lead to unexpected results (e.g. overflow).

## Evaluating arithmetic expressions
The compiler requires operands to be of the same type when evaluating subexpressions - it will perform the necessary promotions and conversions:
- promotes operands below int to int
- if they do not match after integer promotion, converts the lower operand to the highest priority operand (see page for priority order)

# [6.16 - Explicit type conversion (casting) and static_cast](https://www.learncpp.com/cpp-tutorial/explicit-type-conversion-casting-and-static-cast/)
A **cast** (a.k.a. **type casting operator** ) represents a request by the programmer to do an explicit type conversion.

## Type casting
There are five types of casts:
1. C-style casts
2. static casts
3. const casts
4. dynamic casts
5. reinterpret casts

**Warning:** avoid const casts and reinterpret casts unless you have a very good reason to use them.

## C-style casts
Done as below
```cpp
int i1{ 10 };
int i2{ 4 };

// in C syntax
float f { (float)i1 / i2 };
// OR with fnxn-like syntax
float g { float(i1) / i2};
```
C-style casts can actually perform a variety of casts depending on the context (including the dangerous const and reinterpret casts). So prefer the C++ casts over this method.

**Warning:** avoid using C-style casts.

## static_cast
In C++, **static_cast** can be used to convert a value of one type to a value of another type.

It takes a single value as input and outputs the same value converted to the specified type inside the angle brackets. It's best used to convert one fundamental type to another.

```cpp
int i1 { 10 };
int i2 { 4 };

float f { static_cast<float>(i1) / i2 };
```

The main advantage of static_cast is that it provides compile-time checking.

**Best practice:** favor static_cast when you need to convert a value from one type to another type.

## Using casts to make implicit type conversions clear
The compiler will either throw a warning or error when an unsafe implicit type conversion is performed, but we can use a static_cast to make it clear that a conversion is intended. For example,
```cpp
int i { 48 }; 
int g { 4.5 };  // error: direct list init disallows narrowing conversions

char ch = i;    // warning: potentially unsafe implicit conversion
char ch { static_cast<char>(i) }; // GOOD: intentional conversion
```

# [6.17 - Unnamed and inline namespaces](https://www.learncpp.com/cpp-tutorial/unnamed-and-inline-namespaces/)
There are two permutations on namespaces worth knowing about:
## 1. Unnamed (anonymous) namespaces
**unnamed namespaces** (a.k.a. **anonymous namespaces**) are namespaces that are defined without a name. All content is:
1. treated as if it is part of the parent namespace
2. given internal linkage (content can't be seen outside of the file); this is easier than marking a bunch of content `static`.

## 2. Inline namespaces
An **inline namespace** is typically used to version content. Anything declared part of the inline namespace is considered part of the parent namespace, but it is not given internal linkage. For example, you may have different versions of a function that you want to define inside separate namespaces (e.g. `v1`, `v2`, `v3`). To specify which function call can be accessed without use of the scope resolution operator (::), i.e. as if it were in the global namespace, use an inline namespace. If you want to roll out a new version as the default, update the inline tag.
```cpp
inline namespace v1
{
    void doSomething()
    {
        std::cout << "v1\n";
    }
}

namespace v2
{
    void doSomething()
    {
        std::cout << "v2\n";
    }
}

int main()
{
    v1::doSomething();  // calls v1's fnxn
    v2::doSomething();  // calls v2's fnxn
    doSomething();      // calls v1's fnxn
}
```
To make 
```cpp
namespace v1
{
    void doSomething()
    {
        std::cout << "v1\n";
    }
}

inline namespace v2
{
    void doSomething()
    {
        std::cout << "v2\n";
    }
}

int main()
{
    v1::doSomething();  // calls v1's fnxn
    v2::doSomething();  // calls v2's fnxn
    doSomething();      // calls v2's fnxn
}
```