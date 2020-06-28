#ifndef _BIGINTEGER_HPP_
#define _BIGINTEGER_HPP_

#include <string>

class BigInteger
{
public:
	BigInteger();
	BigInteger(unsigned int intNum);
	BigInteger(std::string stringNum);
	~BigInteger();

	BigInteger(const BigInteger& rhs);
	BigInteger& operator=(const BigInteger& rhs);

	static BigInteger multiply(const BigInteger& x, unsigned int y);
	void display(bool debug = false);

private:
	char* m_number;		// Internal representation of the number.
	unsigned int m_sizeReserved;	// Total size of the allocated space used to internally store the number
	unsigned int m_digitCount;	// How many digits are in the number.

	char getDigit(unsigned int position) const;
	void setDigit(unsigned int position, char digit);
};

#endif
