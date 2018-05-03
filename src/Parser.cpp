//
// Created by Vadym KOZLOV on 5/1/18.
//

#include "Parser.hpp"
#include <regex>
#include <sstream>
#include <iostream>

Parser::Parser(){
	typedef std::pair<std::string, eOperandType> mapEl;
	_inst.insert(mapEl("int8", Int8));
	_inst.insert(mapEl("int16", Int16));
	_inst.insert(mapEl("int32", Int32));
	_inst.insert(mapEl("float", Float));
	_inst.insert(mapEl("double", Double));
};
Parser::~Parser(){};
Parser::Parser(Parser const &){};
Parser &Parser::operator=(Parser const &){ return *this;}
IOperand const *Parser::parseInstruction(std::string &instruction) {
	eOperandType	type;
	std::string		value;
	std::string		inst;
	std::stringstream strS(instruction);
	std::string word;

	getline(strS, word, ' ');
	instruction = word;
	if (word != "push" && word != "assert")
		return nullptr;
	getline(strS, word, '(');
	type = _inst.at(word);
	getline(strS, word, ')');
	value = word;
	return _creator.createOperand(type, value);
};
