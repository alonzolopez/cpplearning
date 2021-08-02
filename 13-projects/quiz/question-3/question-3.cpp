#include <iostream>
#include <cassert>
 
class IntArray
{
private:
    int m_len;
    int* m_array{nullptr};

public:
    IntArray(int len) : m_len{len} 
    {
        assert (len > 0 && "Array length should be a postive integer");
        m_array = new int[len]{};
    }
    ~IntArray()
    {
        delete[] m_array;
    }
    int& operator[](const int index)
    {
        assert (index < m_len && index >= 0 && "Index must be greater than zero and less than length");
        return m_array[index];
    }
    int& operator[](const int index) const
    {
        assert (index < m_len && index >= 0 && "Index must be greater than zero and less than length");
        return m_array[index];
    }
    friend std::ostream& operator<<(std::ostream& out, const IntArray& a)
    {
        out << a[0] << ' ' << a[1] << ' ' << a[2] << ' ' << a[3] << ' ' << a[4];
        return out;
    }

    // deep copy constructor
    IntArray(const IntArray& a) : m_len{a.m_len}
    {
        delete[] m_array;

        if (a.m_array)
        {
            m_array = new int[m_len];
            for (int i{}; i < m_len; ++i)
            {
                m_array[i] = a[i];
            }
        }
        else
        {
            m_array = nullptr;
        }
    }

    // assigment operator that does a deep copy
    IntArray& operator=(const IntArray& a)
    {
        // do a self-assignment check; if not self-assigning then proceed to do a deep copy
        if (this == &a)
        {
            return *this;
        }

        // delete any memory currently in m_array
        delete[] m_array;
        // copy array length
        m_len = a.m_len;
        // do the assignment
        if (a.m_array)
        {
            m_array = new int[a.m_len];
            for (int j{}; j < a.m_len; ++j)
            {
                m_array[j] = a[j];
            }
        }
        else
        {
            m_array = nullptr;
        }
        return *this;
    }
};

IntArray fillArray()
{
	IntArray a(5);
 
	a[0] = 5;
	a[1] = 8;
	a[2] = 2;
	a[3] = 3;
	a[4] = 6;
 
	return a;
}
 
int main()
{
	IntArray a{ fillArray() };
	std::cout << a << '\n';
 
	auto& ref{ a }; // we're using this reference to avoid compiler self-assignment errors
	a = ref;
 
	IntArray b(1);
	b = a;
 
	std::cout << b << '\n';
 
	return 0;
}