# [8.1 - Using a language reference](https://www.learncpp.com/cpp-tutorial/using-a-language-reference/)

See [cppreference](https://en.cppreference.com/w/) for the unofficial language reference.

# [8.2 - Enumerated types](https://www.learncpp.com/cpp-tutorial/enumerated-types/)
An **enumerated type** (a.k.a. enumeration or **enum**) is a data type where every possible value is defined as a symbolic constant (called an **enumerator**).

## Enumerator scope
Enumerators (the elements of the enumeration) are placed in the same namespace as the enumeration. Therefore, an enumerator name can't be used in multiple enumerations in the same namespace.

You can get around this by prefixing enumerators with a standard prefix corresponding to the enumeration (e.g. `animal_` or `color_`).

## Enumerator values
Each enumerator is automatically assigned an integer value based on its position in the enumerated list. By default, the first enumerator is assigned the integer value 0, and each subsequent enumerator has a value one greater than its predecessor. However, you can explicitly define the value of an enumerator. Subsequent values still follow the ++ pattern.

```cpp
enum Animal
{
    animal_cat,         // assigned 0
    animal_dog,         // assigned 1
    animal_pig = -3,
    animal_horse,       // assigned -2
    animal_giraffe = 5,
    animal_chicken      // assigned 6
};
```

**Best practice:** don't assign specific values to your enumerators, and don't assign the same value to two enumerators in the same enumeration unless you have a very good reason.

## Enum type evaluation and input/output
Because enumerated values evaluate to integers, they can be assigned to integer variables:
```cpp
int mypet{ animal_pig };
std::cout << animal_horse;  // prints -2
```

However, it doesn't go the other way: the compiler will not implicitly convert an into to an enumerator (unless you use a static_cast)
```cpp
Animal animal{ 5 }; // COMPILER ERROR
auto color{ static_cast<Color>(5) }; // works but ugly
```

You can use a different integer type for enumerators:
```cpp
enum Color : std::uint_least8_t
{
    color_black,
    color_red,
    // ...
};
```

You need to specify the enum base when forward declaring:
```cpp
enum Color : int;   // okay
enum Color;         // ERROR
```

## Printing enumerators
Printing an enumerator via `std::cout` prints the integer value. If you want to print the enumerator identifier itself, you'll need to use a function like a switch to match the int to the identifier's text.

## What are enumerators useful for?
Enumerated types are incredibly useful for code documentation and readability when representing a predefined set of states.

For a code readability example:
```cpp
enum ParseResult
{
    // We don't need specific values for our enumerators.
    success,
    error_opening_file,
    error_reading_file,
    error_parsing_file
};
 
ParseResult readFileContents()
{
    if (!openFile())
        return error_opening_file;
    if (!readFile())
        return error_reading_file;
    if (!parsefile())
        return error_parsing_file;
 
    return success;
}
```

For an example of defining related identifiers, see [main.cpp](../8-projects/8-2/main.cpp).

# [8.3 - Enum Classes](https://www.learncpp.com/cpp-tutorial/enum-classes/)
To make enumerated types more type safe, use **enum class** (a.k.a. **scoped enumeration**). 

With enum classes, strong scoping rules are enforced so that all enumerators are considers part of the enumeration (and put in their namespace, e.g. Color::red). This means you don't have to prefix. This also means that they're considered unique types, so the compiler will throw an error when you try to compare two different enumerators from two different enumerations (e.g. `Color::red == Animal::pig`).

With enum classes, the compiler will not implicitly convert enumerator values to integers, but you can do so via static_cast.

Here's an example of an enum class:
```cpp
enum class Color
{
    red,
    blue
};

int main()
{
    Color color{ Color::red };
    if (color == Color::red)
    {
        std::cout << "red\n";
    }
    else
    {
        std::cout << "blue\n";
    }
    std::cout << static_cast<int>(color);
}
```

# [8.4 - Structs](https://www.learncpp.com/cpp-tutorial/structs/)
An **aggregate data type** is a data type that groups multiple invididual variables together. A **struct** (short for structure) allows us to group variables of mixed data types together into a single unit.

Structs are *very* important to understanding C++ and OOP.

## Declaring and defining structs
```cpp
struct Employee
{
    int id{};       // initialized with junk
    int age{};
    double wage{};
};

int main()
{
    Employee joe{};
    Employee frank{};

    return 0;
}
```

## Accessing struct members
```cpp
Employee joe{};
joe.id = 42;
joe.age = 39;
joe.wage = 24.15;

joe.wage += 2.0;
```

## Initializing structs
Rather than initialize each element individually, use list initialization
```cpp
Employee joe{42, 39, 24.15};
Employee frank{ 2, 28};     // frank.id = 2; frank .age = 28; frank.wage default initialized to zero
```

## Non-static member initialization
```cpp
struct Rectangle
{
    double length{ 1.0 };
    double width{ 1.0 };
};

int main()
{
    // list initialization below overrides the non-static member initializer default
    Rectangle x{ 2.0, 2.0}; 
}
```

## Assigning to structs
Similarly, you can assign values to all members of an existing struct
```cpp
Employee joe{};

joe = {1, 32, 60000.0};
Employee emma{ joe }; // you can also copy all members from one var to another
```

## Structs and functions
You can pass structs into functions and return them from functions:
```cpp
struct Point3d
{
    double x{};
    double y{};
    double z{};
};

Point3d getZeroPoint()
{
    Point3d temp{ 0.0, 0.0, 0.0};
    return temp;
}

void printPoint(Point3d point)
{
    // code to print this point...
}
```

## Nested structs
Structs can contain other structs:
```cpp
struct Employee
{
    int id{};
    int age{};
    int wage{};
};

struct Company{}
{
    Employee CEO{};
    int numberOfEmployees{};
};
```

And you can use nested initializers for nested structs:
```cpp
Company myCompany{ {1, 42, 60.000}, 5};
```

## Accessing structs across multiple files
To share a struct declaration across files, put it in a header file and `#include` it wherever you want.

To make a struct variable accessible across multiple files, use the extern keyword in the declaration in the header and define the variable in a source file.

# [8.5 - Random Number Generation](https://www.learncpp.com/cpp-tutorial/random-number-generation/)
Use `std::rand()` as follows
```cpp
#include <cstdlib>
#include <ctime>
std::srand(static_cast<unsigned int>(std::time(nullptr)));  // set the seed using the time
std::rand();    // draw a random number
```

`std::rand()` is a poor random number generator. For a better one, see [Mersenne Twister](http://www.math.sci.hiroshima-u.ac.jp/m-mat/MT/emt.html).

## Better random numbers using Mersenne Twister
```cpp
#include <iostream>
#include <random> // for std::mt19937
#include <ctime> // for std::time
 
int main()
{
	// Initialize our mersenne twister with a random seed based on the clock
	std::mt19937 mersenne{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
 
	// Create a reusable random number generator that generates uniform numbers between 1 and 6
	std::uniform_int_distribution die{ 1, 6 };
	// If your compiler doesn't support C++17, use this instead
	// std::uniform_int_distribution<> die{ 1, 6 };
 
	// Print a bunch of random numbers
	for (int count{ 1 }; count <= 48; ++count)
	{
		std::cout << die(mersenne) << '\t'; // generate a roll of the die here
 
		// If we've printed 6 numbers, start a new row
		if (count % 6 == 0)
			std::cout << '\n';
	}
 
	return 0;
}
```