#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct StudentGrade
{
    std::string m_name{};
    char m_grade{};
};

class GradeMap
{
private:
    std::vector<StudentGrade> m_map{};
public:
    GradeMap(){};
    char& operator[] (std::string name)
    {
        char grade;
        auto found{std::find_if(begin(m_map), end(m_map), [name](const auto& student) {
                return (student.m_name == name);
            })};
        if (found != end(m_map))
        {
            return found->m_grade;
        }
        else
        {
            m_map.push_back( {name});
            return m_map.back().m_grade;
        }
    }
};

int main()
{
	GradeMap grades{};
 
	grades["Joe"] = 'A';
	grades["Frank"] = 'B';
 
	std::cout << "Joe has a grade of " << grades["Joe"] << '\n';
	std::cout << "Frank has a grade of " << grades["Frank"] << '\n';
 
	return 0;
}