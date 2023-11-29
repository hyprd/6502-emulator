#include <gtest/gtest.h>
#include "../src/6502.h"

class M6502StackTestSuite : public testing::Test {
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

TEST_F(M6502StackTestSuite, PHA) {
	InstructionCycles = 3;
	M6502.Memory[0xFFFC] = 0x48;

	M6502.A = 0x42;
	M6502.SP = 0x01FF;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.SP, 0x01FE);
	ASSERT_EQ(M6502.Memory[M6502.SP + 1], 0x42);
}

TEST_F(M6502StackTestSuite, PHP) {
	InstructionCycles = 3;
	M6502.Memory[0xFFFC] = 0x08;

	M6502.SP = 0x01FF;
	M6502.ProcessorStatus.set();
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.SP, 0x01FE);
	ASSERT_EQ(M6502.Memory[M6502.SP + 1], 0b111111);
}

TEST_F(M6502StackTestSuite, PLA) {
	InstructionCycles = 4;
	M6502.Memory[0xFFFC] = 0x68;
	M6502.SP = 0x01FE;
	M6502.Memory[0x01FE] = 0x42;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.A, 0x42);
	ASSERT_EQ(M6502.SP, 0x01FF);
	ASSERT_EQ(M6502.Memory[0x01FE], 0x0);
}

TEST_F(M6502StackTestSuite, PLP) {
	InstructionCycles = 4;
	M6502.Memory[0xFFFC] = 0x28;

	M6502.SP = 0x01FE;
	M6502.ProcessorStatus.set();
	M6502.Memory[0x01FE] = static_cast<u8>(M6502.ProcessorStatus.to_ulong());
	M6502.ProcessorStatus.reset();
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.ProcessorStatus.to_ulong(), 0x3F);
	ASSERT_EQ(M6502.SP, 0x01FF);
	ASSERT_EQ(M6502.Memory[0x01FE], 0x0);
}

