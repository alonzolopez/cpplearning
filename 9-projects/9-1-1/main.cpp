#include <iostream>

struct Rectangle
{
    int length{};
    int width{};
};

int main()
{
    // int array of prime numbers
    int prime[5]{};
    prime[0] = 2;
    prime[1] = 3;
    prime[2] = 5;
    prime[3] = 7;
    prime[5] = 11;

    std::cout << "The lowest prime number is " << prime[0] << '\n';

    // double array
    double batteryLifeInHours[3]{};
    batteryLifeInHours[0] = 2.0;
    batteryLifeInHours[1] = 3.0;
    batteryLifeInHours[2] = 4.3;

    // struct array
    Rectangle rects[5]{};
    rects[0].length = 24;
    rects[0].width = 16;

    // initializer list
    int primes[5]{ 2, 3, 5, 7, 11 };

    return 0;
}