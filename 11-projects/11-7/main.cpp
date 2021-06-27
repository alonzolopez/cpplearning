#include <iostream>
#include <tuple>
#include <functional>

std::tuple<int, int, char> getUserInput()
{
    std::cout << "Enter an integer: ";
    int x{};
    std::cin >> x;

    std::cout << "Enter another integer: ";
    int y{};
    std::cin >> y;

    std::cout << "Enter an operation ('+', '-', '*', '/'): ";
    char op{};
    std::cin >> op;

    return { x, y, op };
}

int add(int x, int y)
{
    return x + y;
}

int subtract(int x, int y)
{
    return x - y;
}

int multiply(int x, int y)
{
    return x * y;
}

int division(int x, int y)
{
    return x / y;
}

using ArithmeticFunction = std::function<int(int, int)>;

ArithmeticFunction getArithmeticFunction(char op)
{
    switch (op)
    {
        default:
        case '+':
            return &add;
        case '-':
            return &subtract;
        case '*':
            return &multiply;
        case '/':
            return &division;
    }
}

int main()
{
    std::tuple<int, int, char> input{ getUserInput() };
    int x{ std::get<0>(input) };
    int y{ std::get<1>(input) };
    char op{ std::get<2>(input) };

    ArithmeticFunction fnxn = getArithmeticFunction(op);
    int answer{ fnxn(x, y) };

    std::cout << x << ' ' <<  op << ' ' << y << " = " << answer << '\n';

    return 0;
}