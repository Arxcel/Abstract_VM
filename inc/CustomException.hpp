//
// Created by Arxcel on 4/29/18.
//

#ifndef CUSTOMEXCEPTION_HPP
#define CUSTOMEXCEPTION_HPP
#include <exception>
#include <string>

class CustomException : public std::exception
{
	public:
	CustomException();
	CustomException(CustomException const &);
	CustomException(std::string const &text);
		virtual const char* what() const throw();
		~CustomException() throw();
private:
	CustomException &operator=(CustomException const &);
	std::string text;
};

#endif
