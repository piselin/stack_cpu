#include <iostream>
#include "gtest/gtest.h"
#include "disassembly.hpp"

class DisassemblyTest : public ::testing::Test {
protected:
	virtual void SetUp() {}

	Disassembler d;
};

// TEST_F(DisassemblyTest, CountDigits) {
	
// 	EXPECT_EQ(1, d.CountDigits(0x1));
// 	EXPECT_EQ(3, d.CountDigits(0x321));
// 	EXPECT_EQ(8, d.CountDigits(0x3200000f));
// 	EXPECT_EQ(0, d.CountDigits(0));
// }

TEST_F(DisassemblyTest, Decode) {

	// d.Decode(0);
	// EXPECT_EQ(d.GetOpcode(),	0x1);
	// EXPECT_EQ(d.GetOperand(),	0x0);

	// d.Decode(0x1);
	// EXPECT_EQ(d.GetOpcode(), 	0x1);
	// EXPECT_EQ(d.GetOperand(), 	0x0);

	// [10][000000] means opcode 0x10
	d.Decode(0x10000000);
	EXPECT_EQ(d.GetOpcode(),	0x10);
	EXPECT_EQ(d.GetOperand(),	0x0);

	// // [1][000] means opcode 0x1
	// d.Decode(0x1000);
	// EXPECT_EQ(d.GetOpcode(),	0x1);
	// EXPECT_EQ(d.GetOperand(),	0x0);

	// [1][0000000] means opcode 0x1
	d.Decode(0x1000000);
	EXPECT_EQ(d.GetOpcode(),	0x1);
	EXPECT_EQ(d.GetOperand(),	0x0);

	// d.Decode(0x321);
	// EXPECT_EQ(d.GetOpcode(), 0x32);
	// EXPECT_EQ(d.GetOperand(), 0x1);

	// d.Decode(0x320103);
	// EXPECT_EQ(d.GetOpcode(), 0x32);
	// EXPECT_EQ(d.GetOperand(), 0x103);

	d.Decode(0x3200000f);
	EXPECT_EQ(d.GetOpcode(), 0x32);
	EXPECT_EQ(d.GetOperand(), 0xf);

	d.Decode(0x32ffffff);
	EXPECT_EQ(d.GetOpcode(), 0x32);
	EXPECT_EQ(d.GetOperand(), -1);

	d.Decode(0x327fffff);
	EXPECT_EQ(d.GetOpcode(), 0x32);
	EXPECT_EQ(d.GetOperand(), 8388607);

	// 8388608, so we have 0x800000 - 2^24 = -8388608
	d.Decode(0x32800000);
	EXPECT_EQ(d.GetOpcode(), 0x32);
	EXPECT_EQ(d.GetOperand(), -8388608);

	d.Decode(0x32400000);
	EXPECT_EQ(d.GetOpcode(), 0x32);
	EXPECT_EQ(d.GetOperand(), 4194304);

	d.Decode(0x12000000);
	EXPECT_EQ(d.GetOpcode(), 0x12);
	EXPECT_EQ(d.GetOperand(), 0);
	
}

TEST_F(DisassemblyTest, MapOpCodeToInstruction) {
	d.Decode(0x1000000);
	EXPECT_EQ("hlt", d.GetInstruction());
	
	d.Decode(0x10000000);
	EXPECT_EQ("in", d.GetInstruction());

	d.Decode(0x26000000);
	EXPECT_EQ("dup", d.GetInstruction());

	d.Decode(0x40000001);
	EXPECT_EQ("jmp 1", d.GetInstruction());

	d.Decode(0xa);
	EXPECT_EQ("data 0xa", d.GetInstruction());

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