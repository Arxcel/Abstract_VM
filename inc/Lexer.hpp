//
// Created by Vadym KOZLOV on 5/1/18.
//

#ifndef LEXER_HPP
#define LEXER_HPP
#include <string>
#include <regex>
#include <vector>

class Lexer {
public:
	Lexer();
	~Lexer();
	std::string &validateLine(std::string &) const;
private:
	Lexer(Lexer const &);
	Lexer &operator=(Lexer const &);
	std::vector<std::regex> _patterns;
};


#endif
