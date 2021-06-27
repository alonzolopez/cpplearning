# Chapter 8 - Type Conversion and Function Overloading
## [8.1 - Implicity type conversion (coercion)](https://www.learncpp.com/cpp-tutorial/implicit-type-conversion-coercion/)
This section was covered in [6.15](./Chapter_6_Object_Scope_and_Conversions.md)

## [8.9 - Introduction to function overloading](https://www.learncpp.com/cpp-tutorial/introduction-to-function-overloading/)

**Function overloading** is a feature of C++ that allows you to define multiple versions of a function as long as they have different parameters.
```cpp
int add(int x, int y)
{
    return x + y;
}

int add(double x, double y)
{
    return x + y;
}

int add(int x, int y, int z)
{
    return x + y + z;
}
```

The compiler will know which version of the function to call based on the input parameters.

**Overload resolution** is the process the compiler goes through to match the function call to the appropriate overload based on the arguments used in the function call.

### Making it compile
In order for your program to use function overloading, two things have to be true:
1. Each overloaded function has to be differentiated from the others.
2. Each call to an overloaded function has to resolve to an overloaded function.

**Best practice:** use function overloading liberally to make your program simpler.

## [8.10 - Function overload differentiation](https://www.learncpp.com/cpp-tutorial/function-overload-differentiation/)
### How overloaded functions are differentiated
Normal functions are differentiated using:
* number of params
* type of params

Member functions are also differentiated using:
* const or volatile
* ref-qualifiers

### Overloading based on type of parameters
Typedefs are not considered distinct types for the purpose of overloading.

For parameters passed by value, the const qualifier is not considered a differentiater for the purpose of function overloading.

Ellipses parameters are considered to be a unique type of parameter for the purposes of function overloading.

### The return type of a function is not considered for differentiation
For example, 
```cpp
// the following produces a compiler error because the return type
// is not considered for function differentiation
int getRandomValue();
double getRandomValue();
```

## [8.11 - Function overload resolution and abmiguous matches](https://www.learncpp.com/cpp-tutorial/function-overload-resolution-and-ambiguous-matches/)
### The argument matching sequence
1. The compiler tries to find an exact match in two phases:
    1. The compiler looks for an exact match.
    2. The compiler performs trivial conversions (e.g. `int` to `const int`) to create exact matches.
2. The compiler tries to find a match through numeric promotion.
3. The compiler tries to find a match through numeric conversion.
4. The compiler tries to find a match through user-defined conversions.
5. The compiler tries to find a match through ellipsis.
6. If no matches have been found by this point, the compiler issues a compile error that it cannot find a matching function.

### Ambiguous matches
An **ambiguous match** occurs when the compiler finds two or more functions that match in the same step in the matching sequence. When this occurs, the compiler will stop matching and issue a compile error.

### Resolving ambiguous matches
There are three options:
1. Define a new overloaded function that matches the parameters in the function call exactly.
2. Convert the parameters in the function call yourself to match one of the available overloaded functions (e.g. using `static_cast`).
3. If the argument is a literal, use the literal suffix to ensure the literal is interpreted as the correct type (e.g. `print(0u)` for an `unsigned int`).

## [8.12 - Default arguments](https://www.learncpp.com/cpp-tutorial/default-arguments/)
A **default argument** is a default value provided for a function parameter. When a default argument is defined, the caller can optionally pass an argument to the function. For example,
```cpp
void print(int x, int y = 10)
{
    // ...
}

int main()
{
    print(1, 2);
    print(3);
}
```
### Multiple default arguments
**Rule:** default arguments can only be provided for the rightmost parameters.
```cpp
#include <iostream>

void print(int x, int y=20, int z=30)
{
    // ...
}

int main()
{
    print(1, 2, 3);
    print(1, 2);
    print(1);
    print();

    return 0;
}
```

### Default arguments can only be declared once
Once declared, a default argument cannot be redeclared.

**Best practice:** if the function has a forward declaration (especially one in a header file), put the default argument there. Otherwise, put the default argument in the funciton definition. 
foo.h:
```cpp
#ifndef FOO_H
#define FOO_H
void print(int x, int y=4);
#endif
```

main.cpp:
```cpp
#include "foo.h"
#include <iostream>

void print(int x, int y)
{
    std::cout << "x: " << x << '\n';
    std::cout << "y: " << y << '\n';
}

int main()
{
    print(5);
    return 0;
}
```

### Default arguments and function overloading
Function with default arguments may be overloaded, but be careful to avoid ambiguous function calls. Here is an example of overloading a function with a default parameter:
```cpp
void print(std::string string)
{
    //
}

void print(char ch=' ')
{
    // 
}

int main()
{
    print("Hello world\n");
    print('a');
    print();

    return 0;
}
```
And here is an example of an ambiguous function call:
```cpp
void print(int x);
void print(int x, int y=10);
void print(int x, double y=20.5);

// ...

int main()
{
    print(1, 2);
    print(1, 2.5);
    print(1); // ambiguous function call

    return 0;
}
```

## [8.13 - Function Templates](https://www.learncpp.com/cpp-tutorial/function-templates/)
### Introduction to C++ templates
C++ templates let us create overloaded functions that can work with arguments of any type.

A **template** describes what a function or class looks like using one or more placeholder types. This allows reuse and maintenance of only a single template.

**Key insight:** the compiler can use a single template to generate a family of related functions or classes, each using a different set of types.

**Key insight:** templates can work with types that didn't even exist when the template was written. This helps us make code that is both flexible and future-proof.

### Function templates
A **function template** is a function-like definition used to generate multiple overloaded functions, each with a different set of actual types.

When we create a function with our function template, we use placeholder types (a.k.a. **template types**) for any parameter type, return type, or type used in the function body.

Here is the max() function as a template:
```cpp
template <typename T> // this is the template param declaration
T max(T x, T y)
{
    return (x > y) ? x : y;
}
```

**Best practice:** use a single capital letter (starting with T) to name your template types (e.g. T, U, V, etc.).

## [8.14 - Function Template Instantiation](https://www.learncpp.com/cpp-tutorial/function-template-instantiation/)

Function templates aren't actually functions themselves (they don't compile or execute directly); they generate functions that are then compiled and executed.

The process of creating functions from templates is called **function template instantiation** (a.k.a. instantiation). When this is done by a function call, it's known as **implicit instantiation**. An instantiated function is often called a **function instance** or a **template function**.

When instantiating a function, the compiler essentially clones the function template and replaces the template type (T) with the actual type (e.g. int).

Here's an example of how to use function templates with multiple template types:
```cpp
#include <iostream>

template <typename T>
T max(T x, T y)
{
    return (x > y) ? x : y;
}

int main()
{
    std::cout << max<int>(1, 2) << '\n'; // instantiates and calls max<int>(int, int)
    std::cout << max<int>(4, 3);<< '\n'; // uses the prev instantiated max<int>(int, int)
    std::cout << max<double>(1, 2) << '\n'; // instantiates and calls max<double>(double, double); int arguments are implicitly converted to double
    return 0;
}
```

### **Template argument deduction**
We can use **template argument deduction** to have the compiler deduce the actual type based on the arguments in the function call.

You can have the compiler deduce the type by either of the two following syntaxes:
```cpp
std::cout << max<>(1, 2) << '\n';
std::cout << max(1, 2) << '\n';
```

The version with <> limits the compiler to resolving to template function overloads. The version *without* <> (i.e. normal function syntax) allows the compiler to consider non-template function overloads too. For example,
```cpp
#include <iostream>

template <typename T>
T max(T x, T y)
{
    return (x > y) ? x : y;
}

int max(int x, int y)
{
    return (x > y) ? x : y;
}

int main()
{
    std::cout << max<int>(1, 2 ) << '\n'; // select max<int>
    std::cout << max<>(1, 2 ) << '\n'; // deduces max<int>(int, int); non-template fnxns not considered
    std::cout << max(1, 2 ) << '\n'; // calls max(int, int)
}
```

**Best practice:** favor the normal function call syntax when using function templates.

### **Function templates with non-template parameters**
You can mix template types and specified types in the same template function. The specified types can apply to the function parameters or return value. For example,
```cpp
template <typename T>
int someFcn(T x, double y)
{
    return 5;
}

int main()
{
    someFcn(1, 3.4);    // matches someFcn(int, double)
    someFcn(1, 3.4f);   // matches someFcn(int, double); float promoted to double
    someFcn(2.0, 3.4);  // matches someFcn(double, double)
    
    return 0;
}
```

### **Conclusion**
**Best practice:** use function templates to write generic code that can work with a variety of types. 

## [8.15 - Function templates with multiple template types](https://www.learncpp.com/cpp-tutorial/function-templates-with-multiple-template-types/)
The following code won't compile:
```cpp
#include <iostream>

template <typename T>

T max(T x, T y)
{
    return (x > y) ? x : y;
}

int main()
{
    std::cout << max(2, 3.5) << '\n';

    return 0;
}
```

By the function template, the x and y arguments must be of the same type.

The compiler only uses numeric conversion to convert the int to a double when resolving function overloads, not when performing template argument deduction. This is a feature; it allows us to enforce that x and y be the same type. If we want to allow them to be different types, we have some options:
1. Use `static_cast` to convert the arguments to matching types
2. Provide an actual type
3. Use a function templates with multiple template type parameters

### **Use static_cast to convert the arguments to matching types**
The first solution is to resolve this on the caller side by using `static_cast` to match the types in the function call:
```cpp
#include <iostream>

template <typename T>

T max(T x, T y)
{
    return (x > y) ? x : y;
}

int main()
{
    std::cout << max(static_cast<double>(2), 3.5) << '\n';

    return 0;
}
```

### **Provide an actual type**
We can specify an actual type to be used, in this case `double`:
```cpp
#include <iostream>

template <typename T>

T max(T x, T y)
{
    return (x > y) ? x : y;
}

int main()
{
    std::cout << max<double>(2, 3.5) << '\n';

    return 0;
}
```

### **Function templates with multiple template type parameters**
We can rewrite the function template to use multiple types:
```cpp
#include <iostream>

template <typename T, typename U>

auto max(T x, U y)
{
    return (x > y) ? x : y;
}

int main()
{
    std::cout << max(2, 3.5) << '\n';

    return 0;
}
```

Use the auto keyword so the compiler deduces the return type from the return statement and avoids a narrowing conversion (double to int).