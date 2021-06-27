# Chapter 11 - Functions
## [11.1 - Function parameters and arguments](https://www.learncpp.com/cpp-tutorial/function-parameters-and-arguments/)
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

## [11.2 - Passing arguments by value](https://www.learncpp.com/cpp-tutorial/passing-arguments-by-value/)
By default, non-pointer arguments in C++ are **passed by value**, i.e. the argument's value is *copied* into the value of the corresponding function parameter.

Because the argument is *copied* into the function parameter, the original argument cannot be modified by the function.

When to use pass by value:
* when passing fundamental types or enumators
* AND when the function does not need to change the argument

When to NOT use pass by value:
* when passing structs or classes (can incur a significant performance penalty)

## [11.3 - Passing arguments by reference](https://www.learncpp.com/cpp-tutorial/passing-arguments-by-reference/)
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

### Returning multiple values via out parameters
**Recommendation:** avoid out parameters if possible. If you need to use them, suffix them with "_out" to indicate that they are out parameters and will be modified.

### Limitations of pass by reference
Non-const references can only reference non-const l-values (e.g. non-const variables), so a reference parameter cannot accept an r-value or const l-value.

### Pass by const reference
**Best practice:** when passing an argument by reference, use a const reference unless you need to change the value of the argument. This means:
* we guarantee that the function will not change the argument (and the compiler checks this)
* allows us to pass r-values and const l-values in addition to non-const l-values

### References to pointers
You can pass a pointer by reference and have the function change the address of the pointer.

You can also pass a C-style array by reference (which decays to a pointer), but you need to explicitly define the array size in the function parameter. There are ways to make this work with arrays of multiple sizes using templates (a future lesson).

### Pros and cons of pass by reference
**Best practice:** use pass by (const) reference instead of pass by value for structs and classes and other expensive-to-copy types.

## [11.4 - Passing arguments by address](https://www.learncpp.com/cpp-tutorial/passing-arguments-by-address/)
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

### Addresses are actually passed by value
When passing a pointer to a function as an argument, the pointer's value (the address it points to) is *copied* from the argument to the function's parameter. Therefore, modifying the address the pointer points to (e.g. setting it to `nullptr`) won't affect the original pointer. However, both the function copy and the original argument still point to the same address, so you can use the function's copy to modify the value at the original address.

### Passing addresses by reference
If you do want to modify the address that a pointer points to, pass it by reference:
```cpp
#include <iostream>

void setToNull(int* &tempPtr)
{
    tempPtr = nullptr;
}
```

### Pros and cons of pass by address
**Best practice:** prefer pass by reference to pass by address whenever applicable.

When to use pass by address:
* when passing built-in arrays (if you're okay with the fact that they decay to pointers)
* when passing a pointer and nullptr is a logically valid argument

When to not use pass by address:
* when passing a pointer and nullptr is NOT a logically valid argument
* when passing structs or classes (use pass by reference)
* when passing fundamental types (use pass by value)

## [11.5 - Returning values by value, reference, and address](https://www.learncpp.com/cpp-tutorial/returning-values-by-value-reference-and-address/)

### Return by value
When to use return by value:
* when returning variables that were declared inside the function
* when returning function arguments that were passed by value

When not to use return by value:
* when returning a built-in array or pointer (use return by address)
* when returning a large struct or class (use return by reference)

### Return by address
When to use return by address:
* when returning dynamically allocated memory and you can't use a type that handles allocations for you (though you should avoid this and instead use types that handle allocation for you)
* when returning function arguments that were passed by address

When not to use return by address:
* when returning variables that were declared inside a function that will go out of scope at the end of the function or parameters that were passed by value (use return by value)
* when returning a large struct or class (use return by reference)

### Return by reference
When to use return by reference:
* when returning a reference parameter
* when returning a member of an object that was passed into the function by reference or address
* when returning a large struct or class that will not be destroyed at the end of the function (e.g. one that was passed in by reference)

When to not use return by reference:
* when returning variables that were declared inside the function or parameters that were passed by value (use return by value)
* when returning a built-in array or pointer value (use return by address)

### Mixing return references and values
```cpp
int returnByValue()
{
    return 5;
}

int& returnByReference()
{
    static int x{ 5 }; // static gives x file scope - ensures x isn't destroyed when the fnxn ends
    return x;
}

int main()
{
    int giana{ returnByReference() }; // treated as return by value

    int& ref{ returnByValue() }; // compiler error: initializing 
    // reference ref with returnByValue is like initializing it with an 
    // r-value, and a non-const ref cannot be initialized with an r-value 

    const int& cref{ returnByValue() }; // okay to initialize const
    // ref with r-value; the lifetime of the r-value is extended to 
    // match cref

    return 0;
}
```

### Lifetime extension doesn't save dangling references
```cpp
const int& returnByReference()
{
    return 5;
} // r-value 5 goes out of scope before the ref extends the lifetime of the r-value

int main()
{
    const int& ref{ returnByReference() }; // runtime error
}
```

### Returning multiple values
There are three ways to return multiple values to a function caller:
1. (not recommended) passing in arguments by reference to be used as out parameters.
2. Use a data-only struct if the struct will be reused.
    ```cpp
    #include <iostream>

    struct S
    {
        int m_x;
        double m_y;
    };

    S returnStruct()
    {
        S s;
        s.m_x = 5;
        s.m_y = 6.7;
        return s;
    }

    int main()
    {
        S s{ returnStruct() };
        std::cout << s.m_x << ' ' << s.m_y << '\n';

        return 0;
    }
    ```
3. Otherwise, use std::tuple to return and std::tie to unpack.
    ```cpp
    #include <tuple>
    #include <iostream>

    std::tuple<int, double> returnTuple()
    {
        return { 5, 6.7};
    }

    int main()
    {
        int a;
        double b;
        std::tie(a, b) = returnTuple();
        std::cout << a << ' ' << b << '\n';

        return 0;
    }
    ```

### Conclusion
* Most of the time return by value will be sufficient. It's the safest and most flexible way to return information to the caller.
* Return by reference or address can be useful when working with dynamically allocated objects, classes or structs.
* When using return by reference or address, make sure to not return a reference to, or address of, a variable that will not go out of scope at the end of the function.

### Quiz
#### Question 1
```cpp
int sumTo(int x);
```

#### Question 2
```cpp
void printEmployeeName(const Employee &e);
```

#### Question 3
```cpp
std::pair<int, int> minmax(int a, int b);
```

#### Question 4
```cpp
std::size_t getIndexOfLargestValue(const std::vector<int> &v);
```

#### Question 5
```cpp
const std::string& getElement(const std::vector<std::string> &array, std::size_t index);
```

## [11.6 - Inline Functions](https://www.learncpp.com/cpp-tutorial/inline-functions/)

Calling a function incurs a performance overhead cost. This is only significant for small functions called frequently, and *not* for large functions where the computation in the function itself is much more expensive than the overhead of the function call.

Marking a function as inline will avoid a function call and instead paste the contents of the function inline wherever the function is called. However, you should avoid this. The compiler will often do this for you where appropriate.

**Best practice:** avoid inline functions. Modern compilers will inline functions for you as appropriate.

### Inline functions are exempt from the one-definition per program rule
This is because inline functions do not actually result in a real function being compiled.

## [**11.7 - Function Pointers**](https://www.learncpp.com/cpp-tutorial/function-pointers/)
Function pointers hold the address of (i.e. point to) functions.

Functions have an l-value function type based on the return type, number of arguments, and argument types. When a function is called, execution jumps to the point of the function memory address:
```cpp
int foo() // code for foo starts at memory address 0x002717f0
{
    return 5;
}

int main()
{
    foo(); // jumps to address 0x002717f0

    return 0;
}
```

### **Pointers to functions**
Creating a non-const function pointer has the following ugly syntax:
```cpp
int (*fcnPtr)();
```
And creating a const function pointer goes:
```cpp
int (*const fcnPtr)();
```

### **Assigning a function to a function pointer**
Although it's not necessary, use the address-of operator& to get the address of a function when assigning to a function pointer for consistency's sake:
```cpp
int foo();
double goo();
int hoo(int x);
int zoo();

int (*fcnPtr1)(){ &foo };
fcnPtr1 = &zoo;
double (*fcnPtr2)(){ &goo };
int (*fcnPtr3)(int){ &hoo };
```

### **Calling a function using a function pointer**
```cpp
int foo(int x)
{
    return x;
}

int main()
{
    int (*fcnPtr)(int){ &foo };
    (*fcnPtr)(5);   // call the fnxn via explicit dereference
    fcnPtr(5);      // call the fnxn via implicit dereference

    return 0;
}
```
Note: implicit dereference looks just like a normal function call. That is because normal function names are pointers to functions anyways.

Note: default parameters are resolved at compile-time, and function pointers are resolved at run-time. Therefore, *default arguments cannot be resolved when making a function call through a function pointer*! You'll have to explicitly pass all arguments in.

### **Passing functions as arguments to other functions**
Functions used as arguments to another function are sometimes called **callback functions**. They are very useful for letting the caller reuse and modify code. Here's a full example of a `comparisonFcn` function pointer passed in as an argument to the `selectionSort()` function then called to make the key sorting comparison:
```cpp
#include <utility> // for std::swap
#include <iostream>
 
// Note our user-defined comparison is the third parameter
void selectionSort(int *array, int size, bool (*comparisonFcn)(int, int))
{
    // Step through each element of the array
    for (int startIndex{ 0 }; startIndex < (size - 1); ++startIndex)
    {
        // bestIndex is the index of the smallest/largest element we've encountered so far.
        int bestIndex{ startIndex };
 
        // Look for smallest/largest element remaining in the array (starting at startIndex+1)
        for (int currentIndex{ startIndex + 1 }; currentIndex < size; ++currentIndex)
        {
            // If the current element is smaller/larger than our previously found smallest
            if (comparisonFcn(array[bestIndex], array[currentIndex])) // COMPARISON DONE HERE
            {
                // This is the new smallest/largest number for this iteration
                bestIndex = currentIndex;
            }
        }
 
        // Swap our start element with our smallest/largest element
        std::swap(array[startIndex], array[bestIndex]);
    }
}
 
// Here is a comparison function that sorts in ascending order
// (Note: it's exactly the same as the previous ascending() function)
bool ascending(int x, int y)
{
    return x > y; // swap if the first element is greater than the second
}
 
// Here is a comparison function that sorts in descending order
bool descending(int x, int y)
{
    return x < y; // swap if the second element is greater than the first
}
 
// This function prints out the values in the array
void printArray(int *array, int size)
{
    for (int index{ 0 }; index < size; ++index)
    {
        std::cout << array[index] << ' ';
    }
    
    std::cout << '\n';
}
 
int main()
{
    int array[9]{ 3, 7, 9, 5, 6, 1, 8, 2, 4 };
 
    // Sort the array in descending order using the descending() function
    selectionSort(array, 9, descending);
    printArray(array, 9);
 
    // Sort the array in ascending order using the ascending() function
    selectionSort(array, 9, ascending);
    printArray(array, 9);
 
    return 0;
}
```
### **Providing default functions**
You can provide a default function as a parameter:
```cpp
void selectionSort(int *array, int size, bool (*comparisonFcn)(int, int) = ascending);
```

### **Making function pointers prettier with type aliases**
We can use type aliases to clean up the syntax of function pointers:
```cpp
using ValidateFunction = bool(*)(int, int);

// cleaner function pointer as a parameter:
bool validate(int x, int y, ValidateFunction pfcn);
// instead of the following:
// bool validate(int x, int y, bool (*fcnPtr)(int, int));
```

### **Using std::function**
`std::function` is a more verbose but more explicit way of defining a function pointer.

```cpp
#include <functional>
bool validate(int x, int y, std::function<bool(int, int)> fcn);
```

The function return type and parameter types are easier to read. The return type goes first, followed by the parameter types in parentheses. 

Here's an example of creating a function pointer that points to the address of `foo`:
```cpp
std::function<int()> fcnPtr{ &foo };
```

You can also type alias std::function:
```cpp
using ValidateFunction = std::function<bool(int, int)>;
```

### **Type inference for function pointers**
You can use the `auto` keyword for function pointers, but it'll hide all of the details of the function's parameter and return types:
```cpp
auto fcnPtr{ &foo };
```

### **Conclusion**
* Function pointers are useful when storing functions in an array (or other structure) or passing functions to other functions
* **Recommendation:** use std::function
* **Recommendation:** when using a function pointer type multiple times, use a type alias to std::function

## [**11.8 - The stack and the heap**](https://www.learncpp.com/cpp-tutorial/the-stack-and-the-heap/)
### **The heap segment**
The **heap segment** (a.k.a. the "free store") keeps track of memory used for dynamic allocation. When using the `new` operator, memory is allocated out of the heap segment.

**Note:** sequential memory requests from the heap may not result in sequential memory addresses being allocated!

Disadvantages of the heap:
* Allocating memory on the heap is comparatively slow.
* Allocated memory stays allocated until it is specifically deallocated (beware memory leaks) or the application ends (the OS should clean it up).
* Dynamically allocated memory must be accessed through a pointer. Dereferencing a pointer is slower than accessing a variable directly.

Advantages of the heap:
* The heap is a big pool of memory, so large arrays, structs, or classes can be stored here.

### **The call stack**
The **call stack** (a.k.a. "the stack") keeps track of all the active functions (those that have been called but not yet terminated) from the start of the program to the current point of execution, and handles allocation of all function parameters and local variables.

### **The stack data structure**
A **data structure** is a programming mechanism for organizing data so that it can be used efficiently.

The stack is a last-in, first-out (LIFO) structure. We can:
1. Look at the top item on the stack (via `top()` or `peek()`)
2. Take the top item off the stack (via `pop()`)
3. Put a new item on top of the stack (via `push()`)

### **The call stack segment** 
The **call stack segment** holds the memory used for the call stack.

The stack has memory addresses, and the items we push and pop off are called **stack frames**.

We keep track of where the top of the call stack currently is with the stack pointer (aka "SP"), which is a register (a small piece of memory in the CPU).

### **Stack overflow**
**Stack overflow** happens when all the memory in the stack has been allocated and further allocations begin overflowing into other sections of memory.

Advantages of the stack:
* Allocating memory is comparatively fast.
* Memory allocated on the stack stays in scope as long as it is on the stack. It is destroyed when it is popped off the stack.
* All memory allocated on the stack is known at compile time, so it can be accessed directly through a variable.

Disadvantages of the stack:
* Because the stack is relatively small, avoid doing anything that eats up a lot of stack space. This includes passing by value or creating local variables or large arrays or other memory-intensive structures.

[This video](https://www.youtube.com/watch?v=wJ1L2nSIV1s&ab_channel=TheCherno) is a good alternate lesson for the stack vs heap.


## [**11.9 - std::vector and stack behavior**](https://www.learncpp.com/cpp-tutorial/stdvector-capacity-and-stack-behavior/)
std::vector:
* can be used as a dynamic array 
* can be dynamically resized as required
* remembers its length

### **Length vs capacity**
**length** is now many elements are being used in the array.

**capacity** is how many elements were allocated in memory.

std::vector keeps track of these two separately. They can be accessed by `array.size()` and `array.capacity()`, respectively.

**Note:** the `resize()` function changes both the length and capacity. Also, the capacity is guaranteed to be at least as large as the array length, but can be larger.

std::vector will reallocate memory if needed, but it would prefer not to because it is computationally expensive. Therefore, we keep length and capacity separate so we don't have to reallocate memory every time we change the length.

### **Stack behavior with std::vector**
We can use std::vector as a stack by using the following three functions:
1. `push_back()` to push an element onto the stack
2. `back()` to return the value of the top element on the stack
3. `pop_back()` to pop an element off the stack

Pushing more elements than currently allowed by the capacity of std::vector will automatically resize the vector. The capacity does not shrink when removing elements. Because resizing arrays/vectors is expensive, we can reserve memory ahead of time with the `reserve` function.
```cpp
std::vector<int> stack{};
stack.reserve(5); // set the capacity to at least 5
```
Vectors may allocate extra capacity for breathing room. If, when, and how much additional memory is allocated is left up to the compiler implementer.

## [**11.10 - Recursion**](https://www.learncpp.com/cpp-tutorial/recursion/)