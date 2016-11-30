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


unsigned int CountDigits(unsigned int h) {
	unsigned int n_digits = 0;
	for(unsigned int i = 0; (i < 8) && (h > 0); i++){
		n_digits++;
		h/=16;
	}
	return n_digits;
}

void Decode(unsigned int hex, unsigned int& opcode, unsigned int& operand) {

	const unsigned int n_digits = CountDigits(hex);

	opcode = 0x1; // default
	operand = 0x0;

	if (n_digits == 0) {
		// nothing
	} else if(n_digits == 1) {
		if(hex == 0x1) {
			opcode = hex;
		} else {
			assert(false); // some crap happened!
		}
	} else if(n_digits == 2) {
		opcode = hex;
	} else {
		for(unsigned int i = 0; i < n_digits-2; i++) {
			unsigned int digit = hex%16;
			operand += digit*std::pow(16,i);
			hex/=16;
		}
		opcode = hex;
	}
}

bool CheckInput(const unsigned int input) {
	std::cout << "in " << input << std::endl;
	std::cout << input / kInputLimit << std::endl;
	return (input / kInputLimit <= 1);
}

std::string MapOpCodeToInstruction(const unsigned int input) {
	std::string op;
	
	switch(input) {
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
		case 0x32: 	op = "const c";	break;
		case 0x26:	op = "dup";		break;
		case 0x30:	op = "load";	break;
		case 0x31:	op = "store";	break;
		case 0x40:	op = "jmp c";	break;
		case 0x41:	op = "jeq c";	break;
		case 0x42:	op = "jne c";	break;
		case 0x43:	op = "jls c";	break;
		case 0x44:	op = "jle c";	break;
	}
	return op;
}