#include <iostream>
#include <string>
#include <array>
#include <algorithm>

struct Student
{
    std::string name{};
    int score{};
};

int main()
{
    std::array<Student, 8> arr{
    { { "Albert", 3 },
        { "Ben", 5 },
        { "Christine", 2 },
        { "Dan", 8 }, // Dan has the most points (8).
        { "Enchilada", 4 },
        { "Francis", 1 },
        { "Greg", 3 },
        { "Hagrid", 5 } }
    };

    // const because we don't want to modify it
    // auto so we infer the type as returned from std::max_element
    // the comparison fnxn is our lambda
    // it takes in const so as to avoid modifying the values
    // and infers the type using auto (it should be a student)
    // and takes it in by reference so avoid copying the struct
    const auto best_student { 
        std::max_element(arr.begin(), arr.end(), [](const auto &a, const auto &b){
            return a.score < b.score;
        })
    };
    
    std::cout << best_student->name << " is the best student\n";

    return 0;
}