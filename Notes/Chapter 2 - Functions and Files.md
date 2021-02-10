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