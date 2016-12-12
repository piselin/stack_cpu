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
0x1000000
*/


// unsigned int Disassembler::CountDigits() {

// 	//unsigned int _n_digits = 0;
// 	unsigned int n = 0;
// 	instruction_t h = _hex_input; // working copy

// 	//const unsigned int kMaxNumberOfDigits = 10; // fixme pi: is this 8 or 10?

// 	for(unsigned int i = 0; (i < 8) && (h > 0); i++){
// 		//_n_digits++;
// 		n++;
// 		h/=16;
// 	}
// 	return n;
// }

void Disassembler::Decode(const instruction_t input) {
	// this assumes we have perfect input
	// note that 16777216 = 0x1000000

	// division by 0x1000000 (7 digits in total)
	// cuts off the last 6 digits, leaves the first 2
	_opcode = input / 16777216;

	// modulo with 0x1000000 (7 digits in total)
	// cuts off the first 2 digits, leaves the last 6
	_operand = input % 16777216;

	// two's complement:
	// if highest bit is set we have a negative number. 
	// we can thus compare _operand to the largest possible
	// positive number:
	// largest positive number with n bits is
	// 2^(n-1) - 1
	// for 24 bits this gives 8388607 = 0x7fffff

	if(_operand > 8388607)
		_operand -= 16777216;

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
		default:	op = "data 0x#"; break; // fixme pi: this is a problem! we don't change the output format to hex!
		// default: 	std::cout << "opcode does not exist: (" << _opcode << ")"<< std::endl;
		// 			assert(false); 	break;
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