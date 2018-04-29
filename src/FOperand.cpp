//
// Created by Arxcel on 4/29/18.
//

#include "FOperand.hpp"

FOperand::FOperand() {

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

IOperand const *FOperand::createOperand(eOperandType const &t, std::string val) const{
//
//	IOperand const* (FOperand::*f)(std::string const &v) const;
//	f = _creationMap.at(t);
//	return ((*this.*f)(val));
	return createInt8("50");
}

IOperand const *FOperand::createInt8(std::string const &v) const {
	return new Operand<char>(v, Int8, 0);
}
IOperand const *FOperand::createInt16(std::string const &v) const {
	return new Operand<short int>(v, Int16, 0);
}
IOperand const *FOperand::createInt32(std::string const &v) const {
	return new Operand<int>(v, Int32, 0);
}
IOperand const *FOperand::createFloat(std::string const &v) const {
	return new Operand<float>(v, Float, 7);
}
IOperand const *FOperand::createDouble(std::string const &v) const {
	return new Operand<double>(v, Double, 14);
}