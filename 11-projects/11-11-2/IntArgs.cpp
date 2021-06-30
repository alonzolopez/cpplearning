#include <iostream>
#include <sstream>
#include <string>

int main(int argc, char *argv[])
{
    // this program takes an int as the first input 
    // after the file name itself

    std::stringstream convert{ argv[1] };

    int myint{};

    if (!(convert >> myint)) // do the conversion
    {
        // if the conversion fails, set myint to a default value
        myint = 0;
    }

    std::cout << "Got integer: " << myint << '\n';
    
    return 0;
}