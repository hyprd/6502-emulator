#include <gtest/gtest.h>
#include "6502.h"

class M6502TestSuite : public testing::Test {
public:
	NMOS6502 NMOS6502;

	virtual void SetUp() {
	}

	virtual void TearDown() {

	}
};