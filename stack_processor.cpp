#include <iostream>


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

using instruction_in_t = unsigned int;


//lookup function

// has to store
// opcode
// operand
// provide functionality to split
class Instruction {
public:
	Instruction(const instruction_in_t in) 
	: _in(in) 
	{
		split();
	}

	/**
	Print human readable information
	*/
	void print(std::ostream& os) const {
		os << "---------------\n";
		os << "Instruction " << _in << "\n";
		os << "OpCode " << _opcode << "\n";
		os << "Operand " << _operand << "\n";
		os << "---------------";
		os << "\n";
	}
private:
	inline bool split();

private:
	instruction_in_t _in;
	int _opcode;
	int _operand;
};


std::ostream& operator<<(std::ostream& os, const Instruction& in) {
	in.print(os);
	return os;
}


bool Instruction::split() {

	std::cout << "splitting " << _in << std::endl;

	return true;
}

int main() {
	// std::string mode_input;
	// std::cin >> mode_input;

	// enum Mode {disassemble, simulation};

	// //1. figure out which we are in
	// if(mode_input == "disassemble") {
	// 	// enter disassemble mode
	// 	Mode current_mode = disassemble;
	// }

	//2. read number of instructions
	int n = 0;
	std::cin >> n;

	std::cin >> std::hex; // set input to hex mode

	for(int instruction_cnt = 0; instruction_cnt < n; instruction_cnt++) {
		unsigned int input; // incoming instruction
		std::cin >> input;
		Instruction in(input);
		//std::cout << in << std::endl;
	}
	//3. process the input 
	//3.1 for each input:
	//	decode the input
	// 	lookup the op code
	// 	output
	// 		
}