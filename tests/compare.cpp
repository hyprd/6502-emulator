#include <gtest/gtest.h>
#include "../src/6502.h"

class M6502CompareTestSuite : public testing::Test {
public:
	NMOS6502 M6502;
	u32 InstructionCycles = 0;
	u32 CyclesRan = 0;

	virtual void SetUp() {
		M6502.Reset();
	}

	virtual void TearDown() {
	}

	void TestCompare(u8 *Register) {
		/* Register < Operand */
		M6502.ProcessorStatus.reset();
		*Register = 0x00;
		CyclesRan = M6502.Execute(InstructionCycles);
		ASSERT_EQ(M6502.ProcessorStatus[M6502.Z], 0);
		ASSERT_EQ(M6502.ProcessorStatus[M6502.C], 0);
		ASSERT_EQ(M6502.ProcessorStatus[M6502.N], 1);
		
		/* Register = Operand */
		M6502.PC = 0xFFFC;
		M6502.ProcessorStatus.reset();
		*Register = 0x20;
		CyclesRan = M6502.Execute(InstructionCycles);
		ASSERT_EQ(M6502.ProcessorStatus[M6502.Z], 1);
		ASSERT_EQ(M6502.ProcessorStatus[M6502.C], 1);
		ASSERT_EQ(M6502.ProcessorStatus[M6502.N], 0);
		
		/* Register > Operand */
		M6502.PC = 0xFFFC;
		M6502.ProcessorStatus.reset();
		*Register = 0x21;
		CyclesRan = M6502.Execute(InstructionCycles);
		ASSERT_EQ(M6502.ProcessorStatus[M6502.Z], 0);
		ASSERT_EQ(M6502.ProcessorStatus[M6502.C], 1);
		ASSERT_EQ(M6502.ProcessorStatus[M6502.N], 0);
	}
};

TEST_F(M6502CompareTestSuite, CMP_IMM) {
	InstructionCycles = 2;
	M6502.Memory[0xFFFC] = 0xC9;

	M6502.Memory[0xFFFD] = 0x20;
	TestCompare(&M6502.A);
	ASSERT_EQ(CyclesRan, InstructionCycles);
}

TEST_F(M6502CompareTestSuite, CMP_ZP) {
	InstructionCycles = 3;
	M6502.Memory[0xFFFC] = 0xC5;

	M6502.Memory[0xFFFD] = 0x42;
	M6502.Memory[0x42] = 0x20;
	TestCompare(&M6502.A);
	ASSERT_EQ(CyclesRan, InstructionCycles);
}

TEST_F(M6502CompareTestSuite, CMP_ZP_X) {
	InstructionCycles = 4;
	M6502.Memory[0xFFFC] = 0xD5;

	M6502.Memory[0xFFFD] = 0x42;
	M6502.X = 0x01;
	M6502.Memory[0x43] = 0x20;
	TestCompare(&M6502.A);
	ASSERT_EQ(CyclesRan, InstructionCycles);
}

TEST_F(M6502CompareTestSuite, CMP_ABS) {
	InstructionCycles = 4;
	M6502.Memory[0xFFFC] = 0xCD;

	M6502.Memory[0xFFFD] = 0xA0;
	M6502.Memory[0xFFFE] = 0xB0;
	M6502.Memory[0xA0B0] = 0x20;
	TestCompare(&M6502.A);
	ASSERT_EQ(CyclesRan, InstructionCycles);
}

TEST_F(M6502CompareTestSuite, CMP_ABS_X) {
	InstructionCycles = 5;
	M6502.Memory[0xFFFC] = 0xDD;

	/* Page boundary crossed */
	M6502.Memory[0xFFFD] = 0xA0;
	M6502.Memory[0xFFFE] = 0xFF;
	M6502.X = 0x01;
	M6502.Memory[0xA100] = 0x20;
	TestCompare(&M6502.A);
	ASSERT_EQ(CyclesRan, InstructionCycles);

	/* Page boundary not crossed */
	M6502.PC = 0xFFFC;
	M6502.Memory[0xFFFE] = 0xFE;
	M6502.Memory[0xA0FF] = 0x20;
	TestCompare(&M6502.A);
	ASSERT_EQ(CyclesRan, InstructionCycles - 1);
}

TEST_F(M6502CompareTestSuite, CMP_ABS_Y) {
	InstructionCycles = 5;
	M6502.Memory[0xFFFC] = 0xD9;

	/* Page boundary crossed */
	M6502.Memory[0xFFFD] = 0xA0;
	M6502.Memory[0xFFFE] = 0xFF;
	M6502.Y = 0x01;
	M6502.Memory[0xA100] = 0x20;
	TestCompare(&M6502.A);
	ASSERT_EQ(CyclesRan, InstructionCycles);

	/* Page boundary not crossed */
	M6502.PC = 0xFFFC;
	M6502.Memory[0xFFFE] = 0xFE;
	M6502.Memory[0xA0FF] = 0x20;
	TestCompare(&M6502.A);
	ASSERT_EQ(CyclesRan, InstructionCycles - 1);
}

TEST_F(M6502CompareTestSuite, CMP_IND_X) {
	InstructionCycles = 6;
	M6502.Memory[0xFFFC] = 0xC1;

	M6502.X = 0x01;

	M6502.Memory[0xFFFD] = 0x42;
	M6502.Memory[0x43] = 0xC0;
	M6502.Memory[0x44] = 0xC0;
	M6502.Memory[0xC0C0] = 0x20;
	TestCompare(&M6502.A);
	ASSERT_EQ(CyclesRan, InstructionCycles);
}

TEST_F(M6502CompareTestSuite, CMP_IND_Y) {
	InstructionCycles = 6;
	M6502.Memory[0xFFFC] = 0xD1;

	M6502.Y = 0x01;

	/* Page boundary crossed */
	M6502.Memory[0xFFFD] = 0x42;
	M6502.Memory[0x42] = 0xFF;
	M6502.Memory[0x43] = 0xC0;
	M6502.Memory[0xC100] = 0x20;
	TestCompare(&M6502.A);
	ASSERT_EQ(CyclesRan, InstructionCycles);

	/* Page boundary not crossed */
	M6502.PC = 0xFFFC;
	M6502.Memory[0x42] = 0xF0;
	M6502.Memory[0xC0F1] = 0x20;
	TestCompare(&M6502.A);
	ASSERT_EQ(CyclesRan, InstructionCycles - 1);
}

TEST_F(M6502CompareTestSuite, CPX_IMM) {
	InstructionCycles = 2;
	M6502.Memory[0xFFFC] = 0xE0;

	M6502.Memory[0xFFFD] = 0x20;
	TestCompare(&M6502.X);
	ASSERT_EQ(CyclesRan, InstructionCycles);
}

TEST_F(M6502CompareTestSuite, CPX_ZP) {
	InstructionCycles = 3;
	M6502.Memory[0xFFFC] = 0xE4;

	M6502.Memory[0xFFFD] = 0x42;
	M6502.Memory[0x42] = 0x20;
	TestCompare(&M6502.X);
	ASSERT_EQ(CyclesRan, InstructionCycles);
}

TEST_F(M6502CompareTestSuite, CPX_ABS) {
	InstructionCycles = 4;
	M6502.Memory[0xFFFC] = 0xEC;

	M6502.Memory[0xFFFD] = 0xA0;
	M6502.Memory[0xFFFE] = 0xB0;
	M6502.Memory[0xA0B0] = 0x20;
	TestCompare(&M6502.X);
	ASSERT_EQ(CyclesRan, InstructionCycles);
}

TEST_F(M6502CompareTestSuite, CPY_IMM) {
	InstructionCycles = 2;
	M6502.Memory[0xFFFC] = 0xC0;

	M6502.Memory[0xFFFD] = 0x20;
	TestCompare(&M6502.Y);
	ASSERT_EQ(CyclesRan, InstructionCycles);
}

TEST_F(M6502CompareTestSuite, CPY_ZP) {
	InstructionCycles = 3;
	M6502.Memory[0xFFFC] = 0xC4;

	M6502.Memory[0xFFFD] = 0x42;
	M6502.Memory[0x42] = 0x20;
	TestCompare(&M6502.Y);
	ASSERT_EQ(CyclesRan, InstructionCycles);
}

TEST_F(M6502CompareTestSuite, CPY_ABS) {
	InstructionCycles = 4;
	M6502.Memory[0xFFFC] = 0xCC;

	M6502.Memory[0xFFFD] = 0xA0;
	M6502.Memory[0xFFFE] = 0xB0;
	M6502.Memory[0xA0B0] = 0x20;
	TestCompare(&M6502.Y);
	ASSERT_EQ(CyclesRan, InstructionCycles);
}
