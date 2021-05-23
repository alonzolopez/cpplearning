# [9.1 - Arrays (Part I)](https://www.learncpp.com/cpp-tutorial/arrays-part-i/)
An **array** is an aggregate data type that lets us access many variables of the same type through a single identifier.

To declare a fixed length array of size 30:
```cpp
int testScore[30]{};
```

## Array elements and subscripting
Arrays are zero-indexed.

For some examples of array declaration, assignment, and initialization, see [main.cpp](../9-projects/9-1-1/main.cpp)

Array subscripts must always be an integral type. They can be a literal value, a variable (constant or non-constant), or an expression that evaluates to an integral type.

## Fixed array declarations
When declaring a fixed array, the length of the array must be a *compile-time* constant. **Note:** `constexpr` is a compile-time constant but not `const`.

Here are a few ways that are okay to declare fixed arrays:
```cpp
// using a literal constant
int numberofLessonsPerDay[7]{};

// using a constexpr symbolic constant
constexpr int daysPerWeek{ 7 };
int numberofLessonsPerDay[daysPerWeek]{};

// using an enumerator
enum Weekday
{
    monday,
    tuesday,
    wednesday,
    thursday,
    friday,
    saturday,
    sunday,
    maxWeekday
}
int numberOfLessonsPerDay[maxWeekday]{};
```

Some ways that are not recommended (macros) or don't work because they're not using compile-time constants:
```cpp
// using a non-const variable
int daysPerWeek{};
std::cin >> daysPerWeek;
int numberOfLessonsPerDay[daysPerWeek]{}; // Not ok -- daysPerWeek is not a compile-time constant!
 
// using a runtime const variable
int temp{ 5 };
const int daysPerWeek{ temp }; // the value of daysPerWeek isn't known until runtime, so this is a runtime constant, not a compile-time constant!
int numberOfLessonsPerDay[daysPerWeek]{}; // Not ok
```

## A note on dynamic arrays
Fixed arrays cannot have a length based on runtime calculations, and their length cannot be changed. For dynamic sizing, see dynamic arrays.

# [9.2 - Arrays (Part II)](https://www.learncpp.com/cpp-tutorial/arrays-part-ii/)
## Initializing fixed arrays
Use an **initializer list** to initialize arrays:
```cpp
// initializer list
int primes[5]{ 2, 3, 5, 7, 11 };
```

If there are less initializers than the array can hold, **zero initialization** occurs where the missing elements are initialized to zero.
```cpp
// the last two elements are not specified so initialized to zero
int array[5]{ 7, 4, 5}; 
int arr[5]{}; // initialize all elements to zero
std::string sarr[5]{}; // initialize with empty strings
```

If the initializer list is omitted, the elements are uninitialized unless they are a class-type
```cpp
int array[5]; // uninitialized
std::string array[5]; // initialize to empty strings
```
**Best practice:** explicitly initialize arrays, even if they would be initialized without an initializer list.

## Omitted length
You can let the compiler figure out the length of the array based on the elements passed in via list initialization
```cpp
int array[]{0, 1, 2, 3, 4};
```

## Arrays and enums
Array indices are hard to follow as a human reader. To improve code readability, consider using enumerations. See [main.cpp](../9-projects/9-2-1/main.cpp) for an example.

## Arrays and enum classes
Enum classes don't have an implicit conversion to integer, so you have to use static_cast to convert the enumerator to an integer:
```cpp
#include <iostream>

enum class StudentNames
{
    kenny,
    kyle,
    stan,
    butters,
    cartman,
    wendy,
    max_students
};

int main()
{
    int testScores[static_cast<int>(StudentNames::max_students)]{};
    testScores[StudentNames::stan] = 76;
}
```
Or you could just use the normal `enum` inside a namespace like in [main.cpp](../9-projects/9-2-1/main.cpp).

## Passing arrays to functions
When normal variables are passed into a function, C++ *copies* the value of the argument into the function's parameter variable. Therefore, modifying the value of the variable in the function does not affect the original argument.

However with arrays, C++ *does not copy* an array when passing it into a function; the *actual array* is passed in. That means if the function modifies the array, it modifies the original argument. For example:
```cpp
void passArray(int prime[5]) // prime is the actual array
{
    prime[0] = 11; // so changing it here will change the original argument!
    prime[1] = 7;
    prime[2] = 5;
    prime[3] = 3;
    prime[4] = 2;
}
```

If you want to make sure the function does not modify the original array, make the array const:
```cpp
void passArray(const int prime[5]) // prime is the actual array
{
    // code that uses the prime array but cannot modify it
}
```

## Determining the length of an array
If you're using C++17 or later, use `std::size`.

If you're using a C++ version before C++17, use `sizeof()`. This returns the total size of the array (i.e. the array length multiplied by the element size).

```cpp
#include <iostream>

int main()
{
    int array[]{ 1, 2, 3, 4, 5};
    std::cout << "The length of the array is: " << sizeof(array) / sizeof(array[0]);

    return 0;
}
```

Note that neither `sizeof()` nor `std::size()` work on arrays passed into functions.  

Also, `std::size()` returns an unsigned integer. If you want a signed integer returned, use `std::ssize()` (signed size).

*How do we get the size of an array within a function??*

## Indexing an array out of range
Indexing an array out of range leads to undefined behavior (either using negative indices or indices >= N). The compiler does not do range checking, so your program will be accessing the memory at where that array element would've been had it been a valid index. Therefore, you may be modifying another variable.

**Rule:** make sure your indices are valid for the range of your array.

See [quiz 1](../9-projects/9-2-quiz-1/main.cpp) and [quiz 2](../9-projects/9-2-quiz-2/main.cpp) for functional examples of arrays.

# [9.3 - Arrays and loops](https://www.learncpp.com/cpp-tutorial/arrays-and-loops/)