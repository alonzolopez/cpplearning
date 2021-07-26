#include <iostream>
#include <cmath>

class Fraction
{
private:
    int m_numerator{ 0 };
    int m_denominator{ 1 };
public:
    Fraction(int numerator, int denominator = 1) : m_numerator{numerator}, m_denominator{denominator} 
    {
        if (m_numerator != 0 && m_denominator != 0)
		{
			int m_gcd{ gcd(m_numerator, m_denominator) };
			m_numerator /= m_gcd;
			m_denominator /= m_gcd;
		}
    }
    void print()
    {
        std::cout << m_numerator << '/' << m_denominator << '\n';
    }
    friend Fraction operator*(const Fraction &f, const Fraction &g);
    friend Fraction operator*(const Fraction &f, int g);
    friend Fraction operator*(int g, const Fraction &f);
    int gcd(int a, int b) 
    {
        return (b == 0) ? std::abs(a) : gcd(b, a % b);
    }
};

Fraction operator*(const Fraction &f, const Fraction &g)
{
    return { f.m_numerator * g.m_numerator, f.m_denominator * g.m_denominator};
}

Fraction operator*(const Fraction &f, int g)
{
    return { f.m_numerator * g, f.m_denominator};
}

Fraction operator*(int g, const Fraction &f)
{
    return { f.m_numerator * g, f.m_denominator};
}

int main()
{
    Fraction f1{2, 5};
    f1.print();
 
    Fraction f2{3, 8};
    f2.print();
 
    Fraction f3{ f1 * f2 };
    f3.print();
 
    Fraction f4{ f1 * 2 };
    f4.print();
 
    Fraction f5{ 2 * f2 };
    f5.print();
 
    Fraction f6{ Fraction{1, 2} * Fraction{2, 3} * Fraction{3, 4} };
    f6.print();
 
    return 0;
}