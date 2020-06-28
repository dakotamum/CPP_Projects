// Dakota Mumford
// Big Integer Assignment

#include <iostream>
#include "BigInteger.hpp"

//main demonstrates the capabilities of the BigInteger class.
int main()
{
	// instantiate BigInteger objects
	BigInteger zero, result;
	BigInteger fromIntValue(12345);
	BigInteger fromStringValue("1234567890");

	// test multiply method
	BigInteger result1 = BigInteger::multiply(fromIntValue, 2);
	BigInteger result2 = BigInteger::multiply(fromStringValue, 2);

	// test display method
	result1.display(true);
	result2.display(true);

	// test copy constructor
	BigInteger copyTest(fromStringValue);
	std::cout << std::endl;
	std::cout << "Copy Constructor Test with fromStringValue: ";
	copyTest.display(true);

	// test overloaded assignment operator
	result = result1;
	std::cout << "Assignment Operator Test: ";
	result.display(true);
	std::cout << std::endl;

	return 0;
}