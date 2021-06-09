#include <iostream>

void changeN(int& ref)
{
    ref = 6;
}

int main()
{
    int n{ 5 };

    std::cout << n << '\n';

    changeN(n); // note that n does not need to be a reference

    std::cout << n << '\n';

    return 0;
}