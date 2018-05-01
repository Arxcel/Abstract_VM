//
// Created by Vadym KOZLOV on 5/1/18.
//

#ifndef AWM_HPP
#define AWM_HPP

#include <string>
#include "Parser.hpp"
#include "Lexer.hpp"

class AWM {
public:
	AWM(bool, bool, std::string const &, std::string const &);
	void start();
	~AWM();
private:
	AWM();
	AWM(AWM const &);
	std::string readFromFile(std::string const &path) const;
	std::string readFromStdI() const;
	AWM &operator=(AWM const &);
	std::string _filePath;
	std::string _errPath;
	bool		_errToFile;
	bool		_readFromFile;
//	Parser		_parser;
	Lexer		_lexer;
};


#endif
