#include "processor.hpp"


void Processor::SetUp() {
	unsigned int hex = 0;
	for(size_t i = 0; i < _n_instructions; i++) {
		std::cin >> std::hex >> hex;
		_memory.push_back(hex);
	}
}

void Processor::Run() {
	std::string op = "";
	while(op != "hlt") {
		
		// Fetch
		auto instruction = GetNextInstruction();
		
		// Decode
		_d.Decode(instruction);
		op = _d.GetInstruction();

		// Execute
		auto opcode = _d.GetOpcode();
		Execute(opcode);
	}
}


void Processor::Execute(const unsigned int opcode) {
	unsigned int c, l, v, r, m = 0;
	switch(opcode) {
		case 0x1: 	/*noting*/	 	break;
		case 0x10:	{
			std::cin >> std::dec >> v;
			_stack.push(v);
			_pc++;
			break;
		}
		case 0x11: 	{
			char k;
			std::cin >> k;
			_stack.push(k);
			_pc++;
			break;
		}
		case 0x12:	{
			v = _stack.top(); _stack.pop();
			std::cout << std::dec << v;
			_pc++;
			break;
		}
		case 0x13: 	{
			char k;
			k = _stack.top(); _stack.pop();
			std::cout << k;
			_pc++;
			break;
		}
		case 0x20:	{
			r = _stack.top(); _stack.pop();
			l = _stack.top(); _stack.pop();
			_stack.push(l+r);
			_pc++;
			break;
		}
		case 0x21:	{
			r = _stack.top(); _stack.pop();
			l = _stack.top(); _stack.pop();
			_stack.push(l-r);
			_pc++;
			break;
		}
		case 0x22:	{
			r = _stack.top(); _stack.pop();
			l = _stack.top(); _stack.pop();
			_stack.push(l*r);
			_pc++;
			break;
		}
		case 0x23:	{
			r = _stack.top(); _stack.pop();
			l = _stack.top(); _stack.pop();
			_stack.push(l/r);
			_pc++;
			break;
		}
		case 0x24: 	{
			r = _stack.top(); _stack.pop();
			l = _stack.top(); _stack.pop();
			_stack.push(l%r);
			_pc++;
			break;
		}
		case 0x25:	{
			r = _stack.top(); _stack.pop();
			_stack.push(-r);
			_pc++;
			break;
		}
		case 0x32: 	{
			c = _d.GetOperand();
			_stack.push(c);
			_pc++;
			break;
		}
		case 0x26:	{
			r = _stack.top(); _stack.pop();
			_stack.push(r); _stack.push(r);
			_pc++;
			break;
		}
		case 0x30:	{
			m = _stack.top(); _stack.pop();
			r = _memory[m];
			_stack.push(r);
			_pc++;
			break;
		}
		case 0x31:	{
			m = _stack.top(); _stack.pop();
			v = _stack.top(); _stack.pop();
			_memory[m] = v;
			_pc++;
			break;
		}
		case 0x40:	{
			c = _d.GetOperand();
			_pc = c;
			//std::cout <<" foo " << _pc << std::endl;
			break;
		}
		case 0x41:	{
			r = _stack.top(); _stack.pop();
			l = _stack.top(); _stack.pop();
			if(l == r)
				_pc = _d.GetOperand();
			else
				_pc++;
			break;
		}
		case 0x42:	{
			r = _stack.top(); _stack.pop();
			l = _stack.top(); _stack.pop();
			if(l != r)
				_pc = _d.GetOperand();
			else
				_pc++;
			break;
		}
		case 0x43:	{
			r = _stack.top(); _stack.pop();
			l = _stack.top(); _stack.pop();
			if(l < r)
				_pc = _d.GetOperand();
			else
				_pc++;
			break;
		}
		case 0x44:	{
			r = _stack.top(); _stack.pop();
			l = _stack.top(); _stack.pop();
			if(l <= r)
				_pc = _d.GetOperand();
			else
				_pc++;
			break;
		}
		default: assert(false); break;
	}
}