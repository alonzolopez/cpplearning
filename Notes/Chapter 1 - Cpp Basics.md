# Summary
See the [summary page](https://www.learncpp.com/cpp-tutorial/chapter-1-summary-and-quiz/) on learncpp.



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

# 1.5 - Introduction to iostream: cout, cin,and endl
The input/output (io) library is part of the C++ standard library. It lets us get input from the keyboard and output data to the console.

To see this code in action, see iotests.cpp in the Chapter 1 projects folder.

## std::cout
Here's an example:
```cpp
#include <iostream>

int main()
{
   int x{ 5 };
   std::cout << x;
   return 0
}
```

If you want to print multiple strings on the same line, use "<<"
```cpp
#include <iostream>

int main()
{
   int x{ 5 };
   std::cout << "x is equal to " << x;
   return 0
}
```

## std::endl

A new line IS NOT automatically inserted between separate output statements. To move the cursor to the next line, use *std::endl*, which stands for "end line". For example,
```cpp
#include <iostream>

int main()
{
   int x{ 5 };
   std::cout << "Hi!" << std::endl;
   std::cout << "My name is Alonzo." << std::endl;
   return 0
}
```

## std::endl vs '\n'
std::endl does two things:
- moves the cursor to the next line
- "flushes" the output (makes it appear on the screen immediately)

The second function, the flush, is a little redundant because std::cout also does this. To get rid of this redundancy, '\n' is preferred. It moves the cursor to the next line but does not flush so it performs better. It's also easier to use and type.
```cpp
#include <iostream>

int main()
{
   int x{ 5 };
   std::cout << "Hi!\nMy name is Alonzo.";
   return 0
}
```

**Best practice: Prefer '\n' over std::endl when outputting text to the console.**

## std::cin
"cin" = character input

This uses the extraction operator (>>) as opposed to the insertion operator (<<).

**Best practice: initialize the variable before re-assigning its value to the user input. It's a little redundant because the user input immediately over-writes any value you assign, but it's in-line with the previous best practice.**

## Summary
- `std::cin` and `std::cout` always go on the left-hand side of the statement
- `std::cout` is used to output a value (cout = character output)
- `std::cin` is used to input a value (cin = character input)
- `<<` is used with std::cout and shows the direction the data is moving - if `std::cout` represents the console, data flows from the variable to the console
- `>>` is used with `std::cin` and shows the direction the data is moving - if `std::cin` represents the keyboard, the input data is moving from the keyboard to the variable

# 1.6 - Uninitialized variables and undefined behavior
## Uninitialized Variables
Unlike other programs, C/C++ does not initialize most variables to a given value (e.g. zero) automatically. Thus, when a variable is assigned a memory location by the compiler, the default value of that variable is whatever value happened to be stored at that memory location previously (garbage).
- Initialization = the object is given a known value at the point of definition
- Assignment = the object is given a known value beyond the point of definition
- Uninitalized = the object has not been given a known value yet

**Best practice: INITIALIZE YOUR VARIABLES!!!**

## Undefined Behavior
Undefined behavior (UB) is the result of executing code whose behavior is not well defined by the C++ language. You never know what you're going to get

# 1.7 - Keywords and naming identifiers
## Identifier naming rules
The name of a variable is called an identifier. The identifier:
- cannot be a keyword
- can only be composed of: letters (lower/upper case), numbers, and the underscore character
- must begin with a letter (lower/upper case) or an underscore; it can't start with a number
- C++ is case senstive, so nvalue is different than nValue

## Identifier Naming Best Practices
Now that we know how *can* name a variable, let's talk about how we *should*.

Some conventions:
* Variable and unction names start with a lowercase letter
   * Identifier names that start with a capital letter are typically used for user-defined types (e.g. structs, classes, and enumerations but NOT int)
   * If the variable or function name is multi-word, there are two common conventions
      - Words separated by underscores, called snake_case
         ```cpp
         int my_variable_name;
         int my_function_name();
         ```
      - Intercapped words, called camelCase
         ```cpp
         int myVariableName;
         int myFunctionName();
         ```
* Avoid naming identifiers starting with an underscore, as these names are typically reserved for OS, library, and/or compiler use
* Identifiers should make clear what the value they are holding means
   * Balance descriptive names with readability by giving an identifier a name length roughly proportional to how widely it's used (i.e. don't give a variable used once a really long name)
* Avoid abbreviations whenever possible. Time saved writing code is lost reading it, and code is read much more than it is written. Emphasize readability.
* A clarifying comment can go a long way, especially to reduce the length of identifiers

**Best practice: When working in an existing program, use the conventions of the program even if they don't conform to modern best practices. Otherwise, use modern best practices.**

# 1.8 - Whitespace and basic formatting
C++ is white-space independent.

Recommendations for basic formatting:
1. Use tabs or white spaces - your preference. Set your tabs to 4 spaces worth of indentation.
2. There are two acceptable styles for function braces:
   1. Google's C++ style guide recommends putting the curly brace on the same line as the statement
      ```cpp
      int main() {

      }
      ```
   2. Others (including myself) prefer putting the curly brace on its own line and matching with the end brace:
      ```cpp
      int main()
      {
      }
      ``` 
3. Each statement within curly braces should start one tab in from the opening brace of the function it belongs to.
4. **Best practice:** lines should be 80 characters max. Split and indent everything after the first line if you have to.
5. If a long line is split at an operator, the operator should be placed at the beginning of the next line, not the end of the current line.
6. Use whitespace to make your code easier to read by aligning values or comments.

**Best practice: Use the automatic formatting feature in your IDE to keep your code's formatting style consistent.**

# 1.9 - Introduction to Literals and Operators
## Literals
*"Hello world!"* and *5* are literals (a.k.a. literal constants), fixed values inserted into the source code. Literals have both a value and a type.

## Operators
The contruct called the operator denotes the specific operation to be performed. It is common nomenclature to append the operator's symbol to the end of the word operator. For example, for the plus operator we write operator+.

The number of operands that an operator takes as input is called the operator's *arity*. Operators in C++ come in three different arities:
* **Unary** operators act on one operand. For example, *operator-* takes literal operand *5* and flips its sign to produce the new output value *-5*.
* **Binary** operators act on two operands (known as left and right). For example, *operator+* takes the left operand (3) and the right operand (4) and produces output *7*.
* **Ternary** operators act on three operands. There is only one ternary operand. It will be discussed later.

# 1.10 - Introduction to Expressions
An expression is a combination of literals, variables, operators, and explicit function calls that produce a single output value, the result of the expression.

**Rule: values calculated in an expression are discarded at the end of the expression.**

Statement != expression. A statement is used when we want the program to perform an action. Expressions are used when we want the program to calculate a value. 
- Expressions must be part of a statement
- Expression statements are statements that consist of an expression followed by a semicolon.
   ```cpp
   x = 5;          // an expression statement
   2 * 3;          // an expression statement that evaluates to 6 then discards the value 6
   std::cout << x; // an expression statement
   ```

# 1.11 - Developing Your First Program
"You have to write a program once to know how you should have written it the first time."

The primary goal is to get a working, accurate program.

