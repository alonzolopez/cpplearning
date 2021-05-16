#include <iostream>

int main()
{
    int count{ 5 };

    while (count > 0)
    {
        int inner_count{ count };
        while (inner_count > 0)
        {
            std::cout << inner_count << ' ';
            --inner_count; 
        }
        std::cout << '\n';
        --count;
    }

    return 0;
}