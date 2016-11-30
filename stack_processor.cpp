#include <iostream>
#include <algorithm>
#include <string>

#include "disassembly.hpp"

/*
Disassembly: 
The program recieves the input in hexadecimal form and
translates it into human readable form

Simulation:
The program simulates a system consisting of
- processor
- memory
- input
- ouput
The simulated system will execute the machine instructions
(by applying their effect)


*/

// using instruction_in_t = unsigned int;

// class Instruction {
// public:
// 	Instruction(const instruction_in_t in) 
// 	: _in(in) 
// 	{
// 		//1. check the input
// 		check();
// 		//2. take it appart into opcode & operand
// 		split();
// 	}

// 	/**
// 	Print human readable information
// 	*/
// 	void print(std::ostream& os) const {
// 		os << "---------------\n";
// 		os << "Instruction " << _in << "\n";
// 		os << "OpCode " << _opcode << "\n";
// 		os << "Operand " << _operand << "\n";
// 		os << "---------------";
// 		os << "\n";
// 	}
// private:
// 	inline bool split();
// 	inline bool check();

// private:
// 	instruction_in_t _in;
// 	int _opcode;
// 	int _operand;
// };

// // wrapper to print an Instruction in an easy way
// std::ostream& operator<<(std::ostream& os, const Instruction& in) {
// 	in.print(os);
// 	return os;
// }

// bool Instruction::check() {
// 	return true;
// }

// bool Instruction::split() {

// 	std::cout << "splitting " << _in << std::endl;



// 	return true;
// }

// // test this with gtest
// std::string dec_to_hex(unsigned int dec) {
// 	const std::string hex_base = "0123456789abcdef";
// 	std::string hex;
// 	while(dec > 0) {
// 		unsigned int r = dec % 16;
// 		hex += hex_base[r];
// 		dec /= 16;
// 	}
// 	std::reverse(hex.begin(), hex.end());
// 	return hex;
// }

// unsigned int get_op_code(std::string hex) {
// 	unsigned int opcode = 0;
		
// 	// doesn't work...
// 	// opcode += std::stoi(hex[0])*16;
// 	// opcode += std::stoi(hex[1]);
// 	return opcode;
// }

int main()
{
    std::string command;
    std::cin >> command;

    // 1. which mode are we in
    if (command == "disassemble") {
       
        // 2. read number of instructions
		unsigned int n = 0;
		std::cin >> n;

		std::cin >> std::hex; // set input to hex mode
		Disassembler d;

		unsigned int hex = 0;
		for (unsigned int i = 0; i < n; i++) {

			// read
			std::cin >> hex;
			
			// extract commands
			d.Decode(hex);

			// output again
			std::cout << d.PrintInstruction() << std::endl;
		}
		std::cout << "end" << std::endl;
        
    } else if (command == "simulate") {
        
        // TODO: perform simulation task b)
        
    } else {
        std::cerr << "unkown command\n";
    }
}