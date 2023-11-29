#include <gtest/gtest.h>
#include "../src/6502.h"

class M6502ShiftTestSuite : public testing::Test {
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

TEST_F(M6502ShiftTestSuite, ASL_A) {
	InstructionCycles = 2;
	M6502.Memory[0xFFFC] = 0x0A;

	M6502.A = 0x7C;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.A, 0xF8);
}

TEST_F(M6502ShiftTestSuite, ASL_ZP) {
	InstructionCycles = 5;
	M6502.Memory[0xFFFC] = 0x06;

	M6502.Memory[0xFFFD] = 0x42;
	M6502.Memory[0x42] = 0x7C;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.Memory[0x42], 0xF8);
}

TEST_F(M6502ShiftTestSuite, ASL_ZP_X) {
	InstructionCycles = 6;
	M6502.Memory[0xFFFC] = 0x16;

	M6502.Memory[0xFFFD] = 0x42;
	M6502.X = 0x01;
	M6502.Memory[0x43] = 0x7C;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.Memory[0x43], 0xF8);
}


TEST_F(M6502ShiftTestSuite, ASL_ABS) {
	InstructionCycles = 6;
	M6502.Memory[0xFFFC] = 0x0E;

	M6502.Memory[0xFFFD] = 0xBD;
	M6502.Memory[0xFFFE] = 0xBD;
	M6502.Memory[0xBDBD] = 0x7C;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.Memory[0xBDBD], 0xF8);
}

TEST_F(M6502ShiftTestSuite, ASL_ABS_X) {
	InstructionCycles = 7;
	M6502.Memory[0xFFFC] = 0x1E;

	M6502.Memory[0xFFFD] = 0xBD;
	M6502.Memory[0xFFFE] = 0xBD;
	M6502.X = 0x01;
	M6502.Memory[0xBDBE] = 0x7C;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.Memory[0xBDBE], 0xF8);
}

TEST_F(M6502ShiftTestSuite, LSR_A) {
	InstructionCycles = 2;
	M6502.Memory[0xFFFC] = 0x4A;

	M6502.A = 0x8D;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.A, 0x46);
}

TEST_F(M6502ShiftTestSuite, LSR_ZP) {
	InstructionCycles = 5;
	M6502.Memory[0xFFFC] = 0x46;

	M6502.Memory[0xFFFD] = 0x42;
	M6502.Memory[0x42] = 0x8D;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.Memory[0x42], 0x46);
}

TEST_F(M6502ShiftTestSuite, LSR_ZP_X) {
	InstructionCycles = 6;
	M6502.Memory[0xFFFC] = 0x56;

	M6502.Memory[0xFFFD] = 0x42;
	M6502.X = 0x01;
	M6502.Memory[0x43] = 0x8D;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.Memory[0x43], 0x46);
}

TEST_F(M6502ShiftTestSuite, LSR_ABS) {
	InstructionCycles = 6;
	M6502.Memory[0xFFFC] = 0x4E;

	M6502.Memory[0xFFFD] = 0xBD;
	M6502.Memory[0xFFFE] = 0xBD;
	M6502.Memory[0xBDBD] = 0x8D;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.Memory[0xBDBD], 0x46);
}

TEST_F(M6502ShiftTestSuite, LSR_ABS_X) {
	InstructionCycles = 7;
	M6502.Memory[0xFFFC] = 0x5E;

	M6502.Memory[0xFFFD] = 0xBD;
	M6502.Memory[0xFFFE] = 0xBD;
	M6502.X = 0x01;
	M6502.Memory[0xBDBE] = 0x8D;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.Memory[0xBDBE], 0x46);
}

TEST_F(M6502ShiftTestSuite, ROL_A) {
	InstructionCycles = 2;
	M6502.Memory[0xFFFC] = 0x2A;

	M6502.A = 0x8D;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.A, 0x1B);
}

TEST_F(M6502ShiftTestSuite, ROL_ZP) {
	InstructionCycles = 5;
	M6502.Memory[0xFFFC] = 0x26;

	M6502.Memory[0xFFFD] = 0x42;
	M6502.Memory[0x42] = 0x8D;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.Memory[0x42], 0x1B);
}

TEST_F(M6502ShiftTestSuite, ROL_ZP_X) {
	InstructionCycles = 6;
	M6502.Memory[0xFFFC] = 0x36;

	M6502.Memory[0xFFFD] = 0x42;
	M6502.X = 0x01;
	M6502.Memory[0x43] = 0x8D;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.Memory[0x43], 0x1B);
}

TEST_F(M6502ShiftTestSuite, ROL_ABS) {
	InstructionCycles = 6;
	M6502.Memory[0xFFFC] = 0x2E;

	M6502.Memory[0xFFFD] = 0xBD;
	M6502.Memory[0xFFFE] = 0xBD;
	M6502.Memory[0xBDBD] = 0x8D;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.Memory[0xBDBD], 0x1B);
}

TEST_F(M6502ShiftTestSuite, ROL_ABS_X) {
	InstructionCycles = 7;
	M6502.Memory[0xFFFC] = 0x3E;

	M6502.Memory[0xFFFD] = 0xBD;
	M6502.Memory[0xFFFE] = 0xBD;
	M6502.X = 0x01;
	M6502.Memory[0xBDBE] = 0x8D;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.Memory[0xBDBE], 0x1B);
}

TEST_F(M6502ShiftTestSuite, ROR_A) {
	InstructionCycles = 2;
	M6502.Memory[0xFFFC] = 0x6A;

	M6502.A = 0x8D;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.A, 0xC6);
}

TEST_F(M6502ShiftTestSuite, ROR_ZP) {
	InstructionCycles = 5;
	M6502.Memory[0xFFFC] = 0x66;

	M6502.Memory[0xFFFD] = 0x42;
	M6502.Memory[0x42] = 0x8D;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.Memory[0x42], 0xC6);
}

TEST_F(M6502ShiftTestSuite, ROR_ZP_X) {
	InstructionCycles = 6;
	M6502.Memory[0xFFFC] = 0x76;

	M6502.Memory[0xFFFD] = 0x42;
	M6502.X = 0x01;
	M6502.Memory[0x43] = 0x8D;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.Memory[0x43], 0xC6);
}

TEST_F(M6502ShiftTestSuite, ROR_ABS) {
	InstructionCycles = 6;
	M6502.Memory[0xFFFC] = 0x6E;

	M6502.Memory[0xFFFD] = 0xBD;
	M6502.Memory[0xFFFE] = 0xBD;
	M6502.Memory[0xBDBD] = 0x8D;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.Memory[0xBDBD], 0xC6);
}

TEST_F(M6502ShiftTestSuite, ROR_ABS_X) {
	InstructionCycles = 7;
	M6502.Memory[0xFFFC] = 0x7E;

	M6502.Memory[0xFFFD] = 0xBD;
	M6502.Memory[0xFFFE] = 0xBD;
	M6502.X = 0x01;
	M6502.Memory[0xBDBE] = 0x8D;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.Memory[0xBDBE], 0xC6);
}

