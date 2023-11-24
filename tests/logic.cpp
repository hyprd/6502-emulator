#include <gtest/gtest.h>
#include "../src/6502.h"

class M6502LogicTestSuite : public testing::Test {
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

TEST_F(M6502LogicTestSuite, AND_IMM) {
	InstructionCycles = 2;
	M6502.Memory[0xFFFC] = 0x29;

	M6502.Memory[0xFFFD] = 0x06;
	M6502.A = 0x0E;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.A, 0x06);
}

TEST_F(M6502LogicTestSuite, AND_ZP) {
	InstructionCycles = 3;
	M6502.Memory[0xFFFC] = 0x25;

	M6502.Memory[0xFFFD] = 0x42;
	M6502.Memory[0x42] = 0x06;
	M6502.A = 0x0E;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.A, 0x06);
}

TEST_F(M6502LogicTestSuite, AND_ZP_X) {
	InstructionCycles = 4;
	M6502.Memory[0xFFFC] = 0x35;

	M6502.Memory[0xFFFD] = 0x42;
	M6502.X = 0x01;
	M6502.Memory[0x43] = 0x06;
	M6502.A = 0x0E;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.A, 0x06);
}

TEST_F(M6502LogicTestSuite, AND_ABS) {
	InstructionCycles = 4;
	M6502.Memory[0xFFFC] = 0x2D;

	M6502.Memory[0xFFFD] = 0xFE;
	M6502.Memory[0xFFFE] = 0xF0;
	M6502.Memory[0xFEF0] = 0x06;
	M6502.A = 0x0E;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.A, 0x06);
}

TEST_F(M6502LogicTestSuite, AND_ABS_X) {
	InstructionCycles = 5;
	M6502.Memory[0xFFFC] = 0x3D;

	/* Page boundary crossed */
	M6502.X = 0xFF;
	M6502.Memory[0xFFFD] = 0xCE;
	M6502.Memory[0xFFFE] = 0xC0;
	M6502.Memory[0xCFBF] = 0x06;
	M6502.A = 0x0E;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.A, 0x06);
	ASSERT_EQ(CyclesRan, InstructionCycles);

	/* Page boundary not crossed */
	M6502.X = 0x01;
	M6502.PC = 0xFFFC;
	M6502.A = 0x0E;
	M6502.Memory[0xCEC1] = 0x03;
	CyclesRan = M6502.Execute(InstructionCycles - 1);
	ASSERT_EQ(M6502.A, 0x02);
	ASSERT_EQ(CyclesRan, InstructionCycles - 1);
}

TEST_F(M6502LogicTestSuite, AND_ABS_Y) {
	InstructionCycles = 5;
	M6502.Memory[0xFFFC] = 0x39;

	/* Page boundary crossed */
	M6502.Y = 0xFF;
	M6502.Memory[0xFFFD] = 0xCE;
	M6502.Memory[0xFFFE] = 0xC0;
	M6502.Memory[0xCFBF] = 0x06;
	M6502.A = 0x0E;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.A, 0x06);
	ASSERT_EQ(CyclesRan, InstructionCycles);

	/* Page boundary not crossed */
	M6502.Y = 0x01;
	M6502.PC = 0xFFFC;
	M6502.A = 0x0E;
	M6502.Memory[0xCEC1] = 0x03;
	CyclesRan = M6502.Execute(InstructionCycles - 1);
	ASSERT_EQ(M6502.A, 0x02);
	ASSERT_EQ(CyclesRan, InstructionCycles - 1);
}

TEST_F(M6502LogicTestSuite, AND_IND_X) {
	InstructionCycles = 6;
	M6502.Memory[0xFFFC] = 0x21;

	M6502.X = 0x01;
	M6502.Memory[0xFFFD] = 0x42;
	M6502.Memory[0x43] = 0xA0;
	M6502.Memory[0x44] = 0xA1;
	
	M6502.Memory[0xA1A0] = 0x06;
	M6502.A = 0x0E;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.A, 0x06);
	ASSERT_EQ(CyclesRan, InstructionCycles);
}

TEST_F(M6502LogicTestSuite, AND_IND_Y) {
	InstructionCycles = 6;
	M6502.Memory[0xFFFC] = 0x31;

	/* Page boundary crossed */
	M6502.Y = 0x01;
	M6502.A = 0x0E;
	M6502.Memory[0xFFFD] = 0x50;
	M6502.Memory[0x50] = 0xFF;
	M6502.Memory[0x51] = 0xA2;
	M6502.Memory[0xA300] = 0x06;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.A, 0x06);
	ASSERT_EQ(CyclesRan, InstructionCycles);

	/* Page boundary not crossed */
	M6502.Y = 0x01;
	M6502.A = 0x0E;
	M6502.PC = 0xFFFC;
	M6502.Memory[0x50] = 0xF0;
	M6502.Memory[0x51] = 0xFF;
	M6502.Memory[0xFFF1] = 0x06;
	CyclesRan = M6502.Execute(InstructionCycles - 1);
	ASSERT_EQ(M6502.A, 0x06);
	ASSERT_EQ(CyclesRan, InstructionCycles - 1);
}

TEST_F(M6502LogicTestSuite, EOR_IMM) {
	InstructionCycles = 2;
	M6502.Memory[0xFFFC] = 0x49;

	M6502.A = 0x04;
	M6502.Memory[0xFFFD] = 0x03;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.A, 0x07);
	ASSERT_EQ(CyclesRan, InstructionCycles);
}

TEST_F(M6502LogicTestSuite, EOR_ZP) {
	InstructionCycles = 3;
	M6502.Memory[0xFFFC] = 0x45;

	M6502.A = 0x04;
	M6502.Memory[0xFFFD] = 0x42;
	M6502.Memory[0x42] = 0x03;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.A, 0x07);
	ASSERT_EQ(CyclesRan, InstructionCycles);
}

TEST_F(M6502LogicTestSuite, EOR_ZP_X) {
	InstructionCycles = 4;
	M6502.Memory[0xFFFC] = 0x55;

	M6502.A = 0x04;
	M6502.X = 0x01;
	M6502.Memory[0xFFFD] = 0x42;
	M6502.Memory[0x43] = 0x03;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.A, 0x07);
	ASSERT_EQ(CyclesRan, InstructionCycles);
}

TEST_F(M6502LogicTestSuite, EOR_ABS) {
	InstructionCycles = 4;
	M6502.Memory[0xFFFC] = 0x4D;

	M6502.A = 0x03;
	M6502.Memory[0xFFFD] = 0xB0;
	M6502.Memory[0xFFFE] = 0xB0;
	M6502.Memory[0xB0B0] = 0x04;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.A, 0x07);
	ASSERT_EQ(CyclesRan, InstructionCycles);
}

TEST_F(M6502LogicTestSuite, EOR_ABS_X) {
	InstructionCycles = 5;
	M6502.Memory[0xFFFC] = 0x5D;

	/* Page boundary crossed */
	M6502.A = 0x03;
	M6502.Memory[0xFFFD] = 0xA0;
	M6502.Memory[0xFFFE] = 0xFF;
	M6502.X = 0x01;
	M6502.Memory[0xA100] = 0x04;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.A, 0x07);
	ASSERT_EQ(CyclesRan, InstructionCycles);

	/* Page boundary not crossed */
	M6502.PC = 0xFFFC;
	M6502.A = 0x03;
	M6502.Memory[0xFFFE] = 0xF0;
	M6502.Memory[0xA0F1] = 0x04;
	CyclesRan = M6502.Execute(InstructionCycles - 1);
	ASSERT_EQ(M6502.A, 0x07);
	ASSERT_EQ(CyclesRan, InstructionCycles - 1);
}

TEST_F(M6502LogicTestSuite, EOR_ABS_Y) {
	InstructionCycles = 5;
	M6502.Memory[0xFFFC] = 0x59;

	/* Page boundary crossed */
	M6502.A = 0x03;
	M6502.Memory[0xFFFD] = 0xA0;
	M6502.Memory[0xFFFE] = 0xFF;
	M6502.Y = 0x01;
	M6502.Memory[0xA100] = 0x04;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.A, 0x07);
	ASSERT_EQ(CyclesRan, InstructionCycles);

	/* Page boundary not crossed */
	M6502.PC = 0xFFFC;
	M6502.A = 0x03;
	M6502.Memory[0xFFFE] = 0xF0;
	M6502.Memory[0xA0F1] = 0x04;
	CyclesRan = M6502.Execute(InstructionCycles - 1);
	ASSERT_EQ(M6502.A, 0x07);
	ASSERT_EQ(CyclesRan, InstructionCycles - 1);
}

TEST_F(M6502LogicTestSuite, EOR_IND_X) {
	InstructionCycles = 6;
	M6502.Memory[0xFFFC] = 0x41;

	M6502.A = 0x04;
	M6502.X = 0x01;
	M6502.Memory[0xFFFD] = 0x42;
	M6502.Memory[0x43] = 0xD0;
	M6502.Memory[0x44] = 0xD0;
	M6502.Memory[0xD0D0] = 0x03;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.A, 0x07);
	ASSERT_EQ(CyclesRan, InstructionCycles);
}

TEST_F(M6502LogicTestSuite, EOR_IND_Y) {
	InstructionCycles = 6;
	M6502.Memory[0xFFFC] = 0x51;

	/* Page boundary crossed */
	M6502.A = 0x04;
	M6502.Memory[0xFFFD] = 0x42;
	M6502.Memory[0x42] = 0xFF;
	M6502.Memory[0x43] = 0xC0;
	M6502.Y = 0x01;
	M6502.Memory[0xC100] = 0x03;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.A, 0x07);
	ASSERT_EQ(CyclesRan, InstructionCycles);

	/* Page boundary not crossed */
	M6502.PC = 0xFFFC;
	M6502.A = 0x04;
	M6502.Memory[0x42] = 0xF0;
	M6502.Memory[0xC0F1] = 0x03;
	CyclesRan = M6502.Execute(InstructionCycles - 1);
	ASSERT_EQ(M6502.A, 0x07);
	ASSERT_EQ(CyclesRan, InstructionCycles - 1);
}

TEST_F(M6502LogicTestSuite, ORA_IMM) {
	InstructionCycles = 2;
	M6502.Memory[0xFFFC] = 0x09;

	M6502.A = 0x12;
	M6502.Memory[0xFFFD] = 0x13;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.A, 0x13);
	ASSERT_EQ(CyclesRan, InstructionCycles);
}

TEST_F(M6502LogicTestSuite, ORA_ZP) {
	InstructionCycles = 3;
	M6502.Memory[0xFFFC] = 0x05;

	M6502.A = 0x12;
	M6502.Memory[0xFFFD] = 0x42;
	M6502.Memory[0x42] = 0x13;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.A, 0x13);
	ASSERT_EQ(CyclesRan, InstructionCycles);
}

TEST_F(M6502LogicTestSuite, ORA_ZP_X) {
	InstructionCycles = 4;
	M6502.Memory[0xFFFC] = 0x15;

	M6502.A = 0x12;
	M6502.X = 0x01;
	M6502.Memory[0xFFFD] = 0x42;
	M6502.Memory[0x43] = 0x13;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.A, 0x13);
	ASSERT_EQ(CyclesRan, InstructionCycles);
}

TEST_F(M6502LogicTestSuite, ORA_ABS) {
	InstructionCycles = 4;
	M6502.Memory[0xFFFC] = 0x0D;

	M6502.A = 0x12;
	M6502.Memory[0xFFFD] = 0xB0;
	M6502.Memory[0xFFFE] = 0xB0;
	M6502.Memory[0xB0B0] = 0x13;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.A, 0x13);
	ASSERT_EQ(CyclesRan, InstructionCycles);
}

TEST_F(M6502LogicTestSuite, ORA_ABS_X) {
	InstructionCycles = 5;
	M6502.Memory[0xFFFC] = 0x1D;

	/* Page boundary crossed */
	M6502.A = 0x12;
	M6502.Memory[0xFFFD] = 0xA0;
	M6502.Memory[0xFFFE] = 0xFF;
	M6502.X = 0x01;
	M6502.Memory[0xA100] = 0x13;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.A, 0x13);
	ASSERT_EQ(CyclesRan, InstructionCycles);

	/* Page boundary not crossed */
	M6502.PC = 0xFFFC;
	M6502.A = 0x12;
	M6502.Memory[0xFFFE] = 0xF0;
	M6502.Memory[0xA0F1] = 0x13;
	CyclesRan = M6502.Execute(InstructionCycles - 1);
	ASSERT_EQ(M6502.A, 0x13);
	ASSERT_EQ(CyclesRan, InstructionCycles - 1);
}

TEST_F(M6502LogicTestSuite, ORA_ABS_Y) {
	InstructionCycles = 5;
	M6502.Memory[0xFFFC] = 0x19;

	/* Page boundary crossed */
	M6502.A = 0x12;
	M6502.Memory[0xFFFD] = 0xA0;
	M6502.Memory[0xFFFE] = 0xFF;
	M6502.Y = 0x01;
	M6502.Memory[0xA100] = 0x13;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.A, 0x13);
	ASSERT_EQ(CyclesRan, InstructionCycles);

	/* Page boundary not crossed */
	M6502.PC = 0xFFFC;
	M6502.A = 0x12;
	M6502.Memory[0xFFFE] = 0xF0;
	M6502.Memory[0xA0F1] = 0x13;
	CyclesRan = M6502.Execute(InstructionCycles - 1);
	ASSERT_EQ(M6502.A, 0x13);
	ASSERT_EQ(CyclesRan, InstructionCycles - 1);
}

TEST_F(M6502LogicTestSuite, ORA_IND_X) {
	InstructionCycles = 6;
	M6502.Memory[0xFFFC] = 0x01;

	M6502.A = 0x12;
	M6502.X = 0x01;
	M6502.Memory[0xFFFD] = 0x42;
	M6502.Memory[0x43] = 0xD0;
	M6502.Memory[0x44] = 0xD0;
	M6502.Memory[0xD0D0] = 0x13;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.A, 0x13);
	ASSERT_EQ(CyclesRan, InstructionCycles);
}

TEST_F(M6502LogicTestSuite, ORA_IND_Y) {
	InstructionCycles = 6;
	M6502.Memory[0xFFFC] = 0x11;

	/* Page boundary crossed */
	M6502.A = 0x12;
	M6502.Memory[0xFFFD] = 0x42;
	M6502.Memory[0x42] = 0xFF;
	M6502.Memory[0x43] = 0xC0;
	M6502.Y = 0x01;
	M6502.Memory[0xC100] = 0x13;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.A, 0x13);
	ASSERT_EQ(CyclesRan, InstructionCycles);

	/* Page boundary not crossed */
	M6502.PC = 0xFFFC;
	M6502.A = 0x12;
	M6502.Memory[0x42] = 0xF0;
	M6502.Memory[0xC0F1] = 0x03;
	CyclesRan = M6502.Execute(InstructionCycles - 1);
	ASSERT_EQ(M6502.A, 0x13);
	ASSERT_EQ(CyclesRan, InstructionCycles - 1);
}

