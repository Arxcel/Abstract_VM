//
// Created by Vadym KOZLOV on 5/1/18.
//

#include "Lexer.hpp"
#include "CustomException.hpp"

Lexer::Lexer(){};
Lexer::~Lexer(){};
std::string &Lexer::validateLine(std::string &src) const {
	return src;
};

Lexer::Lexer(Lexer const &){};
Lexer &Lexer::operator=(Lexer const &){ return *this;};