#include "6502.h"

NMOS6502::NMOS6502() {
	Memory = std::vector<u8>(1024 * 64);
	std::fill(Memory.begin(), Memory.end(), 0);
	A = 0x0;
	X = 0x0;
	Y = 0x0;
	PC = 0xFFFC;
	SP = 0x0100; 
}

NMOS6502::~NMOS6502() {}

void NMOS6502::Reset() {
	A = 0x0;
	X = 0x0;
	Y = 0x0;
	PC = 0xFFFC;
	SP = 0x0100;
	std::fill(Memory.begin(), Memory.end(), 0);
}