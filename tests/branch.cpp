#include <gtest/gtest.h>
#include "../src/6502.h"

class M6502BranchTestSuite : public testing::Test {
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

TEST_F(M6502BranchTestSuite, BCC) {
	InstructionCycles = 4;
	M6502.PC = 0xFF00;
	M6502.Memory[0xFF00] = 0x90;
	
	/* Carry isn't cleared, don't branch. If branching occurred there would be 3 cycles. */
	M6502.ProcessorStatus.set(M6502.C);
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(CyclesRan, InstructionCycles - 2);

	M6502.ProcessorStatus.reset(M6502.C);

	/* Branch with positive offset (non-crossing) */
	M6502.PC = 0xFF00;
	M6502.Memory[0xFF01] = 0x10;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.PC, 0xFF10);
	ASSERT_EQ(CyclesRan, InstructionCycles - 1);

	/* Branch with negative offset (non-crossing) */
	M6502.PC = 0xFF05;
	M6502.Memory[0xFF05] = 0x90;
	M6502.Memory[0xFF06] = 0xFB; // -5
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.PC, 0xFF00);
	ASSERT_EQ(CyclesRan, InstructionCycles - 1);

	/* Branch with positive offset (crossing) */
	M6502.PC = 0xEEF0;
	M6502.Memory[0xEEF0] = 0x90;
	M6502.Memory[0xEEF1] = 0x10;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.PC, 0xEF00);
	ASSERT_EQ(CyclesRan, InstructionCycles);

	/* Branch with negative offset (crossing) */
	M6502.PC = 0xFF04;
	M6502.Memory[0xFF04] = 0x90;
	M6502.Memory[0xFF05] = 0xFB;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.PC , 0xFEFF);
	ASSERT_EQ(CyclesRan, InstructionCycles);
}



