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
#include "FOperand.hpp"

template <typename T>
class Operand: public IOperand
{
public:
	Operand(std::string const &val, eOperandType t, int precision, FOperand const *fop): _type(t), _precision(precision), _fop(fop) {
		std::stringstream ss;
		if (t < Float) {
			long long v = std::stoll(val);
			if (isOverflow<long long>(_type, v)) {
				throw CustomException("Constructor. Int overflow or underflow!");
			}
			_value = static_cast<T>(v);
			ss << std::setprecision(precision) << v;
			_str = ss.str();
		} else {
			long double v = std::stod(val);
			if (isOverflow<long double>(_type, v)) {
				throw CustomException("Constructor. Float/double overflow or underflow!");
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
		if (t < Float) {
			long long res = std::stoll(_str) + std::stoll(rhs.toString());
			if (isOverflow(_type, res)) {
				throw CustomException("Sum. Int overflow or underflow!");
			}
			ss << std::setprecision(p) << res;
		} else {
			long double res = std::stod(_str) + std::stod(rhs.toString());
			if (isOverflow(_type, res)) {
				throw CustomException("Sum. Float/double overflow or underflow!");
			}
			ss << std::setprecision(p) << res;
		}
		return _fop->createOperand(_type, ss.str());
	};
	IOperand const * operator-( IOperand const & rhs ) const {
		eOperandType	t;
		int				p;
		getTypePrec(t, p, rhs);
		std::stringstream ss;
		if (t < Float) {
			long long res = std::stoll(_str) - std::stoll(rhs.toString());
			if (isOverflow(_type, res)) {
				throw CustomException("Sub. Int overflow or underflow!");
			}
			ss << std::setprecision(p) << res;
		} else {
			long double res = std::stod(_str) - std::stod(rhs.toString());
			if (isOverflow(_type, res)) {
				throw CustomException("Sub. Float/double overflow or underflow!");
			}
			ss << std::setprecision(p) << res;
		}
		return _fop->createOperand(_type, ss.str());
	};
	IOperand const * operator*( IOperand const & rhs ) const {
		eOperandType	t;
		int				p;
		getTypePrec(t, p, rhs);
		std::stringstream ss;
		if (t < Float) {
			long long res = std::stoll(_str) * std::stoll(rhs.toString());
			if (isOverflow(_type, res)) {
				throw CustomException("Multiply. Int overflow or underflow!");
			}
			ss << std::setprecision(p) << res;
		} else {
			long double res = std::stod(_str) * std::stod(rhs.toString());
			if (isOverflow(_type, res)) {
				throw CustomException("Multiply. Float/double overflow or underflow!");
			}
			ss << std::setprecision(p) << res;
		}
		return _fop->createOperand(_type, ss.str());
	};
	IOperand const * operator/( IOperand const & rhs ) const{
		eOperandType	t;
		int				p;
		getTypePrec(t, p, rhs);
		std::stringstream ss;
		if (t < Float) {
			long long div = std::stoll(rhs.toString());
			if (div == 0) {
				throw CustomException("Division. Int. Division by zero exception.");
			}
			long long res = std::stoll(_str) / div;
			if (isOverflow(_type, res)) {
				throw CustomException("Division. Int overflow or underflow!");
			}
			ss << std::setprecision(p) << res;
		} else {
			long double div = std::stod(rhs.toString());
			if (div == 0) {
				throw CustomException("Division. Float/double. Division by zero exception.");
			}
			long double res = std::stod(_str) / div;
			if (isOverflow(_type, res)) {
				throw CustomException("Division. Float/double overflow or underflow!");
			}
			ss << std::setprecision(p) << res;
		}
		return _fop->createOperand(_type, ss.str());
	};
	IOperand const * operator%( IOperand const & rhs ) const {
		eOperandType	t;
		int				p;
		getTypePrec(t, p, rhs);
		std::stringstream ss;
		if (t < Float) {
			long long div = std::stoll(rhs.toString());
			if (div == 0) {
				throw CustomException("Modulo. Int. Division by zero exception.");
			}
			long long res = std::stoll(_str) % div;
			if (isOverflow(_type, res)) {
				throw CustomException("Modulo. Int overflow or underflow!");
			}
			ss << std::setprecision(p) << res;
		} else {
			long double div = std::stod(rhs.toString());
			if (div == 0) {
				throw CustomException("Modulo. Float/double. Division by zero exception.");
			}
			long double res = std::fmod(std::stod(_str), div);
			if (isOverflow(_type, res)) {
				throw CustomException("Modulo. Float/double overflow or underflow!");
			}
			ss << std::setprecision(p) << res;
		}
		return _fop->createOperand(_type, ss.str());
	}
	bool operator==(IOperand const & rhs ) const {
		if (getType() != rhs.getType())
			return false;
		if (getPrecision() != rhs.getPrecision())
			return false;
		if (toString() != rhs.toString())
			return false;
		return true;
	}

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
			overflow = value >= -FLT_MAX && value <= FLT_MAX;
		} else if (type == Double) {
			overflow = value >= -DBL_MAX && value <= DBL_MAX;
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
	FOperand const	*_fop;
	std::string		_str;
};

#endif
