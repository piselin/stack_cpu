#ifndef DISASSEMBLY_LIB
#define DISASSEMBLY_LIB

#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <string>


// largest number possible:
// 0xffffffff = 4294967295
const unsigned int kInputLimit = 0xffffffff;

unsigned int CountDigits(unsigned int h);

void Decode(unsigned int hex, unsigned int& opcode, unsigned int& operand);

std::string MapOpCodeToInstruction(const unsigned int input);

bool CheckInput(const unsigned int input);


#endif /* DISASSEMBLY_LIB */