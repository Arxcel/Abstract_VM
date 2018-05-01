//
// Created by Vadym KOZLOV on 5/1/18.
//

#include "AWM.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include "CustomException.hpp"
AWM::AWM(){};
AWM::~AWM(){};
AWM::AWM(AWM const &){};
AWM &AWM::operator=(AWM const &){ return *this;};
AWM::AWM(bool rFF, bool eTF, std::string const &eP, std::string const &fP):
_filePath(fP), _errPath(eP), _errToFile(eTF), _readFromFile(rFF) {

}

void AWM::start() {
	std::string instructions;
	if (_readFromFile && !_errToFile)
	{
		instructions = readFromFile(_filePath);
	} else {
		instructions = readFromStdI();
	}
}

std::string AWM::readFromFile(std::string const &path) const
{
	std::string line;
	std::stringstream ss;
	std::ifstream f(path);
	if (f.is_open()) {
		while (getline(f, line)) {
			ss << _lexer.validateLine(line) << std::endl;
		}
		f.close();
	} else {
		std::string err("Error: ");
		err += std::strerror(errno);
		throw CustomException(err);
	}
	return ss.str();
}

std::string AWM::readFromStdI() const
{
	std::string line;
	std::stringstream ss;
	while(true) {
		getline(std::cin, line);
		if (line.find(";;") == std::string::npos)
			break ;
		ss << _lexer.validateLine(line) << std::endl;
	}
	return ss.str();
}
