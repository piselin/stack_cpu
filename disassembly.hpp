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
using in_t = unsigned int;
const unsigned int kInputLimit = 0xffffffff;


class Disassembler {
public:

	Disassembler() : 
		_hex_input(0), _opcode(0), _operand(0), _n_digits(0) {}

	void Decode(const in_t hex);

	// fixme: i would prefere this to be private!
	// but then I would have to blackbox test...
	
	std::string GetInstruction() const;
	// bool CheckInput(const unsigned int input);

	inline in_t GetOpcode() const { return _opcode; }
	inline in_t GetOperand() const { return _operand; }

	void print() const{
		std::cout << std::hex;
		std::cout << "_hex_input " << _hex_input << std::endl;
		std::cout << "_opcode " << _opcode << std::endl;
		std::cout << "_operand " << _operand << std::endl;
		std::cout << std::dec << "_n_digits " << _n_digits << std::endl;
	}

	std::string PrintInstruction() const;

private:

	unsigned int CountDigits();

	in_t _hex_input;
	in_t _opcode;
	in_t _operand;
	unsigned int _n_digits;
};

#endif /* DISASSEMBLY_LIB */