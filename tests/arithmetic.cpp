#include <gtest/gtest.h>
#include "../src/6502.h"

class M6502ArithmeticTestSuite : public testing::Test {
public:
	NMOS6502 M6502;
	u32 InstructionCycles = 0;
	u32 CyclesRan = 0;

	virtual void SetUp() {
		M6502.Reset();
		M6502.ProcessorStatus.set(M6502.C);
		M6502.A = 0x00;
	}

	virtual void TearDown() {
	}

	void TestArithmetic(u8 Operand, u8 Target) {
		M6502.A = 0x00;
		M6502.ProcessorStatus.set(M6502.C);
		CyclesRan = M6502.Execute(InstructionCycles);
		
		ASSERT_EQ(M6502.A, Target);
	}
};

TEST_F(M6502ArithmeticTestSuite, ADC_IMM) {
	InstructionCycles = 2;
	M6502.Memory[0xFFFC] = 0x69;

	M6502.Memory[0xFFFD] = 0x42;
	TestArithmetic(M6502.A, 0x43);
	ASSERT_EQ(CyclesRan, InstructionCycles);
}

TEST_F(M6502ArithmeticTestSuite, ADC_ZP) {
	InstructionCycles = 3;
	M6502.Memory[0xFFFC] = 0x65;

	M6502.Memory[0xFFFD] = 0x42;
	M6502.Memory[0x42] = 0xB3;
	TestArithmetic(M6502.A, 0xB4);
	ASSERT_EQ(CyclesRan, InstructionCycles);
}

TEST_F(M6502ArithmeticTestSuite, ADC_ZP_X) {
	InstructionCycles = 4;
	M6502.Memory[0xFFFC] = 0x75;

	M6502.Memory[0xFFFD] = 0x42;
	M6502.X = 0x01;
	M6502.Memory[0x43] = 0xB3;
	TestArithmetic(M6502.A, 0xB4);
	ASSERT_EQ(CyclesRan, InstructionCycles);
}

TEST_F(M6502ArithmeticTestSuite, ADC_ABS) {
	InstructionCycles = 4;
	M6502.Memory[0xFFFC] = 0x6D;

	M6502.Memory[0xFFFD] = 0xAB;
	M6502.Memory[0xFFFE] = 0xAB;
	M6502.Memory[0xABAB] = 0xB3;
	TestArithmetic(M6502.A, 0xB4);
	ASSERT_EQ(CyclesRan, InstructionCycles);
}

TEST_F(M6502ArithmeticTestSuite, ADC_ABS_X) {
	InstructionCycles = 5;
	M6502.Memory[0xFFFC] = 0x7D;

	M6502.X = 0x01;

	/* Page boundary crossed */
	M6502.Memory[0xFFFD] = 0xA0;
	M6502.Memory[0xFFFE] = 0xFF;
	M6502.Memory[0xA100] = 0xB3;
	TestArithmetic(M6502.A, 0xB4);
	ASSERT_EQ(CyclesRan, InstructionCycles);

	/* Page boundary not crossed */
	M6502.PC = 0xFFFC;
	M6502.A = 0x00;
	M6502.Memory[0xFFFE] = 0xFE;
	M6502.Memory[0xA0FF] = 0xB3;
	TestArithmetic(M6502.A, 0xB4);
	ASSERT_EQ(CyclesRan, InstructionCycles - 1);
}

TEST_F(M6502ArithmeticTestSuite, ADC_ABS_Y) {
	InstructionCycles = 5;
	M6502.Memory[0xFFFC] = 0x79;

	M6502.Y = 0x01;

	/* Page boundary crossed */
	M6502.Memory[0xFFFD] = 0xA0;
	M6502.Memory[0xFFFE] = 0xFF;
	M6502.Memory[0xA100] = 0xB3;
	TestArithmetic(M6502.A, 0xB4);
	ASSERT_EQ(CyclesRan, InstructionCycles);

	/* Page boundary not crossed */
	M6502.PC = 0xFFFC;
	M6502.A = 0x00;
	M6502.Memory[0xFFFE] = 0xFE;
	M6502.Memory[0xA0FF] = 0xB3;
	TestArithmetic(M6502.A, 0xB4);
	ASSERT_EQ(CyclesRan, InstructionCycles - 1);
}

TEST_F(M6502ArithmeticTestSuite, ADC_IND_X) {
	InstructionCycles = 6;
	M6502.Memory[0xFFFC] = 0x61;
	
	M6502.X = 0x01;

	M6502.Memory[0xFFFD] = 0x42;
	M6502.Memory[0x43] = 0xC0;
	M6502.Memory[0x44] = 0xC2;
	M6502.Memory[0xC2C0] = 0xB3;
	TestArithmetic(M6502.A, 0xB4);
	ASSERT_EQ(CyclesRan, InstructionCycles);
}

TEST_F(M6502ArithmeticTestSuite, ADC_IND_Y) {
	InstructionCycles = 6;
	M6502.Memory[0xFFFC] = 0x71;

	/* Page boundary crossed */
	M6502.Memory[0xFFFD] = 0x42;
	M6502.Y = 0x01;
	M6502.Memory[0x42] = 0xFF;
	M6502.Memory[0x43] = 0xA2;
	M6502.Memory[0xA300] = 0xB3;
	TestArithmetic(M6502.A, 0xB4);
	ASSERT_EQ(CyclesRan, InstructionCycles);

	/* Page boundary not crossed */
	M6502.PC = 0xFFFC;
	M6502.A = 0x00;
	M6502.Memory[0x42] = 0xF0;
	M6502.Memory[0xA2F1] = 0xB3;
	TestArithmetic(M6502.A, 0xB4);
	ASSERT_EQ(CyclesRan, InstructionCycles - 1);
}