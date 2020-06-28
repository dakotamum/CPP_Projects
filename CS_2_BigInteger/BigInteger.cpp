// Dakota Mumford
// Big Integer Assignment

#include <iostream> 
#include <algorithm>
#include <cmath>

#include "BigInteger.hpp"

// default constructor that sets the number to 0
BigInteger::BigInteger()
{
	m_sizeReserved = 4;
	m_digitCount = 0;
	m_number = new char[4];
	for (unsigned int i = 0; i < m_sizeReserved; i++)
	{
		m_number[i] = '0';
	}
}

// overloaded constructor that accepts an integer value
BigInteger::BigInteger(unsigned int intNum)
{
	std::string stringNum = std::to_string(intNum);
	m_digitCount = stringNum.length();
	m_sizeReserved = stringNum.length();
	m_number = new char[stringNum.length()];

	unsigned int arrayLength = stringNum.length() - 1;
	for (unsigned int i = 0; i <= arrayLength; i++)
	{
		m_number[i] = stringNum[arrayLength - i] - '0';
	}
}

// overloaded constructor that accepts a string value
BigInteger::BigInteger(std::string stringNum)
{
	m_digitCount = stringNum.length();
	m_sizeReserved = stringNum.length();
	m_number = new char[stringNum.length()];

	unsigned int arrayLength = stringNum.length() - 1;
	for (unsigned int i = 0; i <= arrayLength; i++)
	{
		m_number[i] = stringNum[arrayLength - i] - '0';
	}
}

// destructor
BigInteger::~BigInteger()
{
	delete[] m_number;
	m_number = nullptr;
}

// copy constructor
BigInteger::BigInteger(const BigInteger& rhs)
{
	m_digitCount = rhs.m_digitCount;
	m_sizeReserved = rhs.m_sizeReserved;
	m_number = new char[m_sizeReserved];
	for (unsigned int i = 0; i < m_sizeReserved; i++)
	{
		m_number[i] = rhs.m_number[i];
	}
}

// overloaded assignment operator
BigInteger& BigInteger:: operator=(const BigInteger& rhs)
{
	m_digitCount = rhs.m_digitCount;
	m_sizeReserved = rhs.m_sizeReserved;
	m_number = new char[m_sizeReserved];
	for (unsigned int i = 0; i < m_sizeReserved; i++)
	{
		m_number[i] = rhs.m_number[i];
	}

	return *this;
}

// ------------------------------------------------------------------
//
// This method accepts a BigInteger and an integer, multiplies them
// together and returns a new BigInteger with the result.
//
// ------------------------------------------------------------------
BigInteger BigInteger::multiply(const BigInteger& x, unsigned int y)
{
	BigInteger result;
	unsigned int carry = 0;
	unsigned int pos = 0;

	for (unsigned int digit = 0; digit < x.m_digitCount; digit++)
	{
		carry += x.getDigit(digit) * y;
		result.setDigit(pos++, carry % 10);
		carry /= 10;
	}

	while (carry > 0)
	{
		result.setDigit(pos++, carry % 10);
		carry /= 10;
	}

	return result;
}

// ------------------------------------------------------------------
//
// Provides a means to display the BigInteger value.  Optionally, some
// debug information can be displayed by setting the 'debug' parameter
// to true.
//
// ------------------------------------------------------------------
void BigInteger::display(bool debug)
{
	for (unsigned int digit = m_digitCount; digit > 0; digit--)
	{
		std::cout << static_cast<int>(m_number[digit - 1]);
	}

	if (debug)
	{
		std::cout << " [size = " << m_sizeReserved << ", digit count = " << m_digitCount << std::endl;
	}
}


// ------------------------------------------------------------------
//
// Returns the digit as the specified positon.  If the position is greater
// that the number representation, a '0' is returned.  Not the best
// idea in the world, but the best we can do for now, can make this better
// in the future.
//
// ------------------------------------------------------------------
char BigInteger::getDigit(unsigned int position) const
{
	if (position < m_digitCount)
	{
		return m_number[position];
	}

	return '0';
}

void BigInteger::setDigit(unsigned int position, char digit)
{
	if (position < m_sizeReserved)
	{
		m_digitCount++;
		m_number[position] = digit;
	}
	else
	{
		m_sizeReserved *= 2;
		char* newArray = new char[m_sizeReserved];

		for (unsigned int i = 0; i < m_sizeReserved; i++)
		{
			newArray[i] = '\0';
		}
		for (unsigned int i = 0; i < m_sizeReserved / 2; i++)
		{
			newArray[i] = m_number[i];
		}

		newArray[position] = digit;
		m_digitCount++;
		delete[] m_number;
		m_number = newArray;
	}
}
