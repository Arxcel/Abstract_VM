//
// Created by Vadym KOZLOV on 5/1/18.
//

#include "Lexer.hpp"
#include "CustomException.hpp"

Lexer::Lexer(){
	_patterns.emplace_back(std::regex(R"(^\s*push\s*(Int(8|16|32)|Float|Double)\([0-9]+\)\s*(|;.*)$)"));
	_patterns.emplace_back(std::regex(R"(^\s*pop\s*(|;.*)$)"));
	_patterns.emplace_back(std::regex(R"(^\s*dump\s*(|;.*)$)"));
	_patterns.emplace_back(std::regex(R"(^\s*assert\s*(Int(8|16|32)|Float|Double)\([0-9]+\)\s*(|;.*)$)"));
	_patterns.emplace_back(std::regex(R"(^\s*add\s*(|;.*)$)"));
	_patterns.emplace_back(std::regex(R"(^\s*sub\s*(|;.*)$)"));
	_patterns.emplace_back(std::regex(R"(^\s*mul\s*(|;.*)$)"));
	_patterns.emplace_back(std::regex(R"(^\s*div\s*(|;.*)$)"));
	_patterns.emplace_back(std::regex(R"(^\s*mod\s*(|;.*)$)"));
	_patterns.emplace_back(std::regex(R"(^\s*print\s*(|;.*)$)"));
	_patterns.emplace_back(std::regex(R"(^\s*exit\s*(|;.*)$)"));
};
Lexer::~Lexer(){};
std::string &Lexer::validateLine(std::string &src) const {
	bool valid = false;
	for (auto i = _patterns.begin(); i != _patterns.end(); i++) {
		if (std::regex_match(src, *i)) {
			valid = true;
			break ;
		}
	}
	if (!valid)
		throw CustomException("Not valid symbol!");
	return src;
};

Lexer::Lexer(Lexer const &){};
Lexer &Lexer::operator=(Lexer const &){ return *this;};