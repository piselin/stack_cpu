#include <iostream>
#include "gtest/gtest.h"
#include "disassembly.hpp"

class DisassemblyTest : public ::testing::Test {
protected:
	DisassemblyTest() {
		std::cout << "Ctor was called" << std::endl;
		foo = 3;
	}
	int foo;
};

TEST(DisassemblyTest, CountDigits) {
	EXPECT_EQ(1, CountDigits(0x1));
	EXPECT_EQ(3, CountDigits(0x321));
	EXPECT_EQ(8, CountDigits(0x3200000f));
	EXPECT_EQ(0, CountDigits(0));
}

TEST(DisassemblyTest, Decode) {
	unsigned int opcode = 0;
	unsigned int operand = 0;

	Decode(0x1, opcode, operand);
	EXPECT_EQ(opcode, 0x1);
	EXPECT_EQ(operand, 0x0);

	Decode(0, opcode, operand);
	EXPECT_EQ(opcode, 0x1);
	EXPECT_EQ(operand, 0);

	Decode(0x321, opcode, operand);
	EXPECT_EQ(0x32, opcode);
	EXPECT_EQ(1, operand);

	Decode(0x320103, opcode, operand);
	EXPECT_EQ(0x32, opcode);
	EXPECT_EQ(0x103, operand);

	Decode(0x3200000f, opcode, operand);
	EXPECT_EQ(0x32, opcode);
	EXPECT_EQ(0xf, operand);

	Decode(0x32ffffff, opcode, operand);
	EXPECT_EQ(0x32, opcode);
	EXPECT_EQ(0xffffff, operand);
}

TEST(DisassemblyTest, MapOpCodeToInstruction) {
	std::string op = "hlt";
	unsigned int opcode = 0;
	unsigned int operand = 0;
	Decode(0x1, opcode, operand);
	EXPECT_EQ(op, MapOpCodeToInstruction(opcode));

	EXPECT_EQ("dup", MapOpCodeToInstruction(0x26));

}
// TEST(DisassemblyTest, CheckInput) {
// 	const unsigned int input = 0x3200000f;
// 	EXPECT_TRUE(CheckInput(0x3200000f));
// 	EXPECT_TRUE((CheckInput(4294967295))); // theoretical max
// }

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}