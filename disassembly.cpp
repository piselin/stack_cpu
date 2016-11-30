#include "disassembly.hpp"

/*
Disassembly: 
The program recieves the input in hexadecimal form and
translates it into human readable form

Assembly: translation of human readable format into 
a stream of instructions

Disassembly: the reverse (stream of instructions to
human readable format)


input: 
disassemble
5
0x3200000f
0x12000000
0x3200000a
0x13000000
0x01000000
*/


unsigned int Disassembler::CountDigits() {

	//unsigned int _n_digits = 0;
	unsigned int n = 0;
	in_t h = _hex_input; // working copy

	//const unsigned int kMaxNumberOfDigits = 10; // fixme pi: is this 8 or 10?

	for(unsigned int i = 0; (i < 8) && (h > 0); i++){
		//_n_digits++;
		n++;
		h/=16;
	}
	//std::cout << "after calc : " << std::dec << _n_digits << std::endl;
	//assert(n == 8);
	return n;
}

void Disassembler::Decode(in_t input) {
	_hex_input = input; // keep the original input

	in_t hex = input; // working copy

	_n_digits = CountDigits();
	_operand = 0x0;
	_opcode = 0x0; // halt

	// std::cout << "we are about to set opcode to " << hex << std::endl;
	// std::cout << _n_digits << std::endl;

	if (_n_digits == 0) {
		
	} else if(_n_digits == 1) {
		if(hex == 0x1) {
			_opcode = hex; // we have the exit code
		} else {
			assert(false); // some crap happened!
		}
	} else if(_n_digits == 2) {
		_opcode = hex;		// we have a straight up opcode
	} else {
		
		for(unsigned int i = 0; i < _n_digits-2; i++) {
			unsigned int digit = hex%16;
			_operand += digit*std::pow(16,i);
			hex/=16;
		}

		// 0x [1][0000000] (operand 7 digits) means 0x1 with 0
		// 0x [10][000000] (opreand 6 digits) means 0x10 with 0
		if(_operand == 0 && _n_digits == 7)
			_opcode = 0x1;
		else
			_opcode = hex;
	}
}


std::string Disassembler::GetInstruction() const {
	std::string op;

	switch(_opcode) {
		case 0x1: 	op = "hlt"; 	break;
		case 0x10:	op = "in"; 		break;
		case 0x11: 	op = "inchar"; 	break;
		case 0x12:	op = "out"; 	break;
		case 0x13:	op = "outchar";	break;
		case 0x20:	op = "add";		break;
		case 0x21:	op = "sub";		break;
		case 0x22:	op = "mul";		break;
		case 0x23:	op = "div";		break;
		case 0x24: 	op = "mod";		break;
		case 0x25:	op = "neg";		break;
		case 0x32: 	op = "const #";	break;
		case 0x26:	op = "dup";		break;
		case 0x30:	op = "load";	break;
		case 0x31:	op = "store";	break;
		case 0x40:	op = "jmp #";	break;
		case 0x41:	op = "jeq #";	break;
		case 0x42:	op = "jne #";	break;
		case 0x43:	op = "jls #";	break;
		case 0x44:	op = "jle #";	break;
	}
	return op;
}

std::string Disassembler::PrintInstruction() const {
	std::string instruction = GetInstruction();

	std::string::size_type pos = instruction.find("#");
	if(pos != std::string::npos) {
		
		instruction.pop_back();
		instruction+= std::to_string(_operand);
	}

	return instruction;
}