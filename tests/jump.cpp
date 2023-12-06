#include <gtest/gtest.h>
#include "../src/6502.h"

class M6502JumpTestSuite : public testing::Test {
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

TEST_F(M6502JumpTestSuite, JMP_ABS) {
	InstructionCycles = 3;
	M6502.Memory[0xFFFC] = 0x4C;

	M6502.Memory[0xFFFD] = 0x00;
	M6502.Memory[0xFFFE] = 0x30;

	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.PC, 0x3000);
	ASSERT_EQ(CyclesRan, InstructionCycles);
}

TEST_F(M6502JumpTestSuite, JMP_IND) {
	InstructionCycles = 5;
	M6502.Memory[0xFFFC] = 0x6C;

	M6502.Memory[0xFFFD] = 0x00;
	M6502.Memory[0xFFFE] = 0x30;

	M6502.Memory[0x3000] = 0x42;
	M6502.Memory[0x3001] = 0x43;
	CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.PC, 0x4243);
	ASSERT_EQ(CyclesRan, InstructionCycles);
}

TEST_F(M6502JumpTestSuite, JSR_ABS) {
	InstructionCycles =	6;
	M6502.SP = 0x01FF;
	M6502.Memory[0xFFFC] = 0x20;
	M6502.Memory[0xFFFE] = 0xB3; // ll
	M6502.Memory[0xFFFF] = 0xB1; // HH
	CyclesRan = M6502.Execute(InstructionCycles);
	// PC was pushed correctly to the stack
	ASSERT_EQ(M6502.Memory[0x01FF], 0xFF);
	ASSERT_EQ(M6502.Memory[0x01FE], 0xFC);
	// PC is now set to subroutine at 0xB1B3
	ASSERT_EQ(M6502.PC, 0xB1B3);
	// Stack pointer decremented correctly after adding two bytes to the stack
	ASSERT_EQ(M6502.SP, 0x01FD);
	ASSERT_EQ(CyclesRan, InstructionCycles);
}

TEST_F(M6502JumpTestSuite, RTS) {
	M6502.PC = 0xFFF0;
	M6502.Memory[0xFFF0] = 0x20;
	M6502.ProcessorStatus.reset();

	/* 
		Program flow 
		1. Jump to subroutine
		2. Load A with value 0x30
		3. Shift A one bit
		4. Store this new A value in memory location (zero page)
		5. Return from subroutine
		6. Following instruction compares A to zero page location 
		7. Assert flags
	*/

	/* Simulate the JSR instruction */
	M6502.SP = 0x01FF;
	M6502.Memory[0xFFF2] = 0xB3;
	M6502.Memory[0xFFF3] = 0xB1;
	CyclesRan = M6502.Execute(InstructionCycles);

	M6502.Memory[0xB1B3] = 0xA9; // LDA
	M6502.Memory[0xB1B4] = 0x30; // IMM
	CyclesRan = M6502.Execute(InstructionCycles);

	M6502.Memory[0xB1B5] = 0x4A; // LSR
	CyclesRan = M6502.Execute(InstructionCycles);

	M6502.Memory[0xB1B6] = 0x85; // STA
	M6502.Memory[0xB1B7] = 0xF0; // STA ZP
	CyclesRan = M6502.Execute(InstructionCycles);

	M6502.Memory[0xB1B8] = 0x60; // RTS
	CyclesRan = M6502.Execute(InstructionCycles);

	M6502.Memory[0xFFF1] = 0xC5; // CMP
	M6502.Memory[0xFFF2] = 0xF0; // CMP ZP
	CyclesRan = M6502.Execute(InstructionCycles);

	ASSERT_EQ(M6502.A, M6502.Memory[0xF0]);
	ASSERT_EQ(M6502.ProcessorStatus[M6502.N], 0);
	ASSERT_EQ(M6502.ProcessorStatus[M6502.Z], 1);
	ASSERT_EQ(M6502.ProcessorStatus[M6502.C], 1);
}
