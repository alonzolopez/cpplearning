# [10.1 - Function parameters and arguments](https://www.learncpp.com/cpp-tutorial/function-parameters-and-arguments/)
A **function parameter** (a.k.a. **formal parameter**) is a variable declared in the function declaration.
```cpp
void foo(int x); // x is a parameter

void foo(int x) // x is a parameter
{

}
```

An **argument** (a.k.a. **actual parameter**) is the value that is passed to the function by the caller.
```cpp
foo(6); // 6 is the argument passed to the parameter x
foo(y+1); // the value y+1 is passed to the parameter x
```

When a function is called, all of the parameters of the function are created as variables, and the values of the arguments are copied into the parameters (normally). The *parameters have local scope*, i.e. they are created when the function is invoked and destroyed when the function block terminates.

There are 3 primary methods of passing arguments to functions:
1. pass by value
2. pass by reference
3. pass by address

# [10.2 - Passing arguments by value](https://www.learncpp.com/cpp-tutorial/passing-arguments-by-value/)
By default, non-pointer arguments in C++ are **passed by value**, i.e. the argument's value is *copied* into the value of the corresponding function parameter.

Because the argument is *copied* into the function parameter, the original argument cannot be modified by the function.

When to use pass by value:
* when passing fundamental types or enumators
* AND when the function does not need to change the argument

When to NOT use pass by value:
* when passing structs or classes (can incur a significant performance penalty)

# [10.3 - Passing arguments by reference](https://www.learncpp.com/cpp-tutorial/passing-arguments-by-reference/)
To pass a variable by reference, we simply declare the function parameters as references instead of normal variables:
```cpp
void addOne(int &ref)
{
    ref = ref + 1;
}

int main()
{
    int value{ 5 };

    std::cout << "value = " << value << '\n';
    addOne(value);
    std::cout << "value = " << value << '\n';
    return 0;
}
```
The reference to the original argument is treated exactly the same as the variable itself, meaning we can modify the orginal argument (as shown above).

## Returning multiple values via out parameters
**Recommendation:** avoid out parameters if possible. If you need to use them, suffix them with "_out" to indicate that they are out parameters and will be modified.

## Limitations of pass by reference
Non-const references can only reference non-const l-values (e.g. non-const variables), so a reference parameter cannot accept an r-value or const l-value.

## Pass by const reference
**Best practice:** when passing an argument by reference, use a const reference unless you need to change the value of the argument. This means:
* we guarantee that the function will not change the argument (and the compiler checks this)
* allows us to pass r-values and const l-values in addition to non-const l-values

## References to pointers
You can pass a pointer by reference and have the function change the address of the pointer.

You can also pass a C-style array by reference (which decays to a pointer), but you need to explicitly define the array size in the function parameter. There are ways to make this work with arrays of multiple sizes using templates (a future lesson).

## Pros and cons of pass by reference
**Best practice:** use pass by (const) reference instead of pass by value for structs and classes and other expensive-to-copy types.

# [10.4 - Passing arguments by address](https://www.learncpp.com/cpp-tutorial/passing-arguments-by-address/)
**Passing an argument by address** involves passing the address of the argument variable rather than the variable itself. *The argument is an address* (e.g `&value`), therefore the function parameter must be a pointer (e.g. `int* ptr`). 

```cpp
#include <iostream>

void foo(int* ptr)
{
    *ptr = 6;
}

int main()
{
    int value{ 5 };

    std::cout << "value = " << value << '\n';
    foo(&value);
    std::cout << "value = " << value << '\n';
    return 0;
}
```

Reminder: we can use indirection through the pointer to modify the value at the address.

Reminder: fixed arrays decay into pointers when passed into a function, so the length must be passed as a separate parameter.
```cpp
void printArray(int* array, int length)
{
    // check that the pointer is not a nullptr
    if (!array)
        return;

    for (int index{}; index < length; ++index)
    {
        std::cout << array[index] << ' ';
    }
}

int main()
{
    int array[6]{ 6, 5, 4, 3, 2, 1 };
    printArray(array, 6);
}
```

## Addresses are actually passed by value
When passing a pointer to a function as an argument, the pointer's value (the address it points to) is *copied* from the argument to the function's parameter. Therefore, modifying the address the pointer points to (e.g. setting it to `nullptr`) won't affect the original pointer. However, both the function copy and the original argument still point to the same address, so you can use the function's copy to modify the value at the original address.

## Passing addresses by reference
If you do want to modify the address that a pointer points to, pass it by reference:
```cpp
#include <iostream>

void setToNull(int* &tempPtr)
{
    tempPtr = nullptr;
}
```

## Pros and cons of pass by address
**Best practice:** prefer pass by reference to pass by address whenever applicable.

When to use pass by address:
* when passing built-in arrays (if you're okay with the fact that they decay to pointers)
* when passing a pointer and nullptr is a logically valid argument

When to not use pass by address:
* when passing a pointer and nullptr is NOT a logically valid argument
* when passing structs or classes (use pass by reference)
* when passing fundamental types (use pass by value)

# [10.5 - Returning values by value, reference, and address](https://www.learncpp.com/cpp-tutorial/returning-values-by-value-reference-and-address/)
