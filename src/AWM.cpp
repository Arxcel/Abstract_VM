//
// Created by Vadym KOZLOV on 5/1/18.
//

#include "AWM.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
typedef std::pair<std::string, IOperand const*> pairInst;
AWM::AWM(){};
AWM::~AWM(){
	for(auto i = _instructions.begin(); i != _instructions.end(); i++) {
		if ((*i).second)
			delete (*i).second;
	}
};
AWM::AWM(AWM const &){};
AWM &AWM::operator=(AWM const &){ return *this;};
AWM::AWM(bool rFF, bool eTF, std::string const &eP, std::string const &fP):
_filePath(fP), _errPath(eP), _errToFile(eTF), _readFromFile(rFF) {};

void AWM::start() {
	std::string instructions;
	instructions = readInstructions();
	parseInstructions(instructions);
	for (auto i = _instructions.begin(); i != _instructions.end(); i++)
	{
		if ((*i).first == "push" || (*i).first == "assert")
			std::cout << (*i).first << " " << (*i).second->getType() << " " << (*i).second->toString() << std::endl;
		else
			std::cout << (*i).first << std::endl;
	}
};

void AWM::parseInstructions(std::string const &instructions) {
	std::stringstream ss(instructions);
	std::string line;
	while (getline(ss, line)){
		if (std::regex_match(line, std::regex(R"(^;.*$)")) ||
			std::regex_match(line, std::regex(R"(^\s*$)")))
			continue ;
		IOperand const *tmp = _parser.parseInstruction(line);
		_instructions.emplace_back(pairInst(line, tmp));
	}
};

std::string AWM::readInstructions() {
	std::string instructions;
	if (_readFromFile && !_errToFile) {
		instructions = readFromFile(_filePath);
	} else {
		instructions = readFromStdI();
	}
	return instructions;
}

std::string AWM::readFromFile(std::string const &path) const {
	std::string line;
	std::stringstream ss;
	std::ifstream f(path);
	if (f.is_open()) {
		while (getline(f, line)) {
			ss << _lexer.validateLine(line) << std::endl;
		}
		f.close();
	} else {
		throw CustomException(std::string("Error: ") + std::strerror(errno));
	}
	return ss.str();
};

std::string AWM::readFromStdI() const {
	std::string line;
	std::stringstream ss;
	while(true) {
		getline(std::cin, line);
		if (line == ";;")
			break ;
		ss << _lexer.validateLine(line) << std::endl;
	}
	return ss.str();
};
