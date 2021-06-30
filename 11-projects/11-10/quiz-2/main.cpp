#include <iostream>

int sumDigits(int input)
{
    if (input < 10)
    {
        return input;
    }
    else
    {
        return sumDigits(input / 10 ) + (input % 10);
    }

}

int main()
{
    std::cout << sumDigits(93427) << '\n';
    return 0;
}