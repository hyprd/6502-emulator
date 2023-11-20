#include <gtest/gtest.h>
#include "../src/6502.h"

class M6502TestSuite : public testing::Test {
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

TEST_F(M6502TestSuite, LDA_IMM) {
	InstructionCycles = 2;
	M6502.Memory[0xFFFC] = 0xA9;

	M6502.Memory[0xFFFD] = 0x42;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.A, 0x42);
	ASSERT_EQ(CyclesRan, InstructionCycles);
}

TEST_F(M6502TestSuite, LDA_ABS) {
	InstructionCycles = 4;
	M6502.Memory[0xFFFC] = 0xAD;

	M6502.Memory[0xFFFD] = 0xBC;
	M6502.Memory[0xFFFE] = 0xA1;

	M6502.Memory[0xBCA1] = 0x90;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.A, 0x90);
	ASSERT_EQ(CyclesRan, InstructionCycles);
}

TEST_F(M6502TestSuite, LDA_ABS_X) {
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

TEST_F(M6502TestSuite, LDA_ABS_Y) {
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

TEST_F(M6502TestSuite, LDA_ZP) {
	InstructionCycles = 3;
	M6502.Memory[0xFFFC] = 0xA5;
	M6502.Memory[0xFFFD] = 0x42;
	M6502.Memory[0x42] = 0x90;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.A, 0x90);
	ASSERT_EQ(CyclesRan, InstructionCycles);
}

TEST_F(M6502TestSuite, LDA_ZP_X) {
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

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}