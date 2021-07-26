#include <iostream>
#include <cmath>

class Fraction
{
private:
    int m_numerator{ 0 };
    int m_denominator{ 1 };
public:
    Fraction(int numerator = 0, int denominator = 1) : m_numerator{numerator}, m_denominator{denominator} 
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
    friend std::ostream& operator<<(std::ostream &out, const Fraction &f);
    friend std::istream& operator>>(std::istream &in, Fraction &f);
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

std::ostream& operator<<(std::ostream &out, const Fraction &f)
{
    out << f.m_numerator << '/' << f.m_denominator;
    return out;
}

std::istream& operator>>(std::istream &in, Fraction &f)
{
    in >> f.m_numerator;
    in >> f.m_denominator;
    return in;
}

int main()
{
    Fraction f1;
	std::cout << "Enter fraction 1: ";
	std::cin >> f1;
 
	Fraction f2;
	std::cout << "Enter fraction 2: ";
	std::cin >> f2;
 
	std::cout << f1 << " * " << f2 << " is " << f1 * f2 << '\n'; // note: The result of f1 * f2 is an r-value
 
	return 0;
}