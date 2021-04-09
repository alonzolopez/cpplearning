# [4.1 - Introduction to Fundamental Data Types](https://www.learncpp.com/cpp-tutorial/introduction-to-fundamental-data-types/)

## Bits, Bytes, and Memory Addressing
The smallest unit of memory = 1 binary digit (bit)

1 byte = 8 bit

Each byte has a unique memory address (not each bit).

![memory address](images/MemoryAddresses.png)

## Data Types
A **data type** tells the compiler how to interpret the contents of memory (bits) in a meaningful way. The compiler and CPU take care of encoding the value into the appropriate sequence of bits for that data type.

For example, when we declare a variable as an integer, we are telling the compiler "the piece of memory that this variable uses is going to be interpreted as an integer value." So `65` may be converted to the sequence of bits `01000001`, and when evaluated to produce a value it's converted back to `65`.

## Fundamental Data Types
fundamental data types = basic types = primitive types = built-in types

![Fundamental Data Types](images/fundamental_data_types.png)

# [4.2 - Void](https://www.learncpp.com/cpp-tutorial/void/)
**Void** means *no type*.

Void variables cannot be defined with a type of void.

```cpp
void value; // won't work
```

## Functions that do not return a value
Most commonly, *void* is used to indicate that a function does not return a value:
```cpp
void writeValue(int x) // void here means no return value
{
    std::cout << "The value of x is: " << x << '\n';
    // no return statement because this function doesn't return a value
}
```

## Deprecated: Functions that do not take parameters
This is what you'd do in C to indicate that a function doesn't take parameters:
```c
int getValue(void) // void here means no parameters
{
    int x;
    std::cin >> x;
    return x;
}
```
This will compile in C++ (for backwards compatibility reasons), but this use of *void* is considered deprecated in C++. This following code is equivalent and preferred in C++:
```cpp
int getValue() // empty function parameters is an implicit void
{
    int x;
    std::cin >> x;
    return x;
}
```

## Other Uses of Void
There is a third, more advanced use that will be covered later: [9.20 - Void Pointers](https://www.learncpp.com/cpp-tutorial/void-pointers/).


# [4.3 - Object Sizes and the sizeof Operator](https://www.learncpp.com/cpp-tutorial/object-sizes-and-the-sizeof-operator/)
A single object of variable name *x* may occupy multiple consecutive memory addresses depending on its type.

**Key insight:** focus on writing maintainable code, and optimize only when and where the difference will be substantive.

## Fundamental Data Type Sizes
C++ only guarantees that each fundamental data type is a *minimum* size; the actual size of the variables is compiler and/or computer architecture-dependent. 

**Best practice:** for maximum compatibility, don't assume that the variables are longer than the specified minimum size.

## The sizeof operator
The **sizeof** operator is a unary operator that takes either a type or variable and returns its size in bytes. For example,

```cpp
#include <iostream>
 
int main()
{
    std::cout << "bool:\t\t" << sizeof(bool) << " bytes\n";
    std::cout << "char:\t\t" << sizeof(char) << " bytes\n";
    std::cout << "long double:\t" << sizeof(long double) << " bytes\n";
    int x = 3;
    std::cout << "int x:\t\t" << sizeof(x) << " bytes\n";
 
    return 0;
}
```

**As an aside...** CPUs are often optimized to process data of a certain size (e.g. 32 bits), and types that match that size may be processed quicker. On such a machine, a 32-bit *int* could be faster than a 16-bit *short* or an 8-bit *char*.

# [4.4 - Signed Integers](https://www.learncpp.com/cpp-tutorial/signed-integers/)
![int sizes](images/int-sizes.png)

The preferred way to define the four types of signed integers:
```cpp
short s;
int i;
long l;
long long ll;
```

You can also add an optional *int* suffix or *signed* prefix, but this is not best practice because integers are *signed* by default and the *int* suffix is confusing:
```cpp
short int si;
long int li;
long long int lli;

signed short ss;
signed int si;
signed long sl;
signed long long sll;
```

## Signed Integer Ranges
The integers types can hold values within the following ranges
![Signed Int Ranges](images/signed_int_ranges.png)

## Integer Overflow
**Integer overflow** occurs when we try to store a value that is outside the range of the type. 

**Warning:** in the case of signed integers, which bits are lost is not well defined. Thus, signed integer overflow leads to undefined behavior.

## Integer Division
**When dividing with integers, C++ produces an integer result. Any fractional portion is dropped, not rounded!**

```cpp
#include <iostream>

int main()
{
    std::cout << 8 / 5; // = 1

    return 0;
}
```

# [4.5 - Unsigned Integers and Why to Avoid Them](https://www.learncpp.com/cpp-tutorial/unsigned-integers-and-why-to-avoid-them/)
**Unsigned integers** are integers that can hold only non-negative whole numbers.

## Defining Unsigned Integers
To define an unsigned integer, use the *unsigned* keyword:
```cpp
unsigned short us;
unsigned int ui;
unsigned long ul;
unsigned long long ull;
```

## Unsigned Integer Range
![unsigned int range](images/unsigned-int-range.png)

## Unsigned Integer Overflow
Unsigned integer overflow wraps around the values. For example, for a 1 byte unsigned int, the number 255 is held as is, the number 256 wraps back around and is stored as 0, 257 is stored as 1, 280 is stored as 24, and so on.

Negative numbers wrap back around, so -1 wraps to 255, -2 to 254, and so on. This is true for the others sizes/types.

## Warning
Avoid using unsigned numbers except in some cases or when unavoidable. It can lead to undefined behavior, or be confusing when mixing signed and unsigned integers in math (all integers are automatically treated as unsigned integers when mixed in mathematical expressions, so mix them carefully or not at all). 

Sometimes you still need unsigned numbers, and it's more common in embedded systems (e.g. Arduinos).

# [Fixed-width Integers and size_t](https://www.learncpp.com/cpp-tutorial/fixed-width-integers-and-size-t/)
C++ only guarantees that integers have a minimum size, meaning that ranges are not fixed. The rationale for this goes back to C - computers were slow and perormance was of utmost concern, so it was left to compiler implementors to pick the best size for each type on the target computer architecture. But this sucks by modern standards.

To help with cross-compatibility and headaches, C99 defined a set of **fixed-width integers** that are guaranteed to have the same size on any architecture:

![fixed-width-ints](images/fixed-width-ints.png)

These can be accessed by including the *cstdint* header, where they are defined in the *std* namespace. For example,

```cpp
#include <cstdint>
#include <iostream>

int main()
{
    std::int16_t i{5};
    std::cout << i;
    return 0;
}
```

**Warning:** these too should be avoided for reasons of performance and wide compatibility. Also because std::int8_t and std::uint8_t are often treated and behave like chars.

## Fast and Least Integers
The fast type (std::int_fast#_t) provides the fastest signed integer type with a width of at least # bits.

The least type (std::int_least#_t) provides the smallest signed integer type with a width of at least # bits.

`# = 8, 16, 32, 64`

**Best practice:** use the std::fast#_t and std::int_least#_t when you need an integer guaranteed to be at least a certain minimum size.

## Integer Best Practices
- *int* should be preferred when size doesn't matter (e.g. the number value will always fit within the range of a 2 byte signed integer).
- If you need a variable guaranteed to be a particular size and want to favor performance (no lost data), use std::int_fast#_t
- If you need a variable guaranteed to be a particular size and want to favor memory conservation over performance, use std::int_least#_t. 

Avoid the following when possible:
- Unsigned types
- the 8-bit fixed-width integer types
- Compiler-specific fixed-width integers

## What is std::size_t?
**std::size_t** is defined as an unsigned integral type and is typically used to represent the size or length of objects. It is its own type.

*size_t* is defined to be big enough to hold the size of the largest object creatable on your system (in bytes). For a 32-bit system, that's 4 bytes. For a 64-bit system, that's 8 bytes.

# [4.7 - Introduction to Scientific Notation](https://www.learncpp.com/cpp-tutorial/introduction-to-scientific-notation/)

