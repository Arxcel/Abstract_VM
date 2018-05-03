//
// Created by Arxcel on 4/29/18.
//

#ifndef FOPERAND_HPP
#define FOPERAND_HPP
#include "IOperand.hpp"
#include <map>

enum ePrecision {
	int8Precision=0,
	int16Precision=0,
	int32Precision=0,
	floatPrecision=7,
	doublePrecision=14,
};

class FOperand {
public:
	FOperand();
	FOperand(FOperand const &);
	FOperand &operator=(FOperand const &);
	virtual ~FOperand();
	IOperand const *createOperand(eOperandType const &t, std::string val) const;
private:
	IOperand const *createInt8(std::string const &v) const;
	IOperand const *createInt16(std::string const &v) const;
	IOperand const *createInt32(std::string const &v) const;
	IOperand const *createFloat(std::string const &v) const;
	IOperand const *createDouble(std::string const &v) const;
	std::map<eOperandType, IOperand const* (FOperand::*)(std::string const &v) const> _creationMap;
};



#endif
