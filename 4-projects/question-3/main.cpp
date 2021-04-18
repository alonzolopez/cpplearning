#include <iostream>
#include <string>

double getValueFromUser()
{
    double d{};
    std::cout << "Enter a double value: ";
    std::cin >> d;
    return d;
}

char getArithmeticSymbol()
{
    char symbol;
    std::cout << "Enter one of the following: +, -, *, or /: ";
    std::cin >> symbol;
    return symbol;
}

void printAnswer(double d1, double d2, char symbol)
{
    if (symbol == '+')
    {
        std::cout << d1 << " " << symbol << " " << d2 << " = " << d1 + d2 << '\n';
    }
    else if (symbol == '-')
    {
        std::cout << d1 << " " << symbol << " " << d2 << " = " << d1 - d2 << '\n';
    }
    else if (symbol == '*')
    {
        std::cout << d1 << " " << symbol << " " << d2 << " = " << d1 * d2 << '\n';
    }
    else if (symbol == '/')
    {
        std::cout << d1 << " " << symbol << " " << d2 << " = " << d1 / d2 << '\n';
    }
    else
    {
        std::cout << '\n';
    }
}

int main()
{
    double d1 = getValueFromUser();
    double d2 = getValueFromUser();

    char symbol = getArithmeticSymbol();
    
    printAnswer(d1, d2, symbol);

    return 0;
}