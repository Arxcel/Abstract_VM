//
// Created by Vadym KOZLOV on 5/1/18.
//

#ifndef AWM_HPP
#define AWM_HPP

#include <string>
#include "Operand.hpp"
#include "Parser.hpp"
#include "Lexer.hpp"
#include <vector>
#include <map>

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
	std::string readInstructions();
	void runAWM();
	void mPush(IOperand const*);
	void mDump(IOperand const*);
	void mMul(IOperand const*);
	void mPrint(IOperand const*);
	void mExit (IOperand const*);
	void mAssert(IOperand const*);
	void mPop(IOperand const*);
	void mAdd(IOperand const*);
	void mSub(IOperand const*);
	void mDiv(IOperand const*);
	void mMod(IOperand const*);
	void parseInstructions(std::string const &instructions);
	AWM &operator=(AWM const &);
	std::string												_filePath;
	std::string												_errPath;
	bool													_errToFile;
	bool													_readFromFile;
	Parser													_parser;
	Lexer													_lexer;
	std::vector<std::pair<std::string, IOperand const *>>	_instructions;
	std::map<std::string, void (AWM::*)(IOperand const *)> _actionMap;
	std::vector<IOperand const *>							_data;
};


#endif
