//
// Created by Vadym KOZLOV on 5/1/18.
//

#ifndef PARSER_HPP
#define PARSER_HPP
#include <string>
#include "IOperand.hpp"
#include "FOperand.hpp"
#include <map>
class Parser {
public:
	Parser();
	~Parser();
	IOperand const *parseInstruction(std::string &instruction);
private:
	Parser(Parser const &);
	Parser &operator=(Parser const &);
	std::map<std::string, eOperandType> _inst;
	FOperand _creator;
};


#endif 
