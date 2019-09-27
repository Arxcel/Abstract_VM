# Abstract_VM

The first C++ project of the  UNIT Factory (School 42) study program.

#### Table of Contents
- [Intro](#intro)
- [Description](#description)
- [Execution](#execution)
- [Requirements](#requirements)
- [Installation](#installation)
- [Author](#author)

## Intro

__AbstractVM__ is a machine that uses a stack to compute simple arithmetic expressions. These arithmetic expressions are provided to the machine as basic assembly programs.

## Description

As for any assembly language, the language of __AbstractVM__ is composed of a series of instructions, with one instruction per line. However, __AbstractVM__’s assembly language has a limited type system, which is a major difference from other real world assembly languages.

Additional flag: '-l' can be used to store result of the program execution in a file 'info.log'.

Comments: Comments start with a ’;’ and finish with a newline. A comment can be either at the start of a line, or after an instruction.

* ___push v___: Pushes the value v at the top of the stack. The value v must have one of the following form:
    * ___int8(n)___ : Creates an 8-bit integer with value n.
    * ___int16(n)___ : Creates a 16-bit integer with value n.
    * ___int32(n)___ : Creates a 32-bit integer with value n.
    * ___float(z)___ : Creates a float with value z.
    * ___double(z)___ : Creates a double with value z.

* ___pop___: Unstacks the value from the top of the stack. If the stack is empty, the program execution must stop with an error.

* ___dump___: Displays each value of the stack, from the most recent one to the oldest one WITHOUT CHANGING the stack. Each value is separated from the next one by a newline.

* ___assert v___: Asserts that the value at the top of the stack is equal to the one passed as parameter for this instruction. If it is not the case, the program execution must stop with an error. The value v has the same form that those passed as parameters to the instruction push.

* ___add___: Unstacks the first two values on the stack, adds them together and stacks the result. If the number of values on the stack is strictly inferior to 2, the program execution must stop with an error.

* ___sub___: Unstacks the first two values on the stack, subtracts them, then stacks the result. If the number of values on the stack is strictly inferior to 2, the program execution must stop with an error.

* ___mul___: Unstacks the first two values on the stack, multiplies them, then stacks the result. If the number of values on the stack is strictly inferior to 2, the program execution must stop with an error.

* ___div___: Unstacks the first two values on the stack, divides them, then stacks the result. If the number of values on the stack is strictly inferior to 2, the program execution must stop with an error. Moreover, if the divisor is equal to 0, the program execution must stop with an error too. Chatting about floating point values is relevant a this point. If you don’t understand why, some will understand. The linked question is an open one, there’s no definitive answer.

* ___mod___: Unstacks the first two values on the stack, calculates the modulus, then stacks the result. If the number of values on the stack is strictly inferior to 2, the program execution must stop with an error. Moreover,if the divisor is equal to 0, the program execution must stop with an error too. Same note as above about fp values.

* ___min___: Unstacks the first two values on the stack, finds the minimum one and stacks the result. If the number of values on the stack is strictly inferior to 2, the program execution must stop with an error.

* ___max___: Unstacks the first two values on the stack, finds the maximum one and stacks the result. If the number of values on the stack is strictly inferior to 2, the program execution must stop with an error.

* ___avg___: Unstacks the first two values on the stack, finds the average and stacks the result. If the number of values on the stack is strictly inferior to 2, the program execution must stop with an error.

* ___pow___: Unstacks the first two values on the stack, raises the first to the power of the second and stacks theresult. If the number of values on the stack is strictly inferior to 2, the program execution must stop with an error.

* ___print___: Asserts that the value at the top of the stack is an 8-bit integer. (If not, see the instruction assert), then interprets it as an ASCII value and displays the corresponding character on the standard output.

* ___exit___: Terminate the execution of the current program. If this instruction does not appears while all others instruction has been processed, the execution must stop with an error.

```
For non commutative operations, consider the stack v1 on v2 on stack_tail,
the calculation in infix notation v2 op v1.
```

When a computation involves two operands of different types, the value returned has the type of the more precise operand. Please do note that because of the extensibility of the machine, the precision question is not a trivial one. This is covered more in details later in this document.
## Execution

__AbstractVM__ is able to run programs from a file passed as a parameter and from the standard input. When reading from the standard input, the end of the program is indicated by the special symbol ";;" otherwise absent.

### Examples ###

```bash
$>cat test/test0
push int32(42)
push int32(33)
add ;poney
push float(44.55)
mul
push double(42.42) ;commentaire de ouf
push int32(42)
dump
pop
assert double(42.42)
exit
$>./avm test/test0
42
42.42
3341.25
```

```bash
$>./avm
push int32(2)
push int32(3)
add
assert int32(5)
dump
exit
;;
5
```

## Requirements

Mac OS El Capitan / Sierra / High Sierra

## Installation

```bash
git clone https://github.com/Arxcel/Abstract_VM.git ~/ft_awm
mkdir ~ft_awm/build
cd ~/ft_awm/build
cmake ..
cmake --build . -- -j$(nproc)
./awm
```
## Author

Vadim Kozlov (vkozlov)
