#include <iostream>

namespace Animals
{
    enum Animals
    {
        chicken,
        dog,
        cat,
        elephant,
        duck,
        snake,
        num_animals
    };
}

int main()
{
    int legs[Animals::num_animals]{2, 4, 4, 4, 2, 0};

    std::cout << "An elephant has " << legs[Animals::elephant] << " legs\n";
    return 0;
}