# 2.1 - [Introduction to Functions](https://www.learncpp.com/cpp-tutorial/introduction-to-functions/)
A **function** is a reusable sequence of statements designed to do a particular job.

Functions can call other functions. For example

```cpp
int functionA()
{
    std::cout << "Function A is the caller.\n";
    functionB();        // Function b is the callee, or called function
    return 0;
}
```

## An Example of a User-defined Function
The general syntax is
```cpp
returnType identifier()
{
    //  your code here
}
```

## Nested Functions Are NOT Supported
Don't do this in C++:
```cpp
#include <iostream>

int main()
{
    int foo()
    {
        // foo code
    }
    return 0;
}
```

# 2.2 - [Function Return Values](https://www.learncpp.com/cpp-tutorial/function-return-values/)

Set the function's **return type** to indicate what type of value will be stored.

A **return statement** indicates the specific value being returned to the caller. The specific value returned is the **return value**. When the return statement is executed, the return value is copied from the function back to the caller. This process is called **return by value**.

## Void Return Values
Functions are not required to return values. To tell the compiler that the function does not return a value, use the **void** return type.

```cpp
void doPrint()
{
    std::cout << "In doPrint()" << '\n';
    // no return statement
}
```
## Returning to Main

**Best practice: Your main function should return 0 if the program ran normally.**

C++ disallows calling the *main* function explicitly.

C++ defines three status codes:
- 0
- EXIT_SUCCESS
- EXIT_FAILURE

```cpp
#include <cstdlib>    // for EXIT_SUCCESS and EXIT_FAILURE

int main()
{
    return EXIT_SUCCESS;
}
```
## A Few Additional Notes About Return Values
- A function *must* return a value of the type indicated (except for main which will assume a return value of 0 if one is not explicitly provided)
- When a return statement is executed, the function returns back to the caller immediately at that point. Additional code is ignored.
- A function can only return a single value back to the caller each time it is called. The returned value doesn't have to be a literal; it can be a variable or the result of another function call.
- A function is free to define what its return value means (e.g. status code, calculation result, etc.)

## Reusing Functions
DRY: Don't Repeat Yourself

Make code modular, remove redundancies, and maximize reusability.

# 2.3 - [Introduction to Function Parameters and Arguments](https://www.learncpp.com/cpp-tutorial/introduction-to-function-parameters-and-arguments/)

## Function Parameters and Arguments
A **function parameter** is a variable used in a function. Function parameters work almost identically to variables defined inside the function, but with one difference: they are always initialized with a value provided by the caller of the function.

An **argument** is a value that is passed from the caller to the function when a function call is made.

## How Parameters and Arguments Work Together
When a function is called, all of the parameters of the function are created as variables and the value of each argument is *copied* to the matching parameter within the function. This process is called **pass by value**.
For example,
```cpp
#include <iostream>
void printValues(int x, int y)
{
    // printValues's parameter x is created and initalized with the value passed in
    // printValues's parameter y is created and initalized with the value passed in
    std::cout << x << '\n';
    std::cout << y << '\n';
}

int main()
{
    printValues(6, 7);

    return 0;
}
```

## A Warning About Function Argument Order of Evaluation

**Warning:** The C++ specification does not specify the order of operations in copying function arguments to parameters. So if order matters, you must explicitly define the order of execution. For example, order may matter in the following scenario:
```cpp
someFunction( a(), b() ); // a() or b() may be called first
```
In which case you can specify order by
```cpp
int avar{ a() };
int bvar{ b() ];
someFunction( avar, bvar); // a() or b() may be called first
```

# 2.4 - [Introduction to Local Scope](https://www.learncpp.com/cpp-tutorial/introduction-to-local-scope/) 
Function parameters, as well as variables defined inside the function body, are called **local variables** (as opposed to global variables).

## Local Variable Lifetime
An object's **lifetime** is defined to be the time between its creation and destruction. Note that variable creation and destruction happens when the program is running (a.k.a. runtime), not at compile time. Therefore, lifetime is a runtime property.

Local variables are destroyed in the opposite order of creation at the end of the set of curly braces in which it is defined. For a function parameter, this means at the end of the function.

```cpp
#include <iostream>

void doSomething()
{
    std::cout << "Hello!\n";
}

int main()
{
    int x{ 0 }; // x's lifetime begins here

    doSomething(); // x is still alive during this function call

    return 0;
} // x's lifetime ends here
```
## Local Scope
An identifier's **scope** determines where the identifier can be accessed within the source code. Scope is a compile-time property, and trying to use an identifier when it's out of scope will result in a compile errror.

A local variable's scope begins at the point of variable definition and stops at the end of the set of curly braces they are defined in. This ensures that a variable cannot be used before the point of definition.

```cpp
#include <iostream>

// x is not in scope anywhere in this fnxn
void doSomething()
{
    std::cout << "Hello!\n";
}

int main()
{
    // x cannot be used here because it's not in scope yet

    int x{ 0 }; // x comes in scope

    doSomething();

    return 0;
} // x goes out of scope
```
An interesting example:
```cpp
#include <iostream>

// add's x and y are created and enter scope here
void add(int x, int y)
{
    // add's x and y are visible/usable within this fnxn only
    return x + y;
} // add's x and y go out of scope and are destroyed here

int main()
{
    // x cannot be used here because it's not in scope yet

    int x{ 5 }; // main's x is created, initialized, and enters scope here
    int y{ 6 }; // main's y is created, initialized, and enters scope here

    std::cout << add(x, y) << '\n';

    return 0;
} // main's x and y go out of scope and are destroyed here
```

**Key insight**: Names used for function params or variables declared in a function body are only visible within the function that declares them. This means local variables within a function can be named without regard for the names of variables in other functions. This helps keep functions independent.

**Best practice: Define your local variables as close to first use as reasonably possible.**

# 2.5 - [Why Functions Are Useful and How to Use Them Effectively](https://www.learncpp.com/cpp-tutorial/why-functions-are-useful-and-how-to-use-them-effectively/)
Benefits of functions:
- Organization
- Reusability
- Testing
- Extensibility
- Abstraction

Some guidance to effectively use functions:
- Statements that appear more than once in a program should generally be made into a function.
- Code that has a well-defined set of inputs and outputs is a good candidate for a function, especially if it's complicated.
- A function should generally perform one and only one task.
- When a function becomes too long or hard to understand, it can be split into multiple sub-functions. This is called **refactoring**.

# 2.6 - [Forward Declarations and Definitions](https://www.learncpp.com/cpp-tutorial/forward-declarations/)

A **forward declaration** allows us to tell the compiler about the existence of an identifier before actually defining the identifier. We write a forward declaration for a function using a declaration statement called a **function prototype**. The functino prototype consists ofthe function's return type, name, parameters, NO function body, and semicolon termination. For example,
```cpp
int add(int x, int y);
```

For an example of the utility of forward declarations, see the below script where the compiler throws an error because the add() function is called before it is defined.
```cpp
#include <iostream>

int main()
{
    std::cout << "The sum of 3 and 4 is: " << add(3, 4) << "\n";
    return 0;
}

int add(int x, int y)
{
    return x + y;
}
```
But if we add the forward declaration, we can remove the compiler error.
```cpp
#include <iostream>

int add(int x, int y); // forward declaration of add() using a function prototype

int main()
{
    std::cout << "The sum of 3 and 4 is: " << add(3, 4) << "\n";
    return 0;
}

int add(int x, int y)
{
    return x + y;
}
```

Note: parameter names are not required in a function prototype, but their inclusion is best practice. The following works, but IS NOT best practice.
```cpp
int add(int, int); // valid function prototype, but not best practice without parameter names
```
## Declarations vs. Definitions
A **definition** acutally implements (for functions or types) or instantiates (for variables) the identifier. For example,
```cpp
int add(int x, int y) // implements function add()
{
    int z{ x + y}; // instantiates variable z
    return z;
}
```
A definition is needed to satisfy the *linker*.
Note: functions that share an identifier but have different parameters are considered to be different functions.

A **declaration** is a statement that tells the *compiler* about the existence of an identifier and its type information. For example,
```cpp
int add(int x, inty);   // tells the compiler the add fnxn exists, takes two int params, and returns an int
int x;  // tells the compiler about an integer variable named x
```
A declaration is needed to satisfy the *compiler*.

All definitions are declarations, but not all declarations are definitions. An example of tha declaration that is not a definition is the function prototype - it satisfies the compiler but not the linker. Declarations that aren't definitions are called **pure declarations**. 

# 2.7 - [Programs With Multiple Code Files](https://www.learncpp.com/cpp-tutorial/programs-with-multiple-code-files/)
In VS Code and g++, you need 