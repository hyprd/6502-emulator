#include <gtest/gtest.h>
#include "../src/6502.h"

class M6502IncDecTestSuite : public testing::Test {
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

TEST_F(M6502IncDecTestSuite, DEC_ZP) {
	InstructionCycles = 5;
	ASSERT_EQ(0, 0);
}

TEST_F(M6502IncDecTestSuite, DEC_ZP_X) {
	InstructionCycles = 6;
	ASSERT_EQ(0, 0);
}

TEST_F(M6502IncDecTestSuite, DEC_ABS) {
	InstructionCycles = 6;
	ASSERT_EQ(0, 0);
}

TEST_F(M6502IncDecTestSuite, DEC_ABS_X) {
	InstructionCycles = 7;
	ASSERT_EQ(0, 0);
}

TEST_F(M6502IncDecTestSuite, DEX) {
	InstructionCycles = 2;
	ASSERT_EQ(0, 0);
}

TEST_F(M6502IncDecTestSuite, DEY) {
	InstructionCycles = 2;
	ASSERT_EQ(0, 0);
}

TEST_F(M6502IncDecTestSuite, INC_ZP) {
	InstructionCycles = 5;
	ASSERT_EQ(0, 0);
}

TEST_F(M6502IncDecTestSuite, INC_ZP_X) {
	InstructionCycles = 6;
	ASSERT_EQ(0, 0);
}

TEST_F(M6502IncDecTestSuite, INC_ABS) {
	InstructionCycles = 6;
	ASSERT_EQ(0, 0);
}

TEST_F(M6502IncDecTestSuite, INC_ABS_X) {
	InstructionCycles = 7;
	ASSERT_EQ(0, 0);
}

TEST_F(M6502IncDecTestSuite, INX) {
	InstructionCycles = 2;
	ASSERT_EQ(0, 0);
}

TEST_F(M6502IncDecTestSuite, INY) {
	InstructionCycles = 2;
	ASSERT_EQ(0, 0);
}