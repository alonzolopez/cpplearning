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
Left off on: A few additional notes about return values
