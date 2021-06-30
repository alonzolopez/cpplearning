#include <iostream>

int factorial(int n)
{
    if (n <= 0)
    {
        // handle zero and negative input by returning zero
        return 0;
    }
    else if (n == 1)
    {
        // base case
        return 1;
    }
    else
    {
        // recursive call
        return n * factorial(n - 1);
    }
    
}

int main()
{
    for (int iii{ 0 }; iii < 8; ++iii)
    {
        std::cout << factorial(iii) << '\n';
    }

    return 0;

}