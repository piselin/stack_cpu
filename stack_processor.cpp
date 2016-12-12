#include <iostream>
#include <algorithm>
#include <string>
#include <stack>
#include <vector>

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

int main() {
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
			std::cout << d.GetInstruction() << std::endl;
		}
		std::cout << "end" << std::endl;
        
    } else if (command == "simulate") {


		// 1. Set up Initial State
    	
		
    	unsigned int n = 0;
		std::cin >> n;

		unsigned int hex = 0;
		std::vector<unsigned int> memory(0,0);
		for(size_t i = 0; i < n; i++) {
			std::cin >> std::hex >> hex;
			memory.push_back(hex);
		}

		std::stack<int> stack;
		unsigned int pc = 0;
		Disassembler d;

		std::string op = "";
    
   		while(op != "hlt") {
   			// Fetch
   			unsigned int instruction = memory[pc];

   			// Decode
   			d.Decode(instruction);
   			op = d.GetInstruction();

   			// Execute Instruction
   			unsigned int opcode = d.GetOpcode();

   			unsigned int c, l, v, r, m = 0;

   			switch(opcode) {
				case 0x1: 	/*noting*/	 	break;
				case 0x10:	{
					std::cin >> std::dec >> v;
					stack.push(v);
					pc++;
					break;
				}
				case 0x11: 	{
					char k;
					std::cin >> k;
					stack.push(k);
					pc++;
					break;
				}
				case 0x12:	{
					v = stack.top(); stack.pop();
					std::cout << std::dec << v;
					pc++;
					break;
				}
				case 0x13: 	{
					char k;
					k = stack.top(); stack.pop();
					std::cout << k;
					pc++;
					break;
				}
				case 0x20:	{
					r = stack.top(); stack.pop();
					l = stack.top(); stack.pop();
					stack.push(l+r);
					pc++;
					break;
				}
				case 0x21:	{
					r = stack.top(); stack.pop();
					l = stack.top(); stack.pop();
					stack.push(l-r);
					pc++;
					break;
				}
				case 0x22:	{
					r = stack.top(); stack.pop();
					l = stack.top(); stack.pop();
					stack.push(l*r);
					pc++;
					break;
				}
				case 0x23:	{
					r = stack.top(); stack.pop();
					l = stack.top(); stack.pop();
					stack.push(l/r);
					pc++;
					break;
				}
				case 0x24: 	{
					r = stack.top(); stack.pop();
					l = stack.top(); stack.pop();
					stack.push(l%r);
					pc++;
					break;
				}
				case 0x25:	{
					r = stack.top(); stack.pop();
					stack.push(-r);
					pc++;
					break;
				}
				case 0x32: 	{
					c = d.GetOperand();
					stack.push(c);
					pc++;
					break;
				}
				case 0x26:	{
					r = stack.top(); stack.pop();
					stack.push(r); stack.push(r);
					pc++;
					break;
				}
				case 0x30:	{
					m = stack.top(); stack.pop();
					r = memory[m];
					stack.push(r);
					pc++;
					break;
				}
				case 0x31:	{
					m = stack.top(); stack.pop();
					v = stack.top(); stack.pop();
					memory[m] = v;
					pc++;
					break;
				}
				case 0x40:	{
					c = d.GetOperand();
					pc = c;
					//std::cout <<" foo " << pc << std::endl;
					break;
				}
				case 0x41:	{
					r = stack.top(); stack.pop();
					l = stack.top(); stack.pop();
					if(l == r)
						pc = d.GetOperand();
					else
						pc++;
					break;
				}
				case 0x42:	{
					r = stack.top(); stack.pop();
					l = stack.top(); stack.pop();
					if(l != r)
						pc = d.GetOperand();
					else
						pc++;
					break;
				}
				case 0x43:	{
					r = stack.top(); stack.pop();
					l = stack.top(); stack.pop();
					if(l < r)
						pc = d.GetOperand();
					else
						pc++;
					break;
				}
				case 0x44:	{
					r = stack.top(); stack.pop();
					l = stack.top(); stack.pop();
					if(l <= r)
						pc = d.GetOperand();
					else
						pc++;
					break;
				}
				default: assert(false); break;
			}
   		}
    } else {
        std::cerr << "unkown command\n";
    }
}