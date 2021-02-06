# 1.1 - Statements and the structure of a program
## Statements
A computer program is a sequence of instructions, and a statement is a type of instruction that causes the program to *perform some action*.
## Functions
Rule: every C++ program *must* have a main. When the program is run, execution starts with the first statement in the main and continues sequentially (typically terminating with the last statement inside the main).
## Dissecting the Hello World Example
```cpp
#include <iostream>
 
int main()
{
   std::cout << "Hello world!";
   return 0;
}
```
Looking at the hello world example above, we start with the preprocessor directives (#include <iostream>), then go on to the main function declaration and function body.

# 1.2 - Comments
Some general rules:

1. For a library, program, or function, use comments to describe *what* the library, program, or function does.
2. *Within* a library, program, or function use comments to describe *how* the code accomplishes its goal.
3. At the statement level, describe *why* the code is doing something.

      A bad statement describes *what* the code is doing (I am guilty of this). A better one describes *why*.

      Bad comment:
      ```cpp
      // Set sight range to 0
      sight = 0;
      ```
      Good comment:
      ```cpp
      // The player just drank a potion of blindness and can't see anything
      sight = 0;
      ```

**Comment code liberally**.

Different comment options:

Single line
```cpp
std::cout << "Hello world!\n"; // std::cout lives in the iostream library
```
To the right
```cpp
std::cout << "Hello world!\n";         // first comment
std::cout << "Hola mundo!\n";          // another comment
```
Block comment
```cpp
/* Block comment
   continues across
   lines. */
```
Beautified block comment
```cpp
/* A more 
 * "beautiful" version 
 * of the block commment
 * according to some. */  
```

# 1.3 - Introduction to variables
Programs are a collection of instructions that manipulate data to produce a desired result.
## Objects and Variables
In C++, direct memory access is not allowed (i.e. we cannot say *go get the value stored at location 7532*). Instead, an object is defined as a region of storage (usually memory) that has a value. when the object is defined, the compiler automatically determines where the object will be placed in memory. Therefore, we can say *get get the value stored by this object*

Objects can be named or unnamed (anonymous). Named objects are called **variables** and the name of the object is called an **identifier**.

In C++, the term *object* refers to variables and data structures in memory but *not functions*.

## Variable Instantiation
When the program is run (called **runtime**), the variable will be **instantiated** (assigned a memory address). For example, when *x* is instantiated at memloc 140, whenever the program uses the variable *x* it will access the value in memloc 140.

An instantiated object is called an **instance**.

## Data types
In C++, the type of objects must be known at **compile-time** and can't be changed without recompiling the program. 

C++ allows you to create your own user-defined types.

## Summary
In C++, variables are used to access memory. Variables have an identifier, a type, and a value.

# 1.4 - Variable Assignment and initialization
There are three ways to initialize a variable in C++:
```cpp
int width = 5;       // copy initialization of value 5 into variable width
```

```cpp
int width( 5 );      // direct initialization of value 5 into variable width
```

```cpp
int width{ 5 };      // direct list initialization of value 5 into variable width (preferred)
int height = { 6 };  // copy list initialization of value 6 into variable height
```

Initializing a variable with empty braces indicates value initialization, generally initializing the variable to zero (or empty if more appropriate).
```cpp
int width{};         // value initialization to value 0
```

List initialization disallows "narrowing" conversions and will throw an error, whereas copy and direct initialization allow them and will compensate. For example, 
```cpp
int width = 4.5;     // result: width = 4, data lost
int width(4.5);      // result: width = 4, data lost
int width{ 4.5 };    // result: error
```

**Best practice: favor direct list initialization whenever possible.**

**Best practice: initialize your variables upon creation.**

You can do the following, but DON'T DO IT
```cpp
int a = 5, b = 6;
int c(7), d(8);
int e{9}, f{10};
```

This is INCORRECT:
```cpp
int a, b = 5;        //INCORRECT: a is left uninitialized
```

Q: What is the diference between initialization and assignment.
A: Initialization gives a variable an initial value at the time of its creation. Assignment gives a variable a value at some point after its creation.

