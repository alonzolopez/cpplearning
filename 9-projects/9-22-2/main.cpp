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