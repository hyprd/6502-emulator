#include <gtest/gtest.h>
#include "../src/6502.h"

class M6502TestSuite : public testing::Test {
public:
	NMOS6502 M6502;
	u32 InstructionCycles = 0;

	virtual void SetUp() {
		M6502.Reset();
	}

	virtual void TearDown() {

	}
};

TEST_F(M6502TestSuite, LDA_IMM) {
	InstructionCycles = 2;
	M6502.Memory[0xFFFC] = 0xA9;
	M6502.Memory[0xFFFD] = 0x42;
	M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.A, 0x42);
}

TEST_F(M6502TestSuite, LDA_ABS) {
	InstructionCycles = 4;
	M6502.Memory[0xFFFC] = 0xAD;
	M6502.Memory[0xFFFD] = 0xBC;
	M6502.Memory[0xFFFE] = 0xA1;
	M6502.Memory[0xBCA1] = 0x90;
	u8 CyclesRan = M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.A, 0x90);
	ASSERT_EQ(CyclesRan, InstructionCycles);
}

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}