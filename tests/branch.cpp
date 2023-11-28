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

	void BranchTest(u8 Opcode, u8 ProcessorFlag, bool ClearOperation) {
		InstructionCycles = 4;
		M6502.PC = 0xFF00;
		M6502.Memory[0xFF00] = Opcode;

		/* Non-branching conditional */
		ClearOperation ? M6502.ProcessorStatus.set(ProcessorFlag) : M6502.ProcessorStatus.reset(ProcessorFlag);
		CyclesRan = M6502.Execute(InstructionCycles);
		ASSERT_EQ(CyclesRan, InstructionCycles - 2);

		ClearOperation ? M6502.ProcessorStatus.reset(ProcessorFlag) : M6502.ProcessorStatus.set(ProcessorFlag);

		/* Branch with positive offset (non-crossing) */
		M6502.PC = 0xFF00;
		M6502.Memory[0xFF01] = 0x10;
		CyclesRan = M6502.Execute(InstructionCycles);
		ASSERT_EQ(M6502.PC, 0xFF10);
		ASSERT_EQ(CyclesRan, InstructionCycles - 1);

		/* Branch with negative offset (non-crossing) */
		M6502.PC = 0xFF05;
		M6502.Memory[0xFF05] = Opcode;
		M6502.Memory[0xFF06] = 0xFB; // -5
		CyclesRan = M6502.Execute(InstructionCycles);
		ASSERT_EQ(M6502.PC, 0xFF00);
		ASSERT_EQ(CyclesRan, InstructionCycles - 1);

		/* Branch with positive offset (crossing) */
		M6502.PC = 0xEEF0;
		M6502.Memory[0xEEF0] = Opcode;
		M6502.Memory[0xEEF1] = 0x10;
		CyclesRan = M6502.Execute(InstructionCycles);
		ASSERT_EQ(M6502.PC, 0xEF00);
		ASSERT_EQ(CyclesRan, InstructionCycles);

		/* Branch with negative offset (crossing) */
		M6502.PC = 0xFF04;
		M6502.Memory[0xFF04] = Opcode;
		M6502.Memory[0xFF05] = 0xFB;
		CyclesRan = M6502.Execute(InstructionCycles);
		ASSERT_EQ(M6502.PC, 0xFEFF);
		ASSERT_EQ(CyclesRan, InstructionCycles);
	}
};

TEST_F(M6502BranchTestSuite, BCC) {
	BranchTest(0x90, M6502.C, true);
}

TEST_F(M6502BranchTestSuite, BCS) {
	BranchTest(0xB0, M6502.C, false);
}

TEST_F(M6502BranchTestSuite, BEQ) {
	BranchTest(0xF0, M6502.Z, false);
}

TEST_F(M6502BranchTestSuite, BMI) {
	BranchTest(0x30, M6502.N, false);
}

TEST_F(M6502BranchTestSuite, BNE) {
	BranchTest(0xD0, M6502.Z, true);
}

TEST_F(M6502BranchTestSuite, BPL) {
	BranchTest(0x10, M6502.N, true);
}

TEST_F(M6502BranchTestSuite, BVC) {
	BranchTest(0x50, M6502.V, true);
}

TEST_F(M6502BranchTestSuite, BVS) {
	BranchTest(0x70, M6502.V, false);
}


