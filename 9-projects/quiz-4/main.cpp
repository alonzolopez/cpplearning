#include <iostream>

void printCString(const char* strptr)
{
    // print until we reach the null character
    while (*strptr != '\0')
    {
        // print the current character
        std::cout << *strptr << '\n';

        // increment the pointer
        ++strptr;
    }
}

int main()
{
    char str[]{"Alonzo"};

    // we expect the C-style string to decay to a pointer that points
    // to the first element
    printCString(str); 

    return 0;
}