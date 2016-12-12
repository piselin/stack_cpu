#ifndef DISASSEMBLY_LIB
#define DISASSEMBLY_LIB

#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <string>
#include <ostream>


// largest number possible:
// 0xffffffff = 4294967295


// instruction format
using instruction_t = unsigned int;

class Disassembler {
public:

	Disassembler() : 
		_opcode(0), _operand(0), _n_digits(0) {}

	void Decode(const instruction_t hex);
	
	std::string GetInstruction() const;

	inline instruction_t GetOpcode() const { return _opcode; }
	inline int GetOperand() const { return _operand; }

	std::string PrintInstruction() const;

private:

	//unsigned int CountDigits();
	instruction_t _opcode;
	int _operand;	// can be a negative number
	unsigned int _n_digits;
};

#endif /* DISASSEMBLY_LIB */