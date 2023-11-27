#include <gtest/gtest.h>
#include "../src/6502.h"

class M6502FlagTestSuite : public testing::Test {
public:
	NMOS6502 M6502;
	u32 InstructionCycles = 0;
	u32 CyclesRan = 0;

	virtual void SetUp() {
		M6502.Reset();
	}

	virtual void TearDown() {
		ASSERT_EQ(InstructionCycles, CyclesRan);
	}
};

TEST_F(M6502FlagTestSuite, CLC) {
	InstructionCycles = 2;
	M6502.Memory[0xFFFC] = 0x18;

	M6502.ProcessorStatus.set(M6502.C);
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.ProcessorStatus[M6502.C], 0);
}

TEST_F(M6502FlagTestSuite, CLD) {
	InstructionCycles = 2;
	M6502.Memory[0xFFFC] = 0xD8;

	M6502.ProcessorStatus.set(M6502.D);
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.ProcessorStatus[M6502.D], 0);
}

TEST_F(M6502FlagTestSuite, CLI) {
	InstructionCycles = 2;
	M6502.Memory[0xFFFC] = 0x58;

	M6502.ProcessorStatus.set(M6502.I);
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.ProcessorStatus[M6502.I], 0);
}

TEST_F(M6502FlagTestSuite, CLV) {
	InstructionCycles = 2;
	M6502.Memory[0xFFFC] = 0xB8;

	M6502.ProcessorStatus.set(M6502.V);
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.ProcessorStatus[M6502.V], 0);
}

TEST_F(M6502FlagTestSuite, SEC) {
	InstructionCycles = 2;
	M6502.Memory[0xFFFC] = 0x38;

	M6502.ProcessorStatus.reset(M6502.C);
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.ProcessorStatus[M6502.C], 1);
}

TEST_F(M6502FlagTestSuite, SED) {
	InstructionCycles = 2;
	M6502.Memory[0xFFFC] = 0xF8;

	M6502.ProcessorStatus.reset(M6502.C);
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.ProcessorStatus[M6502.D], 1);
}

TEST_F(M6502FlagTestSuite, SEI) {
	InstructionCycles = 2;
	M6502.Memory[0xFFFC] = 0x78;

	M6502.ProcessorStatus.reset(M6502.C);
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.ProcessorStatus[M6502.I], 1);
}

