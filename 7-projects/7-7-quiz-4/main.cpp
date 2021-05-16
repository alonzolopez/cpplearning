#include <iostream>

int main()
{
    int count{ 1 };
    constexpr int maxcount{ 5 };

    while (count <= maxcount)
    {
        int inner_count{ maxcount };
        while (inner_count > 0)
        {
            if (inner_count > count)
            {
                std::cout << "  ";
            }
            else
            {
                std::cout << inner_count << ' ';
            }
            --inner_count; 
        }
        std::cout << '\n';
        ++count;
    }

    return 0;
}