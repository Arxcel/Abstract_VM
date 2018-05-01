//
// Created by Arxcel on 4/29/18.
//

#include "FOperand.hpp"
#include "Operand.hpp"

FOperand::FOperand() {
	typedef std::pair<eOperandType, IOperand const* (FOperand::*)(std::string const &v) const> mapEl;
	_creationMap.insert(mapEl(Int8, &FOperand::createInt8));
	_creationMap.insert(mapEl(Int16, &FOperand::createInt16));
	_creationMap.insert(mapEl(Int32, &FOperand::createInt32));
	_creationMap.insert(mapEl(Float, &FOperand::createFloat));
	_creationMap.insert(mapEl(Double, &FOperand::createDouble));
}

FOperand::FOperand(FOperand const &r){
	static_cast<void>(r);
}

FOperand &FOperand::operator=(FOperand const &r){
	static_cast<void>(r);
	return *this;
}
FOperand::~FOperand(){

}

IOperand const *FOperand::createOperand(eOperandType const &t, std::string val) const {
	auto f = _creationMap.at(t);
	return ((*this.*f)(val));
}

IOperand const *FOperand::createInt8(std::string const &v) const {
	return new Operand<char>(v, Int8, 0, this);
}
IOperand const *FOperand::createInt16(std::string const &v) const {
	return new Operand<short int>(v, Int16, 0, this);
}
IOperand const *FOperand::createInt32(std::string const &v) const {
	return new Operand<int>(v, Int32, 0, this);
}
IOperand const *FOperand::createFloat(std::string const &v) const {
	return new Operand<float>(v, Float, 7, this);
}
IOperand const *FOperand::createDouble(std::string const &v) const {
	return new Operand<double>(v, Double, 14, this);
}