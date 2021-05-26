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
We can use a loop to iterate through an array.

Be careful with off-by-one errors when iterating through arrays.

Here's an example of iterating through an array with a for loop:
```cpp
int scores[]{ 84, 92, 76, 81, 56 };
// int numStudents{ std::size(scores) }; // C++17 or newer
const int numStudents{ sizeof(scores) / sizeof(scores[0])};

int totalScore{ 0 };

for (int student{ 0 }; student < numStudents; ++student)
{
    totalScore += scores[student];
}

auto averageScore{ static_cast<double>(totalScore) / numStudents};
```

For another example, see [question 1](../9-projects/9-3-quiz-1/main.cpp) and [question 2](../9-projects/9-3-quiz-2/main.cpp) and [question 3](../9-projects/9-3-quiz-3/main.cpp).

# [9.4 - Sorting an array using selection sort](https://www.learncpp.com/cpp-tutorial/sorting-an-array-using-selection-sort/)
You can use `std::swap()` to swap two elements:
```cpp
#include <iostream>
#include <utility>

int main()
{
    int x{ 2 };
    int y{ 4 };
    std::cout << "Before swap: x = " << x << ", y = " << y << '\n';
    std::swap(x, y);
    std::cout << "After swap:  x = " << x << ", y = " << y << '\n';
    return 0;
}
```

The section proceeds to provide an example implementation of the sorting algorithm in C++ code, and see my modified implementation to sort in descending order [here](../9-projects/9-4-quiz-2/main.cpp), but you can also use `std::sort()` for this.

## std::sort
```cpp
#include <algorithm> // for std::sort
#include <iostream>
#include <iterator> // for std::size
 
int main()
{
	int array[]{ 30, 50, 20, 10, 40 };
 
    // sort the array
	std::sort(std::begin(array), std::end(array));
 
    // print the array
	for (int i{ 0 }; i < static_cast<int>(std::size(array)); ++i)
		std::cout << array[i] << ' ';
 
	std::cout << '\n';
    
    return 0;
}	
```
std::sort will come up again in a future lesson.

For an example of bubble sort, see [here](../9-projects/9-4-quiz-3/main.cpp)

# [9.5 - Multidimensional Arrays](https://www.learncpp.com/cpp-tutorial/multidimensional-arrays/)
Declare a multidimensional array:
```cpp
int array[3][5];
```
This creates a multidim array in **row-major** order as follows:
```
[0][0]  [0][1]  [0][2]  [0][3]  [0][4] // row 0
[1][0]  [1][1]  [1][2]  [1][3]  [1][4] // row 1
[2][0]  [2][1]  [2][2]  [2][3]  [2][4] // row 2
```
## Initializing two-dimensional arrays
```cpp
int array[3][5]
{
    { 1, 2, 3, 4, 5 },
    { 6, 7, 8, 9, 10},
    { 11, 12, 13, 14, 15}
};
```
You can also take advantage of automatic zero initialization of individual arrays within the larger multi-dim array like so:
```cpp
int array[3][5]
{
    { 1, 2}, // last three elements zero-initialized
    { 6, 7, 8}, // last two elements zero-initialized
    { 11, 12, 13, 14} // last element zero-initialized
};
```
You can let the compiler figure out ONLY the leftmost length specification, but not for both
```cpp
int array[][5]
{
    { 1, 2, 3, 4, 5 },
    { 6, 7, 8, 9, 10},
    { 11, 12, 13, 14, 15}
};
```
You can zero-initialize the whole thing with:
```cpp
int array[3][5]{};
```

## Accessing elements in a 2D array
Use a double for loop or *for-each* loop to do this.

## Multidimensional arrays larger than two dimensions
Arrays can be larger than 2D. 

Declaring a 3D array:
```cpp
int array[3][4][5];
```
You usually zero-initialize them and explicitly assign values using nested loops or functions.

Access values the same way:
```cpp
std::cout << array[2][1][2];
```

# [9.6 - C-style strings](https://www.learncpp.com/cpp-tutorial/c-style-strings/)
C-style strings are char arrays. They follow all the same rules as arrays (because they are arrays). 
```cpp
char myString[]{"string"};
```
Note that C++ automatically appends the null terminator to the end of the string for us ('\0' or ASCII code 0).

`std::cout` will print the string's elements until it hits the null terminator. If that element is altered or omitted, std::cout will print garbage until it sees a null terminator.

The section goes over useful copy, manipulation, and other functions for C-style strings, but it's recommended to not use C-style strings in the first place. 

**Rule:** use `std::string` or `std::string_view` instead of C-style strings.

# [9.7 - An introduction to std::string_view](https://www.learncpp.com/cpp-tutorial/an-introduction-to-stdstring_view/)
**Best practice:** Use `std::string_view` instead of C-style strings. 

**Best practice:** prefer `std::string_view` over `std::string` for read-only strings, unless you already have a `std::string`.

std::string_view comes with a lot of the useful functions that std::string does too (length, find, indexing, etc))

## View modification functions
You can change how much of the string is viewable using `remove_prefix()` and `remove_suffix()` but you can't undo this.

## Ownership issues
**Warning:** make sure that the underlying string viewed with a std::string_vew does not go out of scope and isn't modified while using the std:string_view. Modifying a std::string can cause its internal string to die and be replaced with a new one in a different place.

## Converting a std::string_view to a std::string
You can do this via initialization of a new std::string using the std::string_view or via static_cast
```cpp
std::string_view sv{ "ball" };

std::string str{ sv }; // okay
std::cout << static_cast<std::string>(sv); // also okay
```

## Opening the window (kinda) via the data() function
**Warning:** only use std::string_view::data() if the std::string_view's view hasn't been modified and the string being viewed is null-terminated. Using std::string_view::data() of a non-null-terminated string can cause undefined behavior.

## Incomplemete implementation
`std::string_view` is new and not completely implemented.
For example, you can't add std::string with an std::string_view.

# [9.8 - Introduction to pointers](https://www.learncpp.com/cpp-tutorial/introduction-to-pointers/)
A variable is a name for a piece of memory that holds a value. When our program instantiates a variable, a free memory address (from RAM) is automatically assigned to the variable, and any value we assign to the variable is stored in this memory address.

## The address-of operator (&)
The address-of operator (&) allows us to see what *memory address* is assigned to the variable. For example:
```cpp
#include <iostream>

int main()
{
    int x{ 5 };
    std::cout << x << '\n';
    std::cout << &x << '\n';

    return 0;
}
```
output:
```
5
0027FEA0
```

## The indirection operator (*)
The indirection operator (*) (a.k.a. the dereference operator) allows us to access the value at a particular address:
```cpp
#include <iostream>

int main()
{
    int x{ 5 };
    std::cout << x << '\n';
    std::cout << &x << '\n';
    std::cout << *(&x) << '\n';

    return 0;
}
```
output:
```
5
0027FEA0
5
```

## Pointers
A **pointer** is a variable that holds a *memory address* as its value.

## Declaring a pointer
Pointer variables are declared like normal variables but with an asterisk between the data type and the variable name.
**Best practice:** when declaring a pointer variable, put the asterisk next to the type to make it easier to distinguish from indirection:
```cpp
int* iPtr{};
```

Avoid other sntaxes or invalid syntax.

## Assigning a value to a pointer
To get the address of a variable, we use the address-of operator:
```cpp
int v{ 5 };
int* ptr{ &v }; // initialize the ptr with address of variable v
```
So the following
```cpp
#include <iostream>
 
int main()
{
    int v{ 5 };
    int* ptr{ &v }; // initialize ptr with address of variable v
 
    std::cout << &v << '\n'; // print the address of variable v
    std::cout << ptr << '\n'; // print the address that ptr is holding
 
    return 0;
}
```
prints:
```
0012FF7C
0012FF7C
```

Note: the type of the pointer must match the type of the variable being pointed to.

You cannot initialize a pointer with a literal. Both of the following DO NOT work:
```cpp
int* ptr{ 5 };  // ERROR
double* dptr{ 0x0012FF7C }; // ERROR
```

## The address-of operator returns a pointer
NOTE: the address-of operator& returns a pointer containing the address of the operand whose type is derived from the argument (e.g. taking the address of an int will return the address in an int pointer).

## Indirection through pointers
Using the pointer, we can get the value of the variable being pointed to. Indirection through a pointer evaluates to the contents of the address it is pointing to:
```cpp
int value{ 5 };
std::cout << &value;    // prints the address of value
std::cout << value;     // prints the contents of value

int* ptr{ &value };     // initialize pointer
std::cout << ptr;       // prints the address held in ptr
std::cout << *ptr;      // prints the value stored at the address pointed to by the pointer
```
output:
```
0012FF7C
5
0012FF7C
5
```

You can also reassign pointers to another value and assign values to the variable itself:
```cpp
int value1{ 5 };
int value2{ 7 };

int* ptr{};

// ptr points to the address that stores value1
ptr = &value1;
std::cout << *ptr;

// ptr points to the address that stores value2
ptr = &value2;
std::cout << *ptr;

// assign a new value to value2 through the pointer
*ptr = 9;
std::cout << value2;
```

## The size of pointers
A pointer is just a memory address, and the number of bits needed to access a memory address on a given machine is always constant. A 32-bit executable uses 32-bit memory addresses, so a pointer on a 32-bit machine is 32 bits (4 bytes). With a 64-bit executable, a pointer would be 64 bits (8 bytes). This is true regardless of the object being pointed to.

## Conclusion
Pointers are variables that hold a memory address. The value they are pointing to can be accessed using the indirection operator*. Indirection through a garbage pointer causes undefined behavior.

# [9.9 - Null pointers](https://www.learncpp.com/cpp-tutorial/null-pointers/)
Pointers are not initialized when they are instantiated. Unless a value is assigned, a pointer points to some garbage address by default.

Pointers can point to a null value. A **null value** is a special value that means the pointer is not pointing to anything. A pointer holding a null value is called a **null pointer**.

Assign a pointer to a null value by intializing it or assigning it to 0:
```cpp
float* ptr { 0 };   // ptr is a null pointer

float* ptr2;        // ptr2 is uninitialized
ptr2 = 0;           // ptr2 is now a null pointer
```

Pointers convert to boolean false if they are null and boolean true if they are non-null, so we can test if they are null using a conditional:
```cpp
double* ptr { 0 };

if (ptr)
    std::cout << "ptr is pointing to a double value\n";
else
    std::cout << "ptr is a null pointer\n";
```
**Best practice:** initialize your pointers to a null value if you're not giving them another value.

## Indirection through null pointers
Will likely crash your application because it's trying to access the memory address indicated by a null value.

## The NULL macro
`NULL` is a special preprocessor macro (defined in <cstddef>) that is commonly used to indicate a null pointer. 

**Best practice:** because NULL is a preprocessor macro with an implementation defined value, avoid using NULL.

## The perils of using 0 (or NULL) for null pointers
`0` isn't a pointer type, so assigning 0 (or NULL) to a pointer is inconsistent and the compiler may have trouble differentiating between the two types.

## nullptr in C++11
**Best practice:** use `nullptr` to initialize your pointers to a null value. `nullptr` is a keyword, and C++ will implicitly convert nullptr to any pointer type. You can even pass it into functions expecting a pointer as a parameter.

## std::nullptr_t
`std::nullptr_t` is a type that can only hold one value: `nullptr`. Use this if you want a function to only accept a nullptr value:
```cpp
#include <cstddef>  // for std::nullptr_t
void doSomething(std::nullptr_t ptr)
{
    // ...
}
```

# [9.10 - Pointers and arrays](https://www.learncpp.com/cpp-tutorial/pointers-and-arrays/)
## Array decay
A fixed array will **decay** (a.k.a. be implicitly converted) into a pointer that points to the first element of the array. However, an array and a pointer to the array are NOT identical. For a fixed array of size 5, the array is of type `int[5]` and its value is the array; a pointer to the array would be of type `int*` and its value is the first element of the array .

Because of this, we can use the pointer to get *the first* value of the array, the value at the memory address held by the pointer.

## Differences between pointers and fixed arrays
The pointer and fixed array have different size. 

The pointer and fixed array also return different values when using the address-of operator&:
```cpp
#include <iostream>

int main()
{
    int arr[5] { 5, 4, 3, 2, 1};

    int* ptr { arr };

    std::cout << "The address of the array is " << &arr << '\n';
    std::cout << "The type of the array is " << typeid(arr).name() << '\n';
    std::cout << "The pointer is " << ptr << '\n';
    std::cout << "The type of the pointer is " << typeid(ptr).name() << '\n';

    return 0;
}
```
Outputs:
```
The address of the array is 0x7ffc22518630
The type of the array is A5_i
The pointer is 0x7ffc22518630
The type of the pointer is Pi
```

## Revisiting passing fixed arrays to functions
A fixed array decays into a pointer when passed as an argument into a function. This happens even if the parameter is declared as a fixed array.

Therefore, the following two function declarations are identical:
```cpp
void printSize(int array[]);
void printSize(int* array);
```

**Best practice:** favor the pointer syntax (*) over the array syntax ([]) for array function parameters.

## An intro to pass by address
Using the indirection operator* to modify a the value pointed to by a pointer will modify the *original* value. This is true for arrays and non-array values as well.

## Arrays in structs and classes don't decay
Arrays that are part of structs or classes DO NOT decay when the whole struct or class is passed to a function. This is a useful way to prevent decay if desired.

# [9.11 - Pointer arithmetic and array indexing](https://www.learncpp.com/cpp-tutorial/pointer-arithmetic-and-array-indexing/)
## Pointer arithmetic
C++ allows you to do arithmetic on pointers. `ptr + 1` returns the *memory address of the next object of the type that matches `ptr`*. If ptr is an `int*`, `ptr + 3` returns the memory address of the int  at 3 itnegers after ptr. This increments the memory address of an int (assuming 4 bytes) accordingly:
```cpp
#include <iostream>
 
int main()
{
    int value{ 7 };
    int* ptr{ &value };
 
    std::cout << ptr << '\n';
    std::cout << ptr+1 << '\n';
    std::cout << ptr+2 << '\n';
    std::cout << ptr+3 << '\n';
 
    return 0;
}
```
output:
```
0012FF7C
0012FF80
0012FF84
0012FF88
```
Each increment moves 4 bytes, or one int's space.

## Arrays are laid out sequentially in memory
Arrays are laid out sequentially in memory, so printing the address of each element with the address-of-operator* like so
```cpp
#include <iostream>
 
int main()
{
    int array[]{ 9, 7, 5, 3, 1 };
 
    std::cout << "Element 0 is at address: " << &array[0] << '\n';
    std::cout << "Element 1 is at address: " << &array[1] << '\n';
    std::cout << "Element 2 is at address: " << &array[2] << '\n';
    std::cout << "Element 3 is at address: " << &array[3] << '\n';
 
    return 0;
}
```
will print:
```
Element 0 is at address: 0041FE9C
Element 1 is at address: 0041FEA0
Element 2 is at address: 0041FEA4
Element 3 is at address: 0041FEA8
```
Each address is 4 bytes apart, or the size of an integer (on the author's machine).

## Pointer arithmetic, arrays, and the magic behind indexing
The compiler translates the subscript operator ([]) into pointer addition and indirection. Generalizing, `array[n]` is equivalent to `*(array + n)` where `n` is an integer. 

For example,
```cpp
#include <iostream>

int main()
{
    int array[]{ 9, 7, 6, 5, 3};

    // print the memory address of array element 1
    std::cout << &array[1] << '\n';
    // print the memory address of array pointer + 1
    std::cout << array + 1 << '\n';

    // print the value of array element 1
    std::cout << array[1] << '\n';
    // print the value at the memory address (pointer + 1)
    std::cout << *(array + 1) << '\n';
}
```
outputs:
```
0x7ffd3946ea94
0x7ffd3946ea94
7
7
```

## Using a pointer to iterate through an array
