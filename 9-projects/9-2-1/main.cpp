#include <iostream>

namespace StudentNames
{
    enum StudentNames
    {
        kenny,
        kyle,
        stan,
        butters,
        cartman,
        wendy,
        max_students
    };
}

int main()
{
    int testScores[StudentNames::max_students]{};
    testScores[StudentNames::stan] = 76;
}