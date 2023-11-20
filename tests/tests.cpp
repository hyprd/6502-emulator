#include <gtest/gtest.h>
#include "../src/6502.h"

class M6502TestSuite : public testing::Test {
public:
	NMOS6502 M6502;

	virtual void SetUp() {
		M6502.Reset();
	}

	virtual void TearDown() {

	}
};

TEST_F(M6502TestSuite, LDA_IMM) {
	u32 InstructionCycles = 2;
	M6502.PC = 0xFFFC;
	M6502.Memory[0xFFFC] = 0xA9;
	M6502.Memory[0xFFFD] = 0x42;
	M6502.Execute(InstructionCycles);
	ASSERT_EQ(M6502.A, 0x42);
	ASSERT_EQ(M6502.CyclesPerformed, InstructionCycles);
}

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}