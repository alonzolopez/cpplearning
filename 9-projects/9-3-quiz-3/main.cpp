#include <iostream>
#include <iterator> // for std::size
 
int main()
{
    constexpr int scores[]{ 84, 92, 76, 81, 56 };
 
    // int maxScore{ 0 }; // Assume our largest score is 0 to start
    int indexOfMax{ 0 };
    const int arraySize{ sizeof(scores) / sizeof(scores[0])};

    // now look for a larger score in the full array
    for (int student{ 0 }; student < arraySize; ++student)
    {
        if (scores[student] > scores[indexOfMax])
        {
            indexOfMax = student;
        }
    }
 
    std::cout << "The best score was " << scores[indexOfMax] << '\n';
 
    return 0;
}