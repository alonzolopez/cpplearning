#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <limits>

void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

struct Student
{
    int grade{};
    std::string name{};
};

std::vector<Student> getStudents()
{
    int num_students{};
    std::cout << "How many students would you like to enter? ";
    std::cin >> num_students;

    std::vector<Student> students(num_students);

    for (Student &student : students)
    {
        // must take in each student by reference to modify it

        // clear std::cin
        std::cin.clear();
        ignoreLine();

        // get the student's name
        std::cout << "Enter the student's name: ";
        std::getline(std::cin >> std::ws, student.name);

        // get the student's grade
        std::cout << "Enter the student's grade: ";
        std::cin >> student.grade;
    }

    return students;
}

bool greater(Student a, Student b)
{
    return (a.grade > b.grade);
}

void printStudents(const std::vector<Student> &students)
{
    for (Student student : students)
    {
        std::cout << student.name << " got a grade of " << student.grade << '\n';
    }
}

int main()
{
    // get user input
    std::vector<Student> students = getStudents();

    // sort
    std::sort(std::begin(students), std::end(students), greater);

    // print
    printStudents(students);

    return 0;


}