#include <iostream>
#include <string>
#include <cassert>

class Mystring
{
private:
    std::string m_string;
public:
    Mystring(std::string string) : m_string{string} {}
    std::string operator() (int start, int length) const
    {
        assert(start >= 0);
        assert( (start + length) < static_cast<int>(m_string.length()) && "Mystring::operator(int, int): Substring is out of range");

        std::string out{};
        for (int i{start}; i < (length + start); ++i)
        {
            out += m_string[i];
        }
        return out;
    }
};

int main()
{
    Mystring string{ "Hello, world!" };
    std::cout << string(7, 5) << '\n'; // start at index 7 and return 5 characters
 
    return 0;
}