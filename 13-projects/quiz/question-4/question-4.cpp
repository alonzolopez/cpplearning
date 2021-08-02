#include <iostream>
#include <cstdlib>
#include <cmath>

class FixedPoint2
{
private:
    int m_nonfrac{};
    int m_numerator{};
    int m_denom{100};
public:
    FixedPoint2(int nonfrac = 0, int numerator = 0) : m_nonfrac{nonfrac}, m_numerator{numerator}
    {
        if (m_nonfrac < 0 && m_numerator >= 0)
        {
            m_numerator = -m_numerator;
        }
        if (m_numerator < 0 && m_nonfrac >= 0)
        {
            m_nonfrac = -m_nonfrac;
        }
    }
    FixedPoint2(double input)
        :   m_nonfrac{static_cast<int>(std::round(input*100)/100)}, 
            m_numerator{static_cast<int>( std::round(input * 100) - m_nonfrac*100 )  }
    {}
    friend std::ostream& operator<<(std::ostream& out, FixedPoint2& f)
    {
        out << static_cast<double>(f);
        return out;
    }

    operator double() const
    {
        return m_nonfrac + static_cast<double>(m_numerator) / 100;
    }

    friend bool operator==(const FixedPoint2& a, const FixedPoint2& b)
    {
        return (a.m_nonfrac == b.m_nonfrac && a.m_numerator == b.m_numerator);
    }

    friend std::istream& operator>>(std::istream& in, FixedPoint2& f)
    {
        double input{};
        in >> input;
        f = {input};
        return in;
    }

    FixedPoint2 operator-() const
    {
        return {-m_nonfrac, -m_numerator};
    }

    
};

FixedPoint2 operator+(const FixedPoint2& a, const FixedPoint2& b)
{
    return FixedPoint2{static_cast<double>(a) + static_cast<double>(b)};
}

void testAddition()
{
	// h/t to reader Sharjeel Safdar for this function
	std::cout << std::boolalpha;
	std::cout << (FixedPoint2{ 0.75 } + FixedPoint2{ 1.23 } == FixedPoint2{ 1.98 }) << '\n'; // both positive, no decimal overflow
	std::cout << (FixedPoint2{ 0.75 } + FixedPoint2{ 1.50 } == FixedPoint2{ 2.25 }) << '\n'; // both positive, with decimal overflow
	std::cout << (FixedPoint2{ -0.75 } + FixedPoint2{ -1.23 } == FixedPoint2{ -1.98 }) << '\n'; // both negative, no decimal overflow
	std::cout << (FixedPoint2{ -0.75 } + FixedPoint2{ -1.50 } == FixedPoint2{ -2.25 }) << '\n'; // both negative, with decimal overflow
	std::cout << (FixedPoint2{ 0.75 } + FixedPoint2{ -1.23 } == FixedPoint2{ -0.48 }) << '\n'; // second negative, no decimal overflow
    // std::cout << FixedPoint2{-1.23} << '\n';
    // std::cout << (FixedPoint2{ 0.75 } + FixedPoint2{ -1.23 }) << '\n'; 
	std::cout << (FixedPoint2{ 0.75 } + FixedPoint2{ -1.50 } == FixedPoint2{ -0.75 }) << '\n'; // second negative, possible decimal overflow
    // std::cout << (FixedPoint2{ 0.75 } + FixedPoint2{ -1.50 } ) << '\n'; 
	std::cout << (FixedPoint2{ -0.75 } + FixedPoint2{ 1.23 } == FixedPoint2{ 0.48 }) << '\n'; // first negative, no decimal overflow
    // std::cout << (FixedPoint2{ -0.75 } + FixedPoint2{ 1.23 } ) << '\n'; // first negative, no decimal overflow
	std::cout << (FixedPoint2{ -0.75 } + FixedPoint2{ 1.50 } == FixedPoint2{ 0.75 }) << '\n'; // first negative, possible decimal overflow
    // std::cout << (FixedPoint2{ -0.75 } + FixedPoint2{ 1.50 } ) << '\n'; // first negative, possible decimal overflow
}

int main()
{
    // part b
	// FixedPoint2 a{ 34, 56 };
	// std::cout << a << '\n';
 
	// FixedPoint2 b{ -2, 8 };
	// std::cout << b << '\n';
 
	// FixedPoint2 c{ 2, -8 };
	// std::cout << c << '\n';
 
	// FixedPoint2 d{ -2, -8 };
	// std::cout << d << '\n';
 
	// FixedPoint2 e{ 0, -5 };
	// std::cout << e << '\n';
 
	// std::cout << static_cast<double>(e) << '\n';

    // part c
    // Handle cases where the argument is representable directly
	// FixedPoint2 a{ 0.01 };
	// std::cout << a << '\n';
 
	// FixedPoint2 b{ -0.01 };
	// std::cout << b << '\n';
 
	// // Handle cases where the argument has some rounding error
	// FixedPoint2 c{ 5.01 }; // stored as 5.0099999... so we'll need to round this
	// std::cout << c << '\n';
 
	// FixedPoint2 d{ -5.01 }; // stored as -5.0099999... so we'll need to round this
	// std::cout << d << '\n';
 
	// // Handle case where the argument's decimal rounds to 100 (need to increase base by 1)
	// FixedPoint2 e{ 106.9978 }; // should be stored with base 107 and decimal 0
	// std::cout << e << '\n';

    testAddition();
 
	FixedPoint2 a{ -0.48 };
	std::cout << a << '\n';
 
	std::cout << -a << '\n';
 
	std::cout << "Enter a number: "; // enter 5.678
	std::cin >> a;
	
	std::cout << "You entered: " << a << '\n';
 
	return 0;
}