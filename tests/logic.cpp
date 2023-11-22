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

//TEST_F(M6502LogicTestSuite, EOR_IMM) {
//	ASSERT_EQ(0, 0);
//}
//
//TEST_F(M6502LogicTestSuite, EOR_ZP) {
//	ASSERT_EQ(0, 0);
//}
//
//TEST_F(M6502LogicTestSuite, EOR_ZP_X) {
//	ASSERT_EQ(0, 0);
//}
//
//TEST_F(M6502LogicTestSuite, EOR_ABS) {
//	ASSERT_EQ(0, 0);
//}
//
//TEST_F(M6502LogicTestSuite, EOR_ABS_X) {
//	ASSERT_EQ(0, 0);
//}
//
//TEST_F(M6502LogicTestSuite, EOR_ABS_Y) {
//	ASSERT_EQ(0, 0);
//}
//
//TEST_F(M6502LogicTestSuite, EOR_IND_X) {
//	ASSERT_EQ(0, 0);
//}
//
//TEST_F(M6502LogicTestSuite, EOR_IND_Y) {
//	ASSERT_EQ(0, 0);
//}
//
//TEST_F(M6502LogicTestSuite, ORA_IMM) {
//	ASSERT_EQ(0, 0);
//}
//
//TEST_F(M6502LogicTestSuite, ORA_ZP) {
//	ASSERT_EQ(0, 0);
//}
//
//TEST_F(M6502LogicTestSuite, ORA_ZP_X) {
//	ASSERT_EQ(0, 0);
//}
//
//TEST_F(M6502LogicTestSuite, ORA_ABS) {
//	ASSERT_EQ(0, 0);
//}
//
//TEST_F(M6502LogicTestSuite, ORA_ABS_X) {
//	ASSERT_EQ(0, 0);
//}
//
//TEST_F(M6502LogicTestSuite, ORA_ABS_Y) {
//	ASSERT_EQ(0, 0);
//}
//
//TEST_F(M6502LogicTestSuite, ORA_IND_X) {
//	ASSERT_EQ(0, 0);
//}
//
//TEST_F(M6502LogicTestSuite, ORA_IND_Y) {
//	ASSERT_EQ(0, 0);
//}
//
