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

# 2.7 - [Programs with Multiple Files](https://www.learncpp.com/cpp-tutorial/programs-with-multiple-code-files/)
To build multiple files in VS Code, add the files to tasks.json after the -g flag. For example, to build add.cpp in addition to the active file add it after the -g flag as below
```json
{
	"version": "2.0.0",
	"tasks": [
		{
			"type": "shell",
			"label": "C/C++: g++ build active file",
			"command": "/usr/bin/g++",
			"args": [
				"-g",
				"${file}",
				"${fileDirname}/add.cpp",
				"-o",
				"${fileDirname}/${fileBasenameNoExtension}"
			],
			"options": {
				"cwd": "${workspaceFolder}"
			},
			"problemMatcher": [
				"$gcc"
			],
			"group": {
				"kind": "build",
				"isDefault": true
			}
		}
	]
}
```
The above lets us use the add function from add.cpp in main.cpp.

# 2.8 - [Naming Collisions and an Introduction to Namespaces](https://www.learncpp.com/cpp-tutorial/2-9-naming-collisions-and-an-introduction-to-namespaces/)

Naming collisions often occur in two cases:
1. Two or more definitions for a function (or global variable) are introduced into separate files that are compiled into the same program. This will result in a linker error as shown below.
    a.cpp:
    ```cpp
    #include <iostream>

    void myFcn(int x)
    {
        std::cout << x;
    }
    ```
    main.cpp:
    ```cpp
    #include <iostream>

    void myFcn(int x)
    {
        std::cout << x;
    }

    int main()
    {
        return 0;
    }
    ```
2. Two or more definitions for a function (or global variable) are introduced in the same file (often via an #include). This will result in a compiler error.

## What is a namespace?
A **namespace** is a region that allows you to declare names inside of it for the purpose of disambiguation. The namespace provides a scope (called **namespace scope**) to the names declared inside of it which means that names inside the namespace won't be mistaken for identical names in other scopes.

**Key insight:** a name declared in a namespace won't be mistaken for an identical name declared in another scope.

For example, if you put all your identifiers in a namespace called *math*, then the math functions won't collide with other identically named functions outside the math namespace.

## The Global Namespace
In C++, any name that is not defined inside a class, function, or a namespace is considered to be part of the **global namespace** (a.k.a. **global scope**).

**Key insight:** when you use an identifier that is defined inside a namespace, you have to tell the compiler that the identifier lives inside the namespace.

## Explicit namespace qualifier std::
:: is caled the **scope resolution operator**. The identifier to the left of the :: indicates the namespace that the name to the right of the :: is contained within. If no identifier is provided to the left of ::, the global namespace is assumed.

**Best practice: use explicit namespace prefixes to access identifiers in a namespace.**

## Using namespace std (and why to avoid it)
A **using directive** tells the compiler to check a specified namespace when resolving an identifier without a namespace prefix.

**Warning:** avoid using directives (such as *using namespace std*) at the top of the program. They violate the original intention of namespaces: to avoid naming conflicts in current and future code by adding the namespace.

# 2.9 - [Introduction to the Preprocessor](https://www.learncpp.com/cpp-tutorial/introduction-to-the-preprocessor/)
## Translation and the Preprocessor
Prior to compilation, the code file goes through a phase called **translation**. A code file with translations applied to it is called a **translation unit**. The preprocessor is one sub-phase in the translation phase. 

The **preprocessor** manipulates the text in each code file. **Preprocessor directives** (a.k.a. directives) are instructions that start with a *#* symbol and end with a newline (NOT a semicolon). The preprocessor does not understand C++ syntax -- directives have their own syntax.

## Includes
When the preprocessor sees the *#include* directive, it replaces it with the contents of the included file.

For example, 
```cpp
#include <iostream>
```
replaces *#include* with the contents of the file named "iostream".

## Macro Defines
The *#define* directive is a **macro** that defines how input text is converted to output text in the preprocessor. There are two basic types of macros: *object-like macros* and *function-like macros*. Don't use function-like macros because they're considered dangerous and their purpose can be replicated simply with a normal function.

Within the category of object-like macros, there are two types: those with substitution text and those without.
```cpp
#define identifier
#define identifier substitution_text
```

### Object-like macros with substitution text
Note: this feature was once useful as a cheaper alternative to constant variables, but compilers are better now and the language has grown. **Avoid using object-like macros with substitution text in new code!!!** They should only be seen in legacy code. 

In this macro, the identifier should be in all caps with underscores used to represent spaces.

What do they do? Replace any occurence of the identifier with the substitution text. For example,
```cpp
#include <iostream>

#define MY_NAME "Alex"

int main()
{
    std::cout <<"My name is: " << MY_NAME;

    return 0;
}
```
And the preprocessor converts the above into the below:
```cpp
int main()
{
    std::cout <<"My name is: " << "Alex";

    return 0;
}
```

### Object-like macros without substitution text
These macros replace the identifier with NOTHING! For example,
```cpp
#define USE_YEN
```
These are acceptable to use, and though they seem useless, they're not. More on their uses in future lessons.

## Conditional Compilation
The ```#ifdef``` preprocessor directive allows the preprocessor whether the identifier has been ```#define```d. If yes, then the code between the ```#ifdef``` and matching ```#endif``` is compiled. If not, the code is ignored. The opposite of ```#ifdef``` is ```#ifndef```. Alternatively, you might see ```#if defined(IDENTIFIER)``` or ```#if !defined(IDENTIFIER)```. 
For example,
```cpp
#include <iostream>

#define PRINT_JOE

int main()
{
#ifdef PRINT_JOE
    std::cout << "Joe\n";
#endif

#ifdef PRINT_BOB
    std::cout << "Bob\n";
#endif

#ifndef PRINT_SALLY
    std::cout << "Not Sally\n";
#endif

    return 0;
}
```
The following lines will be compiled in the above
```cpp
#include <iostream>

int main()
{
    std::cout << "Joe\n";
    std::cout << "Not Sally\n";

    return 0;
}
```

## #if 0
This is a convenient way to "comment out" code across multiple lines. For example,

```cpp
#include <iostream>

int main()
{
    std::cout << "Joe\n";

#if 0
    std::cout << "Bob\n";
    std::cout << "Steve\n";
#endif

    return 0;
}
```

## Object-like macros don't affect other preprocessor directives
Macros only substitute text in normal code. Other preprocessor directives are ignored. For example, in the below code
```cpp
#define PRINT_JOE
#ifdef PRINT_JOE
//...
```
The second ```PRINT_JOE``` is not replaced with nothing.

The preprocessor output contains no directives at all -- they are resolved and stripped out before compilation. The compiler won't know what to do with them.

## The Scope of Defines
Preprocessor directives are only valid from the point of definition to the end of the file in which they are defined. The preprocessor doesn't understand concepts like functions, so the scope is not limited to the function if defined within a function. For example below,
```cpp
#include <iostream>

void foo()
{
#define MY_NAME "Alonzo"
}

int main()
{
    std::cout << "My name is: "<< MY_NAME;

    return 0;
}
```
behaves just like 
```cpp
#include <iostream>
#define MY_NAME "Alonzo"

void foo()
{
// ...
}

int main()
{
    std::cout << "My name is: "<< MY_NAME;

    return 0;
}
```

Additionally, directives defined in one code file do not have impact on other code files.

# 2.10 - [Header Files](https://www.learncpp.com/cpp-tutorial/header-files/)
The primary purpose of a header file is to propagate declarations to code files. This is more convenient than tediously forward declaring everything that you want to use that is defined in a different file.

**Key insight:** header files allow us to put declarations in one location and then import them wherever we need them. This saves us a lot of typing.

**Key insight:** when you ```#include``` a file, the content of the included file is inserted at the point of inclusion. This provides a useful way to pull in declarations from another file.

**Best practice:** header files should generally not contain function or variable definitions, only declarations (so as not to violate the one definition rule). An exception is made for symbolic constants.

**Best practice:** use a .h suffix when naming your header files. If a header file is paired with a code file (e.g. add.h and add.cpp), they should both have the same base name (add).

**Best practice:** when writing a source file, include the corresponding header (if one exists), even if you don't need it yet. If the header includes other library headers for function declarations, you probably need it for source files too.

## Troubleshooting
If you get a compiler error, check that the name and directory of the header is right. 

If you get a linker error, make sure that you've added the .cpp file to your project so all function definitions are included in your program.

## Angled Brackets vs Double Quotes
