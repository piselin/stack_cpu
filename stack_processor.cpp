#include <iostream>
#include <algorithm>
#include <string>

#include "disassembly.hpp"
#include "processor.hpp"

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

int main() {
    std::string command;
    std::cin >> command;

    // which mode are we in
    if (command == "disassemble") {
       
        // read number of instructions
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
			std::cout << d.GetInstruction() << std::endl;
		}
		std::cout << "end" << std::endl;
        
    } else if (command == "simulate") {

		// number of instructions
    	unsigned int n = 0;
		std::cin >> n;

		Processor virtual_cpu(n);
		virtual_cpu.Run();

    } else {
        std::cerr << "unkown command\n";
    }
}