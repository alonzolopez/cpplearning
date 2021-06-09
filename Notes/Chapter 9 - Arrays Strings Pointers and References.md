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
Though it's not common, you can do this
```cpp
int main()
{
    char name[]{ "Mollie" };
    int arrayLength{ static_cast<int>(std::size(name)) };
    int numVowels{ 0 };

    for (char* ptr{ name }; ptr != (name + arrayLength); ++ptr)
    {
        if (isVowel(*ptr))
        {
            ++numVowels;
        }
    }
    std::cout << name << " has " << numVowels << " vowels.\n";
    return 0;
}
```

See [quiz 2](../9-projects/9-11-quiz/main.cpp) for an example of iterating through arrays using pointers to find a value.

# [9.12 - C-style string symbolic constants](https://www.learncpp.com/cpp-tutorial/c-style-string-symbolic-constants/)
You may see C-style strings in old code, but new code should favor `std::string` or `std::string_view`.

# [9.13 - Dynamic memory allocation with new and delete](https://www.learncpp.com/cpp-tutorial/dynamic-memory-allocation-with-new-and-delete/)
**Dynamic memory allocation** is a way for running programs to request memory from the operating system when needed.

## Dynamically allocating single variables
To allocate a *single* variable dynamicaly, we use the scalar (non-array) form of the **new** operator. The new operator requests enough memory for the specified variable (e.g. int) and creates the object using that memory, then returns a pointer containing *the address* of the memory that has been allocated. We can assign that address to our own pointer variable so we can access the allocated memory later:
```cpp
int* ptr{ new int }; // dynamically allocate an int and assign the address to ptr so we can access it later
*ptr = 7; // assign value of 7 to allocated memory
```

## How does dynamic memory allocation work?

Unlike static or automatic memory, the program itself can and is responsible for requesting and disposing of dynamically allocated memory. If the OS can fulfill a dynamic memory allocation request, it will return the address of memory to your application.

## Initializing and deleting dynamically allocated variables
To initialize:
```cpp
int* ptr1{ new int(5) }; // direct initialization
int* ptr2{ new int{ 6 } }; // uniform initialization
```
When we are done with a variable, we need to explicitly delete it using the **delete** operator:
```cpp
delete ptr1; // return the memory pointed to by ptr to the OS
ptr = 0; // set ptr to be a null pointer (use nullptr instead of 0)
```
Deleting the pointer returns the memory back to the OS. It doesn't modify the scope of the pointer, which is why we set it to nullptr after.

## Dangling pointers
A pointer that is pointing to deallocated memory is called a **dangling pointer**. Indirection through or deleting a dangling pointer will lead to undefined behavior. Deallocating memory may also create multiple dangling pointers.

For example,
```cpp
#include <iostream>

int main()
{
    int* ptr{ new int }; // dynamically allocate an int
    *ptr = 7; // assign a value to that memory

    delete ptr; // return the memory to the OS; ptr is now a dangling pointer

    std::cout << *ptr; // indirection through dangling pointer will cause undefined pointer
    delete ptr; // trying to deallocate memory again will lead to undefined behavior
}
```

And for an example of multiple dangling pointers:
```cpp
#include <iostream>

int main()
{
    int* ptr{ new int }; // dynamically allocate an int
    int* otherPtr{ ptr }; // otherPtr is now pointed at the same memory location

    delete ptr; // ptr and otherPtr are now dangling pointers
    ptr = nullptr; // ptr is now a nullptr

    // but otherPtr is still a dangling pointer!!!

    return 0;
}
```

**Best practice:** set deleted pointers to 0 (or nullptr in C++11) unless they are going out of scope immediately afterward.

## Operator new can fail
If the OS cannot grant a memory request, operator new will fail. The default behavior is to throw a `bad_alloc` exception. If this exception isn't properly handled, the program will terminate (crash) with an unhandled exception error.

We can have new return a null pointer if memory can't be allocated by adding `std::nothrow`:
```cpp
int* value = new (std::nothrow) int; // value will be set to a null pointer if the integer allocation fails
```

We should check all memory requests to ensure they succeed before using the allocated memory:
```cpp
int* value{ new (std::nothrow) int{} };
if (!value)
{
    // do error handling here
    std::cout << "Could not allocate memory";
}
```

## Null pointers and dynamic memory allocation
Null pointers are particularly useful when dealing with dynamic memory allocation. In the context of dynamic memory allocation, a nullptr means "no memory has been allocated to this pointer". This means we can conditionally allocate memory:
```cpp
// check that ptr has not been allocated memory; if not, allocate it
if (!ptr)
    ptr = new int;
```

Deleting a null pointer has no effect, so instead of:
```cpp
// the following if statement is unnecessary
if (ptr)
    delete ptr;
```
we can just write:
```cpp
delete ptr;
```

## Memory Leaks
If a program loses the address to the dynamically allocated memory, then the dynamically allocated memory cannot be deleted. This is called a **memory leak**. This can cause your program to eat up a ton of memory unnecessarily and prevent other programs from using it. 

There are a few ways memory leaks can occur:
1. A pointer going out of scope
    ```cpp
    void doSomething()
    {
        int* ptr{ new ptr };
    } // ptr goes out of scope here and the memory address is lost (cannot be deleted now)
    ```
2. Reassigning a pointer holding the address of dynamically allocated memory to another value before deleting the memory and returning it to the OS.
    ```cpp
    int value = 5;
    int* ptr{ new int{} }; // allocate memory
    ptr = &value; // old address lost = memory leak
    ```
    To fix this, delete the pointer before reassigning it:
    ```cpp
    int value = 5;
    int* ptr{ new int{} };  // allocate memory
    delete ptr; // return memory back to OS
    ptr = &value; // reassign pointer to address of value
    ```
3. Double-allocation of a dynamic memory address to a single pointer
    ```cpp
    int* ptr{ new int{} };
    ptr = new int{}; // old address lost = memory leak
    ```
    to avoid this, delete the pointer before the second allocation
    ```cpp
    int* ptr{ new int{} };
    delete ptr;
    ptr = new int{}; // old address lost = memory leak
    ```

## Conclusion
1. Operators `new` and `delete` allow us to dynamically allocate single variables for our programs.
2. Dynamically allocated memory has dynamic duration and will stay allocated until you deallocate it or your program terminates.
3. Be careful not to perform indirection through dangling or null pointers.

# [9.14 - Dynamically allocating arrays](https://www.learncpp.com/cpp-tutorial/dynamically-allocating-arrays/)

We can dynamically allocate an array using `new[]` and `delete[]`. 
```cpp
#include <iostream>
#include <cstddef> // std::size_t

int main()
{
    std::cout << "Enter a positive integer";
    std::size_t length{};
    std::cin >> length;

    int* array{ new int[length]{} }; // use array new; we must use type std::size_t for length

    std::cout << "I just allocated an array of integers length " << length << '\n';

    array[0] = 5; // set element zero to 5

    delete[] array; // use array delete to deallocate array

    // we don't set array to nullptr here because it's going to go out of scope anyways

    return 0;
}
```

If we didn't use `std::size_t` as the type for length but instead int, we could static_cast it:
```cpp
int length{};
std::cin >> length;
int* array{ new int[static_cast<std::size_t>(length)]{} };
```

## Dynamically Deleting Arrays
Use `delete[]` not `delete` when deleting dynamically-allocated arrays. Using `delete` causes undefined behavior.

## Initializing dynamically allocated arrays
To initialize a dynamically-allocated array to zero:
```cpp
int* array{ new int[length]{} };
```

As of C++11, you can initialize dynamic arrays using initializer lists
```cpp
int fixedArray[5] = { 9, 7, 5, 3, 1 };
int* array{ new int[5]{9, 7, 5, 3, 1 } }; // initialize a dynamic array using list initialization

// we can also use the auto keyword to avoid writing the type twice
auto* array{ new int[5]{9, 7, 5, 3, 1 }};
```

For an example, see [main.cpp](../9-projects/9-14-1/main.cpp)

## Resizing arrays
Don't use dynamically-allocated arrays to do this yourself. Use `std::vector` which will be introduced shortly.

## Quiz
The [quiz](../9-projects/9-14-quiz/main.cpp) is a great example of dynamically-allocated arrays based on user input.

# [9.15 - Pointers and const](https://www.learncpp.com/cpp-tutorial/pointers-and-const/)
## Pointer to const value
We can't set a non-const pointer to a const variable. To declare a **pointer to a const value**, use the `const` keyword before the data type:
```cpp
const int value{ 5 };
const int* ptr{ &value }; // pointer to a const value
*ptr = 6; // ERROR, can't change the value of the const variable through indirection
```

A pointer to a constant variable can also point to a non-constant variable:
```cpp
int value{ 5 };
const int* ptr{ &value };
// value cannot be changed through the pointer
value = 6; // value is non-const when accessed through the identifier
```

The pointer to a const value is not const itself, so it can be redirected to point at other values:
```cpp
int value1{ 5 };
const int* ptr{ &value1 }; // point to address of value1

int value2{ 6 };
ptr = &value2; // redirect to point to address of value2
```

## Const pointers
A **const pointer** is a pointer whose value (memory address) cannot be changed after initialization. You can still change the value stored at that memory address through indirection. 

To declare a const pointer, use the const keyword between the asterisk and the pointer name. Like all const variables, the pointer must be initialized to a value upon declaration:
```cpp
int value{ 5 }; // non-const value
int* const ptr{ &value };
*ptr = 6; // okay, can change the value stored because it's non-const

int value2{ 8 };
ptr = &value2; // ERROR, the pointer is const, cant change the address it points to
```

## Const pointer to a const value
To declare a const pointer to a const value (i.e. neither the pointer address nor the value pointed to can be changed), use the const keyword before the type AND after the asterisk.
```cpp
int value{ 5 };
const int* const ptr{ &value };
```

# Recap
Here are four notes:
1. A non-const pointer can be redirected to point to other addresses.
2. A const pointer always points to the same address; this address cannot be changed.
3. A pointer to a non-const value can change the value it is pointing to. These CAN NOT point to a const value.
4. A pointer to a const value treats the value as const (even if it is non-const), and thus cannot change the value.


Pointers to const variables are primarily used in function parameters (e.g. passing arrays in) to help ensure the function doesn't inadvertently modify the parameter.

# [9.16 - Reference Variables](https://www.learncpp.com/cpp-tutorial/references/)
There are three basic variable types:
1. Normal variables which hold values directly
2. Pointers which hold the address of another value (or null) and the value pointed to can be retrieved through indirection
3. **References** that act as an alias to another object or value

There are three types of references:
1. References to non-const values (*references* or *non-const references*)
2. References to const values (const references)
3. r-value references (covered later)

## References to non-const values
A reference to a non-const value (a.k.a. a *reference* for short) is declared using an ampersand between the reference type and the variable name. In this context, ampersand does not mean "address of", it means "reference to".
```cpp
int value{ 5 };
int& ref1{ value }; // best practice syntax with the ampersand next to the type
```

## References as aliases
References generally act as aliases for the values they're referencing. For example,
```cpp
#include <iostream>

int main()
{
    int value{ 5 };
    int& ref{ value };
    int& ref2{ value };

    std::cout << "Value is: " << value << '\n';

    value = 6;

    std::cout << "Value is: " << value << '\n';

    ref = 7;

    std::cout << "Value is: " << value << '\n';

    ref2 = 8;

    std::cout << "Value is: " << value << '\n';

    ++ref;

    std::cout << "Value is: " << value << '\n';

    std::cout << "The address of value is " << &value << '\n';
    std::cout << "The address of ref is " << &ref << '\n'; // the same address as value
    std::cout << "The address of ref2 is " << &ref2 << '\n'; // the same address as value

    return 0;
}
```

which outputs:
```
Value is: 5
Value is: 6
Value is: 7
Value is: 8
Value is: 9
The address of value is 0x7ffc5eb92a34
The address of ref is 0x7ffc5eb92a34
The address of ref2 is 0x7ffc5eb92a34
```

## l-values and r-values
**l-values** are values that have an address in memory. They are the only values that can be on the left-hand-side of an assignment statement.

**r-values** are expressions that are not l-values (do not have an address in memory) (e.g. literals or expresions like `x + 2`).

Note: const variables are considered non-modifiable l-values.

## References must be initialized
References must be initialized when created. There is no such thing as a null reference. References to non-const values can only be initialized with *non-const l-values*. They cannot be initialized with const l-values or r-values.
```cpp
// Good example
int x{ 5 };
int& ref1{ x }; // x is a non-const l-value

// BAD example
const int y{ 7 };
int& ref2{ y }; // not okay, y is a const l-value

// BAD example
int& ref3{ 6 }; // not okay, 6 is an r-value
```

## References cannot be reassigned
```cpp
int value1{ 5 };
int value2{ 6 };

int& ref{ value1 };
ref = value2; // DOES NOT reassign the ref to value2, it assigns the value of value2 to value1 !!!
```

## References as function parameters
References are often used as function parameters. When passing a reference to a variable as a function parameter, no copy is made. This means better performance. 

Similar to pointers references allow the function to directly modify the argument passed in.

**Best practice:** pass arguments by non-const reference (rather than by pointer) when the argument needs to be modified by the function.

Note that the variable passed in does not need to be a reference itself. However, the parameter passed in must be a non-const l-value. This can be restrictive.

```cpp
#include <iostream>

void changeN(int& ref)
{
    ref = 6;
}

int main()
{
    int n{ 5 };

    std::cout << n << '\n';

    changeN(n); // note that n does not need to be a reference

    std::cout << n << '\n';

    return 0;
}
```


## Using references to pass C-style arrays to functions
C-style arrays usually decay to pointers when passed into functions as parameters, but this does not happen when passed by reference. Here's an example:
```cpp
#include <iostream>
#include <iterator>

// NOTE: you need to specify the array size in the function declaration
void printElements(int (&arr)[4])
{
    // we can now get the length of the array since it won't decay to a pointer when passed by ref
    int length{ static_cast<int>(sizeof(arr) / sizeof(arr[0])) };

    for (int i{ 0 }; i < length; ++i)
    {
        std::cout << arr[i] << '\n';
    }
}

int main()
{
    int arr[]{ 99, 20, 14, 80 };

    printElements(arr);

    return 0;
}
```

## References as shortcuts
References can also be used as shortcuts. For example, when accessing a struct member:
```cpp
int& ref{ other.something.value1 };
// the following are equivalent statements
ref = 6;
other.something.value1 = 6;
```

## References vs pointers
References act like pointers that implicitly perform indirection when accessed (this is how most compilers implement references).

```cpp
int value{ 5 };
int* const ptr{ &value }; // const pointer
int& ref{ value };

// the following are equivalent statements
*ptr = 5;
ref = 5;
```

References are generally much safer to use than pointers but limited in functionality.

**Best practice:** if a task can be accomplished by either a reference or pointer, prefer references.

## Summary
* References allow us to define aliases to other objects or values. 
* References to non-const values can only be initialized with non-const l-values. 
* References can not be reassigned once initialized.

References are most often used as function parameters when we either want to modify the value of the argument or avoid making an expensive copy of the argument.

# [9.17 - References and const](https://www.learncpp.com/cpp-tutorial/references-and-const/)
You can declare a reference to a const value similar to how you declare a pointer to a const value:
```cpp
const int value{ 5 };
const int &ref{ value }; // ref to a const value
```
A reference to a const value is called a **const reference** for short, though this nomenclature is DIFFERENT than that of pointers.

## References to r-values extend the lifetime of the referenced value
Normally, r-values have expression scope, meaning they are destroyed at the end of the expression in which they are created. However, when a reference to a const value is initialized with an r-value, the lifetime of the r-value is extended to match the lifetime of the reference.

```cpp
int somefcn()
{
    const int& ref{ 2 + 3 }; // normally the result of 2+3 has expression scope and is destroyed at the end of this statement
    // but because the result is now bound to a reference to a const value...
    std::cout << ref << '\n'; // we can use it here
} // and the lifetime of the r-value is extended to here, when the const reference dies
```

## Const references as function parameters
References used as function parameters can also be const. A few notes:
* the function can access the argument without making a copy of it
* the function is guaranteed to not change the value being referenced
* references to const values allow you to pass in a non-const l-value, a const l-value, a literal r-value, or an expression (r-value). They are *versatile*.

**Best practice:** pass non-pointer, non-fundamental data type variables (e.g. structs) by (const) reference, unless you know that passing it by value is faster (e.g. std::string_view, int, double, etc).

Some examples:
```cpp
#include <iostream>
 
void printIt(const int& x)
{
    std::cout << x;
}
 
int main()
{
    int a{ 1 };
    printIt(a); // non-const l-value
 
    const int b{ 2 };
    printIt(b); // const l-value
 
    printIt(3); // literal r-value
 
    printIt(2+b); // expression r-value
 
    return 0;
}
```

Or from kinova-aero, the write function takes in time and period as references to a const value so it does not modify them:
```cpp
void HardwareInterface::write(const ros::Time& time, const ros::Duration& period){
	position_joint_soft_limits_interface_.enforceLimits(period);
	kinova_driver_->writeJointCommand(joint_positions_command_, gripper_position_command_);
}
```

# [9.18 - Member selection with pointers and references](https://www.learncpp.com/cpp-tutorial/member-selection-with-pointers-and-references/)
To access members through references, use the **member selection operator (.)**.
To access members through pointers, use the **arrow operator (->)**. The arrow operator does the same thing as an indirection followed by the .member selection operator.

For an example of all this:
```cpp
struct Person
{
    int age{};
    double weight{};
};

Person person{};

// member selection using actual struct variable directly
person.age = 5;

// member selection using a reference to the struct
Person& ref{ person };
ref.age = 6;

// member selection using pointer to struct
Person* ptr{ &person };
person->age = 5;
// the below is equivalent to the line above but DO NOT use this
(*ptr).age = 5; // DON'T USE THIS, use -> instead
```

There are cases when `->` and `.` can be mixed:
```cpp
#include <iostream>
#include <string>
 
struct Paw
{
    int claws{};
};
 
struct Animal
{
    std::string name{};
    Paw paw{};
};
 
int main()
{
    Animal puma{ "Puma", { 5 } };
 
    Animal* pointy{ &puma };
 
    // pointy is a pointer, use ->
    // paw is not a pointer, use .
    std::cout << pointy->paw.claws << '\n';
 
    return 0;
}
```

# [9.19 - For-each loops](https://www.learncpp.com/cpp-tutorial/for-each-loops/)
## For-each loops
A simpler and safer type of loop is the **for-each** loop (a.k.a. a **range-based for-loop**) for cases where we want to iterate through every element in an array (or other list-type structure).

The basic syntax looks like:
```cpp
for (element_declaration : array)
    statement;
```

The loop will iterate through each element in the array, assigning the value of the current array element to the variable declared in element_declaration. element_declaration shoud have the same type as the array elements, otherwise type conversion will occur.

An example:
```cpp
#include <iostream>

int main()
{
    constexpr int fibonacci[]{ 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 };

    for (int number : fibonacci) // iterate over array fibonacci
    {
        std::cout << number << ' ';
    }

    std::cout << '\n';

    return 0;
}
```
prints:
```
0 1 1 2 3 5 8 13 21 34 55 89 
```

Because the type of `element_declaration` should match the array elements, this is a perfect use-case for the `auto` keyword so C++ can deduce the type.
```cpp
#include <iostream>

int main()
{
    constexpr int fibonacci[]{ 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 };

    for (auto number : fibonacci) // iterate over array fibonacci
    {
        std::cout << number << ' ';
    }

    std::cout << '\n';

    return 0;
}
```

## For-each loops and references
Normally, each array element is *copied* into the `element_declaration` variable. But we can take it by reference, which means:
* we can avoid making a copy (sometime more performant)
* modify the value directly!!!
* make it a const reference if we don't want to modify it.

**Best practice:** in for-each loops element declarations, if your elements are non-fundamental types, use references or const refernces for performance reasons.

An example with both a reference that modifies the original array and a const reference:
```cpp
#include <iostream>

int main()
{
    int array[]{ 1, 3, 5, 7, 9 };

    for (auto& element : array)
    {
        element = element + 1;
    }

    for (const auto& element: array)
    {
        std::cout << element << ' ';
    }

    std::cout << '\n';

    return 0;
}
```

## For-each loops and non-arrays
For-each loops also work with other list-like structures like vectors (std::vector), linked lists, trees, and maps.

## For-each doesn't work with pointers to an array
Because for-each needs to know how big the array is, which means knowing the array size. But arrays that have decayed to a pointer do not know their size!
```cpp
#include <iostream>
 
int sumArray(const int array[]) // array is a pointer
{
    int sum{ 0 };
 
    for (auto number : array) // compile error, the size of array isn't known
    {
        sum += number;
    }
 
    return sum;   
}
 
int main()
{
     constexpr int array[]{ 9, 7, 5, 3, 1 };
 
     std::cout << sumArray(array) << '\n'; // array decays into a pointer here
 
     return 0;
}
```
Dynamic arrays DO NOT work with for-each loops for the same reason.

## Can I get the index of the current element?
For-each loops DO NOT provide a direct way to get the array index of the current element, but starting in C++20 you can add an *init-statement* to your range-based for-each loop to add a counter to increment yourself. The format is:
```cpp
for (init-statement; element_declaration : array)
    statement;
```
## Conclusion
For-each loops should be preferred over normal for loops when possible.

See [quiz 2](../9-projects/9-19-quiz/main.cpp) for an example.

# [9.20 - Void pointers](https://www.learncpp.com/cpp-tutorial/void-pointers/)
The **void pointer** (a.k.a. **generic pointer**) is a special type of pointer that can point to objects of any data type.

```cpp
void* ptr; // a void pointer
```

Because a void pointer doesn't know what object type it's pointing to, indirection through it is impossible. It must first be explicitly cast to another pointer type before indirecting through the new pointer. It's up to the programmer to know what to cast it to.

An example:
```cpp
#include <iostream>
 
enum class Type
{
    INT,
    FLOAT,
    CSTRING
};
 
void printValue(void *ptr, Type type)
{
    switch (type)
    {
        case Type::INT:
            std::cout << *static_cast<int*>(ptr) << '\n'; // cast to int pointer and perform indirection
            break;
        case Type::FLOAT:
            std::cout << *static_cast<float*>(ptr) << '\n'; // cast to float pointer and perform indirection
            break;
        case Type::CSTRING:
            std::cout << static_cast<char*>(ptr) << '\n'; // cast to char pointer (no indirection)
            // std::cout knows to treat char* as a C-style string
            // if we were to perform indirection through the result, then we'd just print the single char that ptr is pointing to
            break;
    }
}
 
int main()
{
    int nValue{ 5 };
    float fValue{ 7.5f };
    char szValue[]{ "Mollie" };
 
    printValue(&nValue, Type::INT);
    printValue(&fValue, Type::FLOAT);
    printValue(szValue, Type::CSTRING);
 
    return 0;
}
```

## Void pointer miscellany
* Void pointers can be set to a null value 
    ```cpp
    void* ptr{ nullptr };
    ```
* Avoid deleting a void pointer that points to dynamically allocated memory.
* It's not possible to do pointer arithmetic on a void pointer (the pointer needs to know what size and type object it's pointing to)
* There is no such thing as a void reference.

## Conclusion
Avoid using void pointers unless it's absolutely necessary. They effectively allow you to avoid type checking. There are other C++ language features that fill the role of void pointers but also include type checking (e.g. function overloading).

# [9.21 - Pointers to pointers and dynamic multidimensional arrays](https://www.learncpp.com/cpp-tutorial/pointers-to-pointers/)
## Pointers to pointers
A **pointer to a pointer** holds the address of another pointer.

```cpp
int value{ 5 };

// a normal pointer
int* ptr{ &value };

// a pointer to a pointer
int** ptrptr{ &ptr };
std::cout << **ptrptr; // use a double asterisk for indirection
```

Note: the address-of operator requires an l-value, but &value is an r-value, so we CANNOT directly set the pointer to a pointer equal to the address of value through a double ampersand.
```cpp
int value = 5;
int** ptrptr = &&value; // ERROR!!! double ampersand doesn't work here.
```

## Arrays of pointers
One of the most common uses of pointers to pointers is to dynamically allocate an array of pointers:
```cpp
int** array = new int*[10]; // allocate an array of 10 pointers
```

## Two-dimensional dynamically allocated arrays
This is complicated. Reread this section when implementing.

## Conclusion
**Recommendation:** avoid using pointers to pointers unless no other options are available.

# [9.22 - An introduction to std::array](https://www.learncpp.com/cpp-tutorial/an-introduction-to-stdarray/)
`std::array` provides a *fixed array functionality* that *won't decay* when passed into a function. 

See below for an example of declaring and initializing an std::array
```cpp
#include <array>

std::array<int, 3> myArray; // declare an integer array with length 3
std::array<int, 5> myArray2{ 9, 7, 5, 3, 1 }; // list initialization
std::array<int, 5> myArray3 = { 10, 4, 2, 6, 8}; // initializer list
```

You cannot omit the type or length in C++14.

You can also assign values using an initializer list:
```cpp
std::array<int, 5> myArray;
myArray = { 1, 2, 3, 4, 5 };
myArray = {9, 8, 7}; // also okay; elements 3 and 4 are set to zero
```

std::array supports a second form of element access using the `.at()` function that does bounds checking (and throws an error if the requested index is out of bounds). Because it does bounds checking, it is slower but safer.

std::array cleans up after itself when it goes out of scope, so there's no need to do any kind of manual cleanup.

## Size and sorting
A couple cool features of std::array
* you can use the `size()` function to get the length of the std::array
* you can even use `size()` from within a function because it doesn't decay to a pointer
* you can sort it with `std::sort()`

**Best practice:** when passing an std::array to a function, pass it by reference as done below.

For an example of all this:

```cpp
#include <iostream>
#include <array>
#include <algorithm>

void printArray(const std::array<double, 5> &arr)
{
    // pass arr by reference to avoid making a copy
    std::cout << "length: " << arr.size() << '\n';

    for (double element : arr)
    {
        // the for-each loop works with std::array because it doesn't decay to a pointer
        std::cout << element << ' ';
    }

    std::cout << '\n';
}

int main()
{
    std::array<double, 5> myArray{ 1.0, 5.7, 9.0, 2.0, 0.1 };

    std::sort(myArray.begin(), myArray.end());

    printArray(myArray);

    return 0;
}
```

## Passing std::array of different lengths to a function
The type and size of an std::array passed into the function *must* match the function declaration. To handle different std::array sizes and types, we have to have a declaration for each size and type combo. Instead of declaring and defining each manually, we can use templates.
```cpp
#include <array>
#include <cstdef>
#include <iostream>
 
// printArray is a template function
template <class T, std::size_t size> // parameterize the element type and size
void printArray(const std::array<T, size>& myArray)
{
    for (auto element : myArray)
        std::cout << element << ' ';
    std::cout << '\n';
}
 
int main()
{
    std::array myArray5{ 9.0, 7.2, 5.4, 3.6, 1.8 };
    printArray(myArray5);
 
    std::array myArray7{ 9.0, 7.2, 5.4, 3.6, 1.8, 1.2, 0.7 };
    printArray(myArray7);
 
    return 0;
}
```

## Manually indexing std::array via size_type
`size()` returns a type called `size_type` which is an *unsigned integral* type. The full prefix for this type is
```cpp
std::array<int, 5>::size_type
```
but fortunately, this is an alias for `std::size_t`

To iterate forwards through an std::array:
```cpp
#include <array>
#include <iostream>
#include <cstddef> // std::size_t

int main()
{
    std::array<int, 5> myArray { 7, 3, 1, 9, 5 };

    for (std::size_t i{ 0 }; i < myArray.size(); ++i)
    {
        std::cout << myArray[i] << ' ';
    }

    std::cout << '\n';

    return 0;
}
```

To iterate in reverse order, see below. Note that because the iterator is an unsigned type, the decrement has to happen in the conditional and takes the form `i--` to return a copy of the current value and then decrement.
```cpp
#include <array>
#include <iostream>

int main()
{
    std::array myArray { 7, 3, 1, 9, 5 };

    for (auto i{ myArray.size() }; i-- > 0; )
    {
        // we use auto for the iterator type because we don't initialize to zero
        // we decrement in the conditional
        std::cout << myArray[i] << ' ';
    }

    std::cout << '\n';

    return 0;
}
```

**Best practice:** avoid manual indexing of std::array by instead using range-based for loops or iterators if possible.

## Array of struct
To initialize an array of struct:
```cpp
#include <array>
#include <iostream>

struct House
{
    int number{};
    int stories{};
    int roomsPerStory{};
};

struct Array
{
    House value[3]{};
};

int main()
{
    Array houses{
        { {13, 4, 30}, {14, 5, 31}, {15, 6, 32} }
    };

    // Alternative, more manual method:
    // houses[0] = {13, 4, 30};
    // houses[1] = {14, 5, 31};
    // houses[2] = {15, 6, 32};

    for (const auto& house : houses.value)
    {
        std::cout   << "House number " << house.number
                    << " has " << (house.stories * house.roomsPerStory)
                    << " rooms\n";
    }
    
    return 0;
}
```

**Recommendation:** use std::array over built-in fixed arrays for any non-trivial array use.

# [9.23 - An introduction to std::vector](https://www.learncpp.com/cpp-tutorial/an-introduction-to-stdvector/)
std::vector provides functionality that makes working with dynamic arrays safer and easier.

## An introduction to std::vector
std::vector provides dynamic array functionality that handles its own memory management. This means:
* you can create arrays that have their length set at runtime
* you DO NOT have to worry about allocating and deallocating memory using `new` and `delete`

```cpp
#include <vector>

// declaration
std::vector<int> array; // no need to specify length at declaration

// initialization
std::vector<int> array2{ 9, 7, 5, 3, 1 };

// assignment
array = { 0, 2, 4, 6 }; // array length is now 4
array = { 0, 5, 3 }; // array length is now 3

// accessing elements
array[2] = 9;       // no bounds checking
array.at(1) = 8;    // does bounds checking
```

## Self-cleanup prevents memory leaks
std::vector automatically deallocates the memory it controls. This avoids memory leaks and is much safer than doing your own memory allocation.

## Vectors remember their length
Just like std::array, std::vector objects keep track of their length and can be accessed via the `size()` function. Just like with std::array, `size()` returns a value of `std::vector<type>::size_type` (e.g. `std::vector<int>::size_type`) which is an unsigned integer.

## Resizing a vector
You can resize a vector to be larger or smaller very easily.

Resizing to be larger:
```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector array{ 0, 1, 2 };
    array.resize(5); // set size to 5

    std::cout << "The length is: " << array.size() << '\n';

    for (int i : array)
    {
        std::cout << i << ' ';
    }
    std::cout << '\n';

    return 0;
}
```
The extra new elements are initialized to zero. This prints:
```
The length is: 5
0 1 2 0 0
```

To resize smaller:
```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector array{ 0, 1, 2, 3, 4 };
    array.resize(3); // set size to 3

    std::cout << "The length is: " << array.size() << '\n';

    for (int i : array)
    {
        std::cout << i << ' ';
    }
    std::cout << '\n';

    return 0;
}
```

This prints:
```
The length is: 3
0 1 2
```

Resizing a vector is computationally expensive, so do it sparingly.

To zero-initialize a vector for which you know the size, use *direct initialization*
```cpp
#include <iostream>
#include <vector>

int main()
{
    // direct initialization creates a zero-initialized vector
    // here with length 5
    std::vector<int> array(5);

    std::cout << "The length is: " << array.size() << '\n';

    for (int i : array)
    {
        std::cout << i << ' ';
    }

    std::cout << '\n';

    return 0;
}
```

## Conclusion
**Recommendation:** use std::vector in most cases where dynamic arrays are needed because it handles its own memory management, remembers its length, and can be easily resized.

# [9.24 - Introduction to iterators](https://www.learncpp.com/cpp-tutorial/introduction-to-iterators/)
## Iterators
An **iterator** is an object designed to traverse through a container (e.g. the values in an array or the characters in a string), providing access to each element along the way.

They give us a consistent method to iterate through a wide variety of container types.

## Standard library iterators
There are several types of standard library iterators. Don't worry about the types for now, all we need are four things: 1) the begin point, 2) the end point, 3) operator++ to increment, 4) operator* to get the value of the current element.

To get the begin and end points:
```cpp
#include <array>
#include <iterator>
#include <iostream>

int main()
{
    std::array<int, 3> array{ 1, 2, 3 };

    // begin point
    auto begin{ array.begin() };      // container function
    auto begin2{ std::begin(array) }; // standard library generic function

    std::cout << begin << '\n';     // these both print the same address
    std::cout << begin2 << '\n';    // these both print the same address

    // end point
    auto end{ array.end() };    // container function
    auto end2{ std::end(array)}; // standard libary generic function

    std::cout << end << '\n';   // these both print the same address
    std::cout << end << '\n';   // these both print the same address

    return 0;
}
```

## Back to range-based for loops
Range-based for loops can be used with all types that have begin and end member functions or can be used with std::begin and std::end.

You can add these begin and end member functions to your own types later so the can be usable with range-based for loops.

## Iterator invalidation (dangling iterators)
Iterators can be left "dangling" if the elements being iterated over change address or are destroyed. When this happens, we say the iterator has been **invalidated**. Accessing invalidated iterators causes undefined behavior.

Good documentation notes which container operations will invalidate iterators.

# [9.25 - Introduction to standard library algorithms](https://www.learncpp.com/cpp-tutorial/introduction-to-standard-library-algorithms/)
Use 'em if you can to avoid writing your own.

**Best practice:** unless otherwise specified, do not assume that the standard library algorithms will execute in a particular sequence. std::for_each, std::copy, std::copy_backward, std::move, and std::move_backward have sequential guarantees.

# [Chapter 9 Summary](https://www.learncpp.com/cpp-tutorial/chapter-9-comprehensive-quiz/)
