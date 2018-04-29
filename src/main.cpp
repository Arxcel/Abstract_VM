#include <iostream>
#include "Operand.hpp"

int main() {
	char a;
	char b;
	b = 127;
	a = -128;
	char c = a + b;
	std::cout << INT8_MIN << ' ' << INT8_MAX << std::endl;
	std::cout << INT16_MIN << ' ' << INT16_MAX << std::endl;
	std::cout << INT32_MIN << ' ' << INT32_MAX << std::endl;
	std::cout << FLT_MIN << ' ' << FLT_MIN << std::endl;
	std::cout << DBL_MIN << ' ' << DBL_MIN << std::endl;

	return 0;
}