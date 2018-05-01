//
// Created by Vadym KOZLOV on 5/1/18.
//

#ifndef LEXER_HPP
#define LEXER_HPP
#include <string>

class Lexer {
public:
	Lexer();
	~Lexer();
	std::string &validateLine(std::string &) const;
private:
	Lexer(Lexer const &);
	Lexer &operator=(Lexer const &);
};


#endif
