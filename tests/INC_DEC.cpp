#include <gtest/gtest.h>
#include "../src/6502.h"

class M6502IncDecTestSuite : public testing::Test {
public:
	NMOS6502 M6502;
	u32 InstructionCycles = 0;
	u32 CyclesRan = 0;

	virtual void SetUp() {
		M6502.Reset();
	}

	virtual void TearDown() {
		ASSERT_EQ(CyclesRan, InstructionCycles);
	}
};

TEST_F(M6502IncDecTestSuite, DEC_ZP) {
	InstructionCycles = 5;
	M6502.Memory[0xFFFC] = 0xC6;

	M6502.Memory[0xFFFD] = 0x42;
	M6502.Memory[0x42] = 0x10;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.Memory[0x42], 0x0F);
}

TEST_F(M6502IncDecTestSuite, DEC_ZP_X) {
	InstructionCycles = 6;
	M6502.Memory[0xFFFC] = 0xD6;

	M6502.Memory[0xFFFD] = 0x42;
	M6502.X = 0x01;
	M6502.Memory[0x43] = 0x10;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.Memory[0x43], 0x0F);
}

TEST_F(M6502IncDecTestSuite, DEC_ABS) {
	InstructionCycles = 6;
	M6502.Memory[0xFFFC] = 0xCE;

	M6502.Memory[0xFFFD] = 0xC1;
	M6502.Memory[0xFFFE] = 0xC0;
	M6502.Memory[0xC1C0] = 0x10;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.Memory[0xC1C0], 0x0F);
}

TEST_F(M6502IncDecTestSuite, DEC_ABS_X) {
	InstructionCycles = 7;
	M6502.Memory[0xFFFC] = 0xDE;

	M6502.Memory[0xFFFD] = 0xC1;
	M6502.Memory[0xFFFE] = 0xC0;
	M6502.X = 0x01;
	M6502.Memory[0xC1C1] = 0x10;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.Memory[0xC1C1], 0x0F);
}

TEST_F(M6502IncDecTestSuite, DEX) {
	InstructionCycles = 2;
	M6502.Memory[0xFFFC] = 0xCA;

	M6502.X = 0x02;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.X, 0x01);
}

TEST_F(M6502IncDecTestSuite, DEY) {
	InstructionCycles = 2;
	M6502.Memory[0xFFFC] = 0x88;

	M6502.Y = 0x02;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.Y, 0x01);
}

TEST_F(M6502IncDecTestSuite, INC_ZP) {
	InstructionCycles = 5;
	M6502.Memory[0xFFFC] = 0xE6;

	M6502.Memory[0xFFFD] = 0x42;
	M6502.Memory[0x42] = 0x0E;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.Memory[0x42], 0x0F);
}

TEST_F(M6502IncDecTestSuite, INC_ZP_X) {
	InstructionCycles = 6;
	M6502.Memory[0xFFFC] = 0xF6;

	M6502.Memory[0xFFFD] = 0x42;
	M6502.X = 0x01;
	M6502.Memory[0x43] = 0x0E;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.Memory[0x43], 0x0F);
}

TEST_F(M6502IncDecTestSuite, INC_ABS) {
	InstructionCycles = 6;
	M6502.Memory[0xFFFC] = 0xEE;

	M6502.Memory[0xFFFD] = 0xC1;
	M6502.Memory[0xFFFE] = 0xC0;
	M6502.Memory[0xC1C0] = 0x0E;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.Memory[0xC1C0], 0x0F);
}

TEST_F(M6502IncDecTestSuite, INC_ABS_X) {
	InstructionCycles = 7;
	M6502.Memory[0xFFFC] = 0xFE;

	M6502.Memory[0xFFFD] = 0xC1;
	M6502.Memory[0xFFFE] = 0xC0;
	M6502.X = 0x01;
	M6502.Memory[0xC1C1] = 0x0E;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.Memory[0xC1C1], 0x0F);
}

TEST_F(M6502IncDecTestSuite, INX) {
	InstructionCycles = 2;
	M6502.Memory[0xFFFC] = 0xE8;

	M6502.X = 0x01;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.X, 0x02);
}

TEST_F(M6502IncDecTestSuite, INY) {
	InstructionCycles = 2;
	M6502.Memory[0xFFFC] = 0xC8;

	M6502.Y = 0x01;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.Y, 0x02);
}