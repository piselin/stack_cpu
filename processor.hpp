#ifndef PROCESSOR_LIB
#define PROCESSOR_LIB

#include <stack>
#include <vector>
#include <cassert>
#include "disassembly.hpp"

class Processor {
public:
	Processor(const unsigned int n) : _n_instructions(n), _memory(0,0) {
		SetUp();
	}

	void Run();

private:
	void SetUp();
	void Execute(const unsigned int opcode);
	unsigned int GetNextInstruction() const { return _memory[_pc]; }

private:
	Disassembler _d;
	unsigned int _pc{0};
	unsigned int _n_instructions{0};

	std::vector<unsigned int> _memory;
	std::stack<int> _stack;
};

#endif /* PROCESSOR_LIB */