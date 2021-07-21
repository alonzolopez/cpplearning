#include <iostream>
#include <array>
#include <cassert>

class Stack
{
private:
    std::array<int, 10> m_stack{};
    int m_stack_size{};
    const int m_max_size{10};

public:
    void reset()
    {
        m_stack_size = 0;
    }

    bool push(int a)
    {
        if (m_stack_size >= m_max_size)
        {
            return false;
        }
        else
        {
            m_stack[m_stack_size] = a;
            ++m_stack_size;
            return true;
        }
    }

    int pop()
    {
        assert(m_stack_size > 0 && "The stack must not be empty");
        --m_stack_size;
        return m_stack[m_stack_size];
    }

    void print()
    {
        std::cout << "( ";
        for (int iii{}; iii < m_stack_size; ++iii)
        {
            std::cout << m_stack[iii] << " ";
        }
        std::cout << ")\n";
    }
};

int main()
{
	Stack stack;
	stack.reset();
 
	stack.print();
 
	stack.push(5);
	stack.push(3);
	stack.push(8);
	stack.print();
 
	stack.pop();
	stack.print();
 
	stack.pop();
	stack.pop();
 
	stack.print();
 
	return 0;
}