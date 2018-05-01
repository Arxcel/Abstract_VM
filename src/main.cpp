#include <iostream>
#include "Operand.hpp"
#include "AWM.hpp"
#include "Lexer.hpp"

int main(int ac, char *av[]) {
	try {
		AWM *awm;
		if (ac == 1) {
			awm = new AWM(false, false, "./errors.log", "");
		} else if (ac == 2) {
			awm = new AWM(true, false, "./errors.log", av[1]);
		} else {
			throw CustomException("Too many arguments!");
		}
		awm->start();
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
//	std::cout << INT8_MIN << ' ' << INT8_MAX << std::endl;
//	std::cout << INT16_MIN << ' ' << INT16_MAX << std::endl;
//	std::cout << INT32_MIN << ' ' << INT32_MAX << std::endl;
//	std::cout << FLT_MIN << ' ' << FLT_MIN << std::endl;
//	std::cout << DBL_MIN << ' ' << DBL_MIN << std::endl;

	return 0;
}