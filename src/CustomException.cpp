//
// Created by Arxcel on 4/29/18.
//

#include "CustomException.hpp"

CustomException::CustomException() {

};

CustomException::CustomException(CustomException const &src){
	static_cast<void>(src);
};

CustomException &CustomException::operator=(CustomException const &src) {
	static_cast<void>(src);
	return *this;
};

CustomException::CustomException(std::string const &text) {
	this->text = text;
};

const char* CustomException::what() const throw() {
	std::string res;
	res = "Exception: " + text;
	return (res.c_str());
};

CustomException::~CustomException() throw() {

};
