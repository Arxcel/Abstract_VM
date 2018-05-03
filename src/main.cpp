#include <iostream>
#include "Operand.hpp"
#include "AWM.hpp"

int main(int ac, char *av[]) {
	AWM *awm = nullptr;
	bool t = false;
	try {
			if (ac == 1) {
				awm = new AWM(false, false, "");
			} else if (ac == 2) {
				std::string tmp(av[1]);
				if (tmp == "-l") {
					awm = new AWM(false, true, "");
					t = true;
				} else
					awm = new AWM(true, false, av[1]);
			} else if (ac == 3) {
				std::string tmp(av[1]);
				if (tmp == "-l") {
					awm = new AWM(true, true, av[2]);
					t = true;
				} else
					throw CustomException("Not valid option!");
			} else {
				throw CustomException("Too many arguments!");
			}
			awm->start();
			delete awm;
	} catch (CustomException &e) {
		if (t){
			awm->getLogPath() << e.what() << std::endl;
		} else {
			std::cout << e.what() << std::endl;
		}
		delete awm;
	} catch (std::exception &e) {
		if (t){
			awm->getLogPath() << e.what() << std::endl;
		} else {
			std::cout << e.what() << std::endl;
		}
		delete awm;
	}
	return 0;
}