//
// Created by Arxcel on 4/29/18.
//

#ifndef ABSTRACT_VM
#define ABSTRACT_VM
#include "IOperand.hpp"
#include <sstream>
#include <limits>
#include <iomanip>
//#include <float.h>
//#include <limits.h>
//#include <math.h>
//#include <iostream>

template <typename T>
class Operand: public IOperand
{
public:
	Operand(std::string const &val, eOperandType t, int precision): _type(t), _precision(precision){
		std::stringstream ss;
		if (t < Float)
		{
			long long v = std::stoll(val);
			//Need to check overflow
			_value = static_cast<T>(v);
			std::stringstream ss;
			ss << std::setprecision(precision) << v;
			_str = ss.str();
		}
		else
		{
			long double v = std::stod(val);
			//Need to check overflow
			_value = static_cast<T>(v);
			std::stringstream ss;
			ss << std::setprecision(precision) << v;
			_str = ss.str();
		}
	}

	virtual int getPrecision( void ) const {
		return _precision;
	};
	virtual eOperandType getType( void ) const {
		return _type;
	};
	virtual IOperand const * operator+( IOperand const & rhs ) {
		eOperandType	t;
		int				p;
		getTypePrec(t, p, rhs);
		std::stringstream ss;
		if (t < Float)
		{
			long long res = std::stoll(_str) + std::stoll(rhs.toString());
			//Overflow check
			ss << std::setprecision(p) << res;
		}
		else
		{
			long double res = std::stod(_str) + std::stod(rhs.toString());
			//Overflow check
			ss << std::setprecision(p) << res;
		}
		//create new instance t, p, ss.str()
	}; // Sum
	virtual IOperand const * operator-( IOperand const & rhs ) const = 0; // Difference
	virtual IOperand const * operator*( IOperand const & rhs ) const = 0; // Product
	virtual IOperand const * operator/( IOperand const & rhs ) const = 0; // Quotient
	virtual IOperand const * operator%( IOperand const & rhs ) const = 0; // Modulo
	virtual std::string const & toString( void ) const{
		return _str;
	};
	virtual ~IOperand( void ) {}
private:
	virtual void getTypePrec(eOperandType &t, int &p, IOperand const &rhs)
	{
		t = _type >= rhs.getType() ? _type : rhs.getType();
		p = _precision >= rhs.getPrecision() ? _precision : rhs.getPrecision();
	}
	Operand(): _value(0), _type(Int8), _precision(0),_str(""){}
	Operand(Operand const &){};
	Operand &operator=(Operand const &s){ return *this;};
	T				_value;
	eOperandType	_type;
	int 			_precision;
	std::string		_str;
};

#endif //ABSTRACT_VM_OPERAND_HPP
