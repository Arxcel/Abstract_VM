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
	for (auto i = _data.begin(); i!=_data.end(); i++) {
		delete (*i);
	}
};
AWM::AWM(AWM const &){};
AWM &AWM::operator=(AWM const &){ return *this;};
AWM::AWM(bool rFF, bool eTF, std::string const &eP, std::string const &fP):
_filePath(fP), _errPath(eP), _errToFile(eTF), _readFromFile(rFF) {
	typedef std::pair<std::string, void (AWM::*)(IOperand const*)> mapE;
	_actionMap.insert(mapE("push", &AWM::mPush));
	_actionMap.insert(mapE("pop", &AWM::mPop));
	_actionMap.insert(mapE("dump", &AWM::mDump));
	_actionMap.insert(mapE("assert", &AWM::mAssert));
	_actionMap.insert(mapE("add", &AWM::mAdd));
	_actionMap.insert(mapE("sub", &AWM::mSub));
	_actionMap.insert(mapE("mul", &AWM::mMul));
	_actionMap.insert(mapE("div", &AWM::mDiv));
	_actionMap.insert(mapE("mod", &AWM::mMod));
	_actionMap.insert(mapE("print", &AWM::mPrint));
	_actionMap.insert(mapE("exit", &AWM::mExit));
};

void AWM::start() {
	std::string instructions;
	instructions = readInstructions();
	if (instructions.length() > 0)
	{
		parseInstructions(instructions);
		runAWM();
		if (_instructions.back().first != "exit")
			throw CustomException("No 'exit' command.");
	}
};

void AWM::runAWM() {
	for (auto i = _instructions.begin(); i != _instructions.end(); i++) {
		auto f = _actionMap.at((*i).first);
		((*this.*f)((*i).second));
	}
}

void AWM::mPush(IOperand const*d){
	_data.emplace_back(d);
};

void AWM::mDump(IOperand const*){
	for (auto i = _data.rbegin(); i!=_data.rend(); i++) {
		std::cout << (*i)->toString() << std::endl;
	}
};

void AWM::mAssert(IOperand const*d){
	if (!(*_data.back() == *d))
		throw CustomException("Assertion failed!");
};

void AWM::mMul(IOperand const*){
	IOperand const *a;
	IOperand const *b;
	a = _data.back();
	_data.pop_back();
	b = _data.back();
	_data.pop_back();
	_data.push_back(*a * *b);
	delete a;
	delete b;
};

void AWM::mPop(IOperand const*){
	if (_data.empty())
		throw CustomException("Pop on empty stack.");
	IOperand const *a =_data.back();
	_data.pop_back();
	delete a;
};

void AWM::mAdd(IOperand const*){
	IOperand const *a;
	IOperand const *b;
	if (_data.size() < 2)
		throw CustomException("Not enough values in stack for arithmetic.");
	a = _data.back();
	_data.pop_back();
	b = _data.back();
	_data.pop_back();
	_data.push_back(*a + *b);
	delete a;
	delete b;
};
void AWM::mSub(IOperand const*){
	IOperand const *a;
	IOperand const *b;
	if (_data.size() < 2)
		throw CustomException("Not enough values in stack for arithmetic.");
	a = _data.back();
	_data.pop_back();
	b = _data.back();
	_data.pop_back();
	_data.push_back(*b - *a);
	delete a;
	delete b;
};
void AWM::mDiv(IOperand const*){
	IOperand const *a;
	IOperand const *b;
	if (_data.size() < 2)
		throw CustomException("Not enough values in stack for arithmetic.");
	a = _data.back();
	_data.pop_back();
	b = _data.back();
	_data.pop_back();
	_data.push_back(*b / *a);
	delete a;
	delete b;
};
void AWM::mMod(IOperand const*){
	IOperand const *a;
	IOperand const *b;
	if (_data.size() < 2)
		throw CustomException("Not enough values in stack for arithmetic.");
	a = _data.back();
	_data.pop_back();
	b = _data.back();
	_data.pop_back();
	_data.push_back(*b % *a);
	delete a;
	delete b;
};
void AWM::mPrint(IOperand const*){
	if ((_data.back()->getType() != Int8))
		throw CustomException("Assertion failed!");
	auto a = std::stoll(_data.back()->toString());
	std::cout << static_cast<char>(a);
};

void AWM::mExit (IOperand const*){};

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
