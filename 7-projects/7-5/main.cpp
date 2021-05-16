# include <iostream>

int getIntFromUser(bool first_call)
{
    if (first_call)
    {
        std::cout << "Enter an integer: ";
    }
    else
    {
        std::cout << "Enter another integer: ";
    }
    int x{};
    std::cin >> x;
    return x;
}

char getOperatorFromUser()
{
    std::cout << "Enter an operator: ";
    char o{};
    std::cin >> o;
    return o;
}

int calculate(int x, int y, char o)
{
    switch(o)
    {
        case '+':
            return x + y;
        case '-':
            return x - y;
        case '*':
            return x * y;
        case '/':
            return x / y;
        case '%':
            return x % y;
        default:
            std::cout << "Error: invalid operator\n";
            return 0;
    }
}

int main()
{
    int x = getIntFromUser(true);
    int y = getIntFromUser(false);
    char o = getOperatorFromUser();

    int a = calculate(x, y, o);

    std::cout << "The answer is: " << a << '\n';
    
    return 0;
}