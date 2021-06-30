#include <functional>

int main()
{
    // method #1: a regular function pointer
    // only works with an empty capture clause
    double (*addNumbers1)(double, double){
        [](double a, double b){
            return (a + b);
        }
    };

    addNumbers1(1, 2);


    // method #2: using std::function to define a fnxn pointer
    // the lambda could have a non-empty capture clause
    std::function<double(double, double)> addNumbers2{
        [](double a, double b){
            return (a + b);
        }
    };

    addNumbers2(3, 4);

    // method #3: using auto
    // stores the lambda with its real type
    auto addNumbers3{
        [](double a, double b){
            return (a + b);
        }
    };

    addNumbers3(5, 6);

    return 0;
}