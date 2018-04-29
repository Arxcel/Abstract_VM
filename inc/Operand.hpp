//
// Created by Arxcel on 4/29/18.
//

#ifndef ABSTRACT_VM
#define ABSTRACT_VM
#include <sstream>
#include <limits>
#include <iomanip>
#include <cfloat>
#include <climits>
#include <cmath>
#include "CustomException.hpp"
#include "IOperand.hpp"

template <typename T>
class Operand: public IOperand
{
public:
	Operand(std::string const &val, eOperandType t, int precision): _type(t), _precision(precision) {
		std::stringstream ss;
		if (t < Float) {
			long long v = std::stoll(val);
			if (isOverflow(_type, v)) {
				throw CustomException("Overflow or underflow!");
			}
			_value = static_cast<T>(v);
			ss << std::setprecision(precision) << v;
			_str = ss.str();
		} else {
			long double v = std::stod(val);
			if (isOverflow(_type, v)) {
				throw CustomException("Overflow or underflow!");
			}
			_value = static_cast<T>(v);
			ss << std::setprecision(precision) << v;
			_str = ss.str();
		}
	};
	int getPrecision() const {
		return _precision;
	};
	eOperandType getType( ) const {
		return _type;
	};
	IOperand const * operator+( IOperand const & rhs ) const {
		eOperandType	t;
		int				p;
		getTypePrec(t, p, rhs);
		std::stringstream ss;
		if (t < Float)
		{
			long long res = std::stoll(_str) + std::stoll(rhs.toString());
			if (isOverflow(_type, res)) {
				throw CustomException("Overflow or underflow!");
			}
			ss << std::setprecision(p) << res;
		}
		else
		{
			long double res = std::stod(_str) + std::stod(rhs.toString());
			if (isOverflow(_type, res)) {
				throw CustomException("Overflow or underflow!");
			}
			ss << std::setprecision(p) << res;
		}
		return this;
		//create new instance t, p, ss.str()
	};
//	virtual IOperand const * operator-( IOperand const & rhs ) const = 0; // Difference
//	virtual IOperand const * operator*( IOperand const & rhs ) const = 0; // Product
//	virtual IOperand const * operator/( IOperand const & rhs ) const = 0; // Quotient
//	virtual IOperand const * operator%( IOperand const & rhs ) const = 0; // Modulo
	std::string const & toString() const {
		return _str;
	};
	~Operand() {}
private:
	void getTypePrec(eOperandType &t, int &p, IOperand const &rhs) const {
		t = _type >= rhs.getType() ? _type : rhs.getType();
		p = _precision >= rhs.getPrecision() ? _precision : rhs.getPrecision();
	}
	template <typename D>
	bool isOverflow(eOperandType const &type, D value) const {
		bool overflow = false;
		if (type == Int8) {
			overflow = value >= INT8_MIN && value <= INT8_MAX;
		} else if (type == Int16) {
			overflow = value >= INT16_MIN && value <= INT16_MAX;
		} else if (type == Int32) {
			overflow =  value >= INT32_MIN && value <= INT32_MAX;
		} else if (type == Float) {
			overflow = value >= FLT_MIN && value <= FLT_MAX;
		} else if (type == Double) {
			overflow = value >= DBL_MIN && value <= DBL_MAX;
		} else {
			throw CustomException("Not valid enum type!");
		}
		return !overflow;
	}
	Operand(): _value(0), _type(Int8), _precision(0),_str(""){}
	Operand(Operand const &s){
		static_cast<void>(s);
	};
	Operand &operator=(Operand const &s){
		static_cast<void>(s);
		return *this;
	};
	T				_value;
	eOperandType	_type;
	int 			_precision;
	std::string		_str;
};

#endif
