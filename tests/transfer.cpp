#include <gtest/gtest.h>
#include "../src/6502.h"

class M6502TransferTestSuite : public testing::Test {
public:
	NMOS6502 M6502;
	u32 InstructionCycles = 0;
	u32 CyclesRan = 0;

	virtual void SetUp() {
		M6502.Reset();
	}

	virtual void TearDown() {
	}
};

TEST_F(M6502TransferTestSuite, LDA_IMM) {
	InstructionCycles = 2;
	M6502.Memory[0xFFFC] = 0xA9;

	M6502.Memory[0xFFFD] = 0x42;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.A, 0x42);
	ASSERT_EQ(CyclesRan, InstructionCycles);
}

TEST_F(M6502TransferTestSuite, LDA_ABS) {
	InstructionCycles = 4;
	M6502.Memory[0xFFFC] = 0xAD;

	M6502.Memory[0xFFFD] = 0xBC;
	M6502.Memory[0xFFFE] = 0xA1;

	M6502.Memory[0xBCA1] = 0x90;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.A, 0x90);
	ASSERT_EQ(CyclesRan, InstructionCycles);
}

TEST_F(M6502TransferTestSuite, LDA_ABS_X) {
	InstructionCycles = 5;
	M6502.Memory[0xFFFC] = 0xBD;
	M6502.X = 0x01;

	/* Test page boundary being crossed */
	M6502.Memory[0xFFFD] = 0xF2;
	M6502.Memory[0xFFFE] = 0xFF;
	M6502.Memory[0xF300] = 0x90;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.A, 0x90);
	ASSERT_EQ(CyclesRan, InstructionCycles);

	/* Test page boundary not being crossed */
	M6502.PC = 0xFFFC;
	M6502.Memory[0xFFFE] = 0x98;
	M6502.Memory[0xF299] = 0x87;
	CyclesRan = M6502.Execute(InstructionCycles - 1);
	ASSERT_EQ(M6502.A, 0x87);
	ASSERT_EQ(CyclesRan, InstructionCycles - 1);
}

TEST_F(M6502TransferTestSuite, LDA_ABS_Y) {
	InstructionCycles = 5;
	M6502.Memory[0xFFFC] = 0xB9;
	M6502.Y = 0x01;

	/* Test page boundary being crossed */
	M6502.Memory[0xFFFD] = 0xF2;
	M6502.Memory[0xFFFE] = 0xFF;
	M6502.Memory[0xF300] = 0x90;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.A, 0x90);
	ASSERT_EQ(CyclesRan, InstructionCycles);

	/* Test page boundary not being crossed */
	M6502.PC = 0xFFFC;
	M6502.Memory[0xFFFE] = 0x98;
	M6502.Memory[0xF299] = 0x87;
	CyclesRan = M6502.Execute(InstructionCycles - 1);
	ASSERT_EQ(M6502.A, 0x87);
	ASSERT_EQ(CyclesRan, InstructionCycles - 1);
}

TEST_F(M6502TransferTestSuite, LDA_ZP) {
	InstructionCycles = 3;
	M6502.Memory[0xFFFC] = 0xA5;
	M6502.Memory[0xFFFD] = 0x42;
	M6502.Memory[0x42] = 0x90;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.A, 0x90);
	ASSERT_EQ(CyclesRan, InstructionCycles);
}

TEST_F(M6502TransferTestSuite, LDA_ZP_X) {
	InstructionCycles = 4;
	M6502.Memory[0xFFFC] = 0xB5;

	/* Test address overflowing 0xFF */
	M6502.Memory[0xFFFD] = 0xFE;
	M6502.X = 0x10;
	M6502.Memory[0x0E] = 0x42;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.A, 0x42);

	/* Test address not overflowing 0xFF */
	M6502.PC = 0xFFFC;
	M6502.X = 0x01;
	M6502.Memory[0xFF] = 0x42;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.A, 0x42);
	ASSERT_EQ(CyclesRan, InstructionCycles);
}

TEST_F(M6502TransferTestSuite, LDA_IND_X) {
	InstructionCycles = 6;
	M6502.Memory[0xFFFC] = 0xA1;

	M6502.Memory[0xFFFD] = 0xF0;
	M6502.X = 0x01;
	M6502.Memory[0xF1] = 0xAA;
	M6502.Memory[0xF2] = 0x0A;
	M6502.Memory[0x0AAA] = 0x90;

	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.A, 0x90);
	ASSERT_EQ(CyclesRan, InstructionCycles);
}

TEST_F(M6502TransferTestSuite, LDA_IND_Y) {
	InstructionCycles = 6;
	M6502.Memory[0xFFFC] = 0xB1;

	/* Test for page boundary being crossed */
	M6502.Memory[0xFFFD] = 0x42;
	M6502.Memory[0x42] = 0xFF;
	M6502.Memory[0x43] = 0x01;
	M6502.Y = 0x01;
	M6502.Memory[0x200] = 0x90;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.A, 0x90);
	ASSERT_EQ(CyclesRan, InstructionCycles);

	/* Test for page boundary not being crossed */
	M6502.PC = 0xFFFC;
	M6502.Memory[0x42] = 0xF1;
	M6502.Memory[0x43] = 0x10;
	M6502.Memory[0x10F2] = 0x90;
	CyclesRan = M6502.Execute(InstructionCycles - 1);
	ASSERT_EQ(M6502.A, 0x90);
	ASSERT_EQ(CyclesRan, InstructionCycles - 1);
}

TEST_F(M6502TransferTestSuite, LDX_IMM) {
	InstructionCycles = 2;
	M6502.Memory[0xFFFC] = 0xA2;

	M6502.Memory[0xFFFD] = 0x42;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.X, 0x42);
	ASSERT_EQ(CyclesRan, InstructionCycles);
}

TEST_F(M6502TransferTestSuite, LDX_ZP) {
	InstructionCycles = 3;
	M6502.Memory[0xFFFC] = 0xA6;

	M6502.Memory[0xFFFD] = 0x42;
	M6502.Memory[0x42] = 0x90;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.X, 0x90);
	ASSERT_EQ(CyclesRan, InstructionCycles);
}

TEST_F(M6502TransferTestSuite, LDX_ZP_Y) {
	InstructionCycles = 4;
	M6502.Memory[0xFFFC] = 0xB6;

	M6502.Y = 0x01;
	M6502.Memory[0xFFFD] = 0x42;
	M6502.Memory[0x43] = 0x90;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.X, 0x90);
	ASSERT_EQ(CyclesRan, InstructionCycles);
}

TEST_F(M6502TransferTestSuite, LDX_ABS) {
	InstructionCycles = 4;
	M6502.Memory[0xFFFC] = 0xAE;

	M6502.Memory[0xFFFD] = 0xBC;
	M6502.Memory[0xFFFE] = 0xA1;

	M6502.Memory[0xBCA1] = 0x90;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.X, 0x90);
	ASSERT_EQ(CyclesRan, InstructionCycles);
	
}

TEST_F(M6502TransferTestSuite, LDX_ABS_Y) {
	InstructionCycles = 5;
	M6502.Memory[0xFFFC] = 0xBE;
	M6502.Y = 0x01;

	/* Test page boundary being crossed */
	M6502.Memory[0xFFFD] = 0xF2;
	M6502.Memory[0xFFFE] = 0xFF;
	M6502.Memory[0xF300] = 0x90;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.X, 0x90);
	ASSERT_EQ(CyclesRan, InstructionCycles);

	/* Test page boundary not being crossed */
	M6502.PC = 0xFFFC;
	M6502.Memory[0xFFFE] = 0x98;
	M6502.Memory[0xF299] = 0x87;
	CyclesRan = M6502.Execute(InstructionCycles - 1);
	ASSERT_EQ(M6502.X, 0x87);
	ASSERT_EQ(CyclesRan, InstructionCycles - 1);
}

TEST_F(M6502TransferTestSuite, LDY_IMM) {
	InstructionCycles = 2;
	M6502.Memory[0xFFFC] = 0xA0;

	M6502.Memory[0xFFFD] = 0x42;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.Y, 0x42);
	ASSERT_EQ(CyclesRan, InstructionCycles);
}

TEST_F(M6502TransferTestSuite, LDY_ZP) {
	InstructionCycles = 3;
	M6502.Memory[0xFFFC] = 0xA4;

	M6502.Memory[0xFFFD] = 0x42;
	M6502.Memory[0x42] = 0x90;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.Y, 0x90);
	ASSERT_EQ(CyclesRan, InstructionCycles);
}

TEST_F(M6502TransferTestSuite, LDY_ZP_X) {
	InstructionCycles = 4;
	M6502.Memory[0xFFFC] = 0xB4;

	M6502.X = 0x01;
	M6502.Memory[0xFFFD] = 0x42;
	M6502.Memory[0x43] = 0x90;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.Y, 0x90);
	ASSERT_EQ(CyclesRan, InstructionCycles);
}

TEST_F(M6502TransferTestSuite, LDY_ABS) {
	InstructionCycles = 4;
	M6502.Memory[0xFFFC] = 0xAC;

	M6502.Memory[0xFFFD] = 0xBC;
	M6502.Memory[0xFFFE] = 0xA1;

	M6502.Memory[0xBCA1] = 0x90;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.Y, 0x90);
	ASSERT_EQ(CyclesRan, InstructionCycles);

}

TEST_F(M6502TransferTestSuite, LDY_ABS_X) {
	InstructionCycles = 5;
	M6502.Memory[0xFFFC] = 0xBC;
	M6502.X = 0x01;

	/* Test page boundary being crossed */
	M6502.Memory[0xFFFD] = 0xF2;
	M6502.Memory[0xFFFE] = 0xFF;
	M6502.Memory[0xF300] = 0x90;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.Y, 0x90);
	ASSERT_EQ(CyclesRan, InstructionCycles);

	/* Test page boundary not being crossed */
	M6502.PC = 0xFFFC;
	M6502.Memory[0xFFFE] = 0x98;
	M6502.Memory[0xF299] = 0x87;
	CyclesRan = M6502.Execute(InstructionCycles - 1);
	ASSERT_EQ(M6502.Y, 0x87);
	ASSERT_EQ(CyclesRan, InstructionCycles - 1);
}
