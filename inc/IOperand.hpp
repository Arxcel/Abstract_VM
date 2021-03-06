//
// Created by Arxcel on 4/29/18.
//

#ifndef IOPERAND_HPP
#define IOPERAND_HPP
#include <string>

enum eOperandType {
		Int8,
		Int16,
		Int32,
		Float,
		Double
};

class IOperand {
public:
	virtual int getPrecision( ) const = 0; // Precision of the type of the instance
	virtual eOperandType getType( ) const = 0; // Type of the instance
	virtual IOperand const * operator+( IOperand const & rhs ) const = 0;
	virtual IOperand const * operator-( IOperand const & rhs ) const = 0; // Difference
	virtual IOperand const * operator*( IOperand const & rhs ) const = 0; // Product
	virtual IOperand const * operator/( IOperand const & rhs ) const = 0; // Quotient
	virtual IOperand const * operator%( IOperand const & rhs ) const = 0; // Modulo
	virtual IOperand const * operator<( IOperand const & rhs ) const = 0; // Min
	virtual IOperand const * operator>( IOperand const & rhs ) const = 0; // Max
	virtual IOperand const * operator>=( IOperand const & rhs ) const = 0; // Avg
	virtual IOperand const * operator<=( IOperand const & rhs ) const = 0; // Pow
	virtual bool operator==(IOperand const & rhs ) const = 0;
	virtual std::string const & toString() const = 0; // String representation of the instance
	virtual ~IOperand() {}
};
#endif
