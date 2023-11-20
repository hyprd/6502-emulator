#include "6502.h"

NMOS6502::NMOS6502() {
	Memory = std::vector<u8>(1024 * 64);
	std::fill(Memory.begin(), Memory.end(), 0);
	A = 0x0;
	X = 0x0;
	Y = 0x0;
	PC = 0xFFFC;
	SP = 0x0100;
	BindOpcodes();
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

u8 NMOS6502::FetchByte()
{
	++CyclesPerformed;
	return Memory[PC++];
}

u16 NMOS6502::FetchWord() {
	CyclesPerformed += 2;
	u16 word = static_cast<u16>(Memory[PC] << 8 | Memory[PC + 1] & 0x00FF);
	PC += 2;
	return word;
}

int NMOS6502::Execute(u32 CyclesRequired) {
	CyclesPerformed = 0;
	u8 inst = FetchByte();
	(this->*Opcodes[inst])();
	return CyclesPerformed;
}

void NMOS6502::Cycle() {
	++CyclesPerformed;
}

void NMOS6502::Opcode0x00() {

}

void NMOS6502::Opcode0x01() {

}

void NMOS6502::Opcode0x02() {

}

void NMOS6502::Opcode0x03() {

}

void NMOS6502::Opcode0x04() {

}

void NMOS6502::Opcode0x05() {

}

void NMOS6502::Opcode0x06() {

}

void NMOS6502::Opcode0x07() {

}

void NMOS6502::Opcode0x08() {

}

void NMOS6502::Opcode0x09() {

}

void NMOS6502::Opcode0x0A() {

}

void NMOS6502::Opcode0x0B() {

}

void NMOS6502::Opcode0x0C() {

}

void NMOS6502::Opcode0x0D() {

}

void NMOS6502::Opcode0x0E() {

}

void NMOS6502::Opcode0x0F() {

}

void NMOS6502::Opcode0x10() {

}

void NMOS6502::Opcode0x11() {

}

void NMOS6502::Opcode0x12() {

}

void NMOS6502::Opcode0x13() {

}

void NMOS6502::Opcode0x14() {

}

void NMOS6502::Opcode0x15() {

}

void NMOS6502::Opcode0x16() {

}

void NMOS6502::Opcode0x17() {

}

void NMOS6502::Opcode0x18() {

}

void NMOS6502::Opcode0x19() {

}

void NMOS6502::Opcode0x1A() {

}

void NMOS6502::Opcode0x1B() {

}

void NMOS6502::Opcode0x1C() {

}

void NMOS6502::Opcode0x1D() {

}

void NMOS6502::Opcode0x1E() {

}

void NMOS6502::Opcode0x1F() {

}

void NMOS6502::Opcode0x20() {

}

void NMOS6502::Opcode0x21() {

}

void NMOS6502::Opcode0x22() {

}

void NMOS6502::Opcode0x23() {

}

void NMOS6502::Opcode0x24() {

}

void NMOS6502::Opcode0x25() {

}

void NMOS6502::Opcode0x26() {

}

void NMOS6502::Opcode0x27() {

}

void NMOS6502::Opcode0x28() {

}

void NMOS6502::Opcode0x29() {

}

void NMOS6502::Opcode0x2A() {

}

void NMOS6502::Opcode0x2B() {

}

void NMOS6502::Opcode0x2C() {

}

void NMOS6502::Opcode0x2D() {

}

void NMOS6502::Opcode0x2E() {

}

void NMOS6502::Opcode0x2F() {

}

void NMOS6502::Opcode0x30() {

}

void NMOS6502::Opcode0x31() {

}

void NMOS6502::Opcode0x32() {

}

void NMOS6502::Opcode0x33() {

}

void NMOS6502::Opcode0x34() {

}

void NMOS6502::Opcode0x35() {

}

void NMOS6502::Opcode0x36() {

}

void NMOS6502::Opcode0x37() {

}

void NMOS6502::Opcode0x38() {

}

void NMOS6502::Opcode0x39() {

}

void NMOS6502::Opcode0x3A() {

}

void NMOS6502::Opcode0x3B() {

}

void NMOS6502::Opcode0x3C() {

}

void NMOS6502::Opcode0x3D() {

}

void NMOS6502::Opcode0x3E() {

}

void NMOS6502::Opcode0x3F() {

}

void NMOS6502::Opcode0x40() {

}

void NMOS6502::Opcode0x41() {

}

void NMOS6502::Opcode0x42() {

}

void NMOS6502::Opcode0x43() {

}

void NMOS6502::Opcode0x44() {

}

void NMOS6502::Opcode0x45() {

}

void NMOS6502::Opcode0x46() {

}

void NMOS6502::Opcode0x47() {

}

void NMOS6502::Opcode0x48() {

}

void NMOS6502::Opcode0x49() {

}

void NMOS6502::Opcode0x4A() {

}

void NMOS6502::Opcode0x4B() {

}

void NMOS6502::Opcode0x4C() {

}

void NMOS6502::Opcode0x4D() {

}

void NMOS6502::Opcode0x4E() {

}

void NMOS6502::Opcode0x4F() {

}

void NMOS6502::Opcode0x50() {

}

void NMOS6502::Opcode0x51() {

}

void NMOS6502::Opcode0x52() {

}

void NMOS6502::Opcode0x53() {

}

void NMOS6502::Opcode0x54() {

}

void NMOS6502::Opcode0x55() {

}

void NMOS6502::Opcode0x56() {

}

void NMOS6502::Opcode0x57() {

}

void NMOS6502::Opcode0x58() {

}

void NMOS6502::Opcode0x59() {

}

void NMOS6502::Opcode0x5A() {

}

void NMOS6502::Opcode0x5B() {

}

void NMOS6502::Opcode0x5C() {

}

void NMOS6502::Opcode0x5D() {

}

void NMOS6502::Opcode0x5E() {

}

void NMOS6502::Opcode0x5F() {

}

void NMOS6502::Opcode0x60() {

}

void NMOS6502::Opcode0x61() {

}

void NMOS6502::Opcode0x62() {

}

void NMOS6502::Opcode0x63() {

}

void NMOS6502::Opcode0x64() {

}

void NMOS6502::Opcode0x65() {

}

void NMOS6502::Opcode0x66() {

}

void NMOS6502::Opcode0x67() {

}

void NMOS6502::Opcode0x68() {

}

void NMOS6502::Opcode0x69() {

}

void NMOS6502::Opcode0x6A() {

}

void NMOS6502::Opcode0x6B() {

}

void NMOS6502::Opcode0x6C() {

}

void NMOS6502::Opcode0x6D() {

}

void NMOS6502::Opcode0x6E() {

}

void NMOS6502::Opcode0x6F() {

}

void NMOS6502::Opcode0x70() {

}

void NMOS6502::Opcode0x71() {

}

void NMOS6502::Opcode0x72() {

}

void NMOS6502::Opcode0x73() {

}

void NMOS6502::Opcode0x74() {

}

void NMOS6502::Opcode0x75() {

}

void NMOS6502::Opcode0x76() {

}

void NMOS6502::Opcode0x77() {

}

void NMOS6502::Opcode0x78() {

}

void NMOS6502::Opcode0x79() {

}

void NMOS6502::Opcode0x7A() {

}

void NMOS6502::Opcode0x7B() {

}

void NMOS6502::Opcode0x7C() {

}

void NMOS6502::Opcode0x7D() {

}

void NMOS6502::Opcode0x7E() {

}

void NMOS6502::Opcode0x7F() {

}

void NMOS6502::Opcode0x80() {

}

void NMOS6502::Opcode0x81() {

}

void NMOS6502::Opcode0x82() {

}

void NMOS6502::Opcode0x83() {

}

void NMOS6502::Opcode0x84() {

}

void NMOS6502::Opcode0x85() {

}

void NMOS6502::Opcode0x86() {

}

void NMOS6502::Opcode0x87() {

}

void NMOS6502::Opcode0x88() {

}

void NMOS6502::Opcode0x89() {

}

void NMOS6502::Opcode0x8A() {

}

void NMOS6502::Opcode0x8B() {

}

void NMOS6502::Opcode0x8C() {

}

void NMOS6502::Opcode0x8D() {

}

void NMOS6502::Opcode0x8E() {

}

void NMOS6502::Opcode0x8F() {

}

void NMOS6502::Opcode0x90() {

}

void NMOS6502::Opcode0x91() {

}

void NMOS6502::Opcode0x92() {

}

void NMOS6502::Opcode0x93() {

}

void NMOS6502::Opcode0x94() {

}

void NMOS6502::Opcode0x95() {

}

void NMOS6502::Opcode0x96() {

}

void NMOS6502::Opcode0x97() {

}

void NMOS6502::Opcode0x98() {

}

void NMOS6502::Opcode0x99() {

}

void NMOS6502::Opcode0x9A() {

}

void NMOS6502::Opcode0x9B() {

}

void NMOS6502::Opcode0x9C() {

}

void NMOS6502::Opcode0x9D() {

}

void NMOS6502::Opcode0x9E() {

}

void NMOS6502::Opcode0x9F() {

}

void NMOS6502::Opcode0xA0() {

}

void NMOS6502::Opcode0xA1() {
	u8 ZeroPage = FetchByte();
	u8 EffectiveAddress = ZeroPage + X; // Wrapping around when > 0xFF is intended behaviour
	Cycle();
	A = Memory[EffectiveAddress];
	Cycle();
}

void NMOS6502::Opcode0xA2() {

}

void NMOS6502::Opcode0xA3() {

}

void NMOS6502::Opcode0xA4() {

}

void NMOS6502::Opcode0xA5() {
	u8 ZeroPage = FetchByte();
	A = Memory[ZeroPage];
	Cycle();
}

void NMOS6502::Opcode0xA6() {

}

void NMOS6502::Opcode0xA7() {

}

void NMOS6502::Opcode0xA8() {

}

void NMOS6502::Opcode0xA9() {
	u8 imm = FetchByte();
	A = imm;
}

void NMOS6502::Opcode0xAA() {

}

void NMOS6502::Opcode0xAB() {

}

void NMOS6502::Opcode0xAC() {

}

void NMOS6502::Opcode0xAD() {
	u16 EffectiveAddress = FetchWord();
	A = Memory[EffectiveAddress];
	Cycle();
}

void NMOS6502::Opcode0xAE() {

}

void NMOS6502::Opcode0xAF() {

}

void NMOS6502::Opcode0xB0() {

}

void NMOS6502::Opcode0xB1() {

}

void NMOS6502::Opcode0xB2() {

}

void NMOS6502::Opcode0xB3() {

}

void NMOS6502::Opcode0xB4() {

}

void NMOS6502::Opcode0xB5() {

}

void NMOS6502::Opcode0xB6() {

}

void NMOS6502::Opcode0xB7() {

}

void NMOS6502::Opcode0xB8() {

}

void NMOS6502::Opcode0xB9() {
	u16 BaseAddress = FetchWord();
	u16 EffectiveAddress = BaseAddress + Y;
	if ((BaseAddress & 0xFF00) != (EffectiveAddress & 0xFF00)) { // Page boundary cross
		Cycle();
	}
	A = Memory[EffectiveAddress];
	Cycle();
}

void NMOS6502::Opcode0xBA() {

}

void NMOS6502::Opcode0xBB() {

}

void NMOS6502::Opcode0xBC() {

}

void NMOS6502::Opcode0xBD() {
	u16 BaseAddress = FetchWord();
	u16 EffectiveAddress = BaseAddress + X;
	if ((BaseAddress & 0xFF00) != (EffectiveAddress & 0xFF00)) { // Page boundary cross
		Cycle();
	}
	A = Memory[EffectiveAddress];
	Cycle();
}

void NMOS6502::Opcode0xBE() {

}

void NMOS6502::Opcode0xBF() {

}

void NMOS6502::Opcode0xC0() {

}

void NMOS6502::Opcode0xC1() {

}

void NMOS6502::Opcode0xC2() {

}

void NMOS6502::Opcode0xC3() {

}

void NMOS6502::Opcode0xC4() {

}

void NMOS6502::Opcode0xC5() {

}

void NMOS6502::Opcode0xC6() {

}

void NMOS6502::Opcode0xC7() {

}

void NMOS6502::Opcode0xC8() {

}

void NMOS6502::Opcode0xC9() {

}

void NMOS6502::Opcode0xCA() {

}

void NMOS6502::Opcode0xCB() {

}

void NMOS6502::Opcode0xCC() {

}

void NMOS6502::Opcode0xCD() {

}

void NMOS6502::Opcode0xCE() {

}

void NMOS6502::Opcode0xCF() {

}

void NMOS6502::Opcode0xD0() {

}

void NMOS6502::Opcode0xD1() {

}

void NMOS6502::Opcode0xD2() {

}

void NMOS6502::Opcode0xD3() {

}

void NMOS6502::Opcode0xD4() {

}

void NMOS6502::Opcode0xD5() {

}

void NMOS6502::Opcode0xD6() {

}

void NMOS6502::Opcode0xD7() {

}

void NMOS6502::Opcode0xD8() {

}

void NMOS6502::Opcode0xD9() {

}

void NMOS6502::Opcode0xDA() {

}

void NMOS6502::Opcode0xDB() {

}

void NMOS6502::Opcode0xDC() {

}

void NMOS6502::Opcode0xDD() {

}

void NMOS6502::Opcode0xDE() {

}

void NMOS6502::Opcode0xDF() {

}

void NMOS6502::Opcode0xE0() {

}

void NMOS6502::Opcode0xE1() {

}

void NMOS6502::Opcode0xE2() {

}

void NMOS6502::Opcode0xE3() {

}

void NMOS6502::Opcode0xE4() {

}

void NMOS6502::Opcode0xE5() {

}

void NMOS6502::Opcode0xE6() {

}

void NMOS6502::Opcode0xE7() {

}

void NMOS6502::Opcode0xE8() {

}

void NMOS6502::Opcode0xE9() {

}

void NMOS6502::Opcode0xEA() {

}

void NMOS6502::Opcode0xEB() {

}

void NMOS6502::Opcode0xEC() {

}

void NMOS6502::Opcode0xED() {

}

void NMOS6502::Opcode0xEE() {

}

void NMOS6502::Opcode0xEF() {

}

void NMOS6502::Opcode0xF0() {

}

void NMOS6502::Opcode0xF1() {

}

void NMOS6502::Opcode0xF2() {

}

void NMOS6502::Opcode0xF3() {

}

void NMOS6502::Opcode0xF4() {

}

void NMOS6502::Opcode0xF5() {

}

void NMOS6502::Opcode0xF6() {

}

void NMOS6502::Opcode0xF7() {

}

void NMOS6502::Opcode0xF8() {

}

void NMOS6502::Opcode0xF9() {

}

void NMOS6502::Opcode0xFA() {

}

void NMOS6502::Opcode0xFB() {

}

void NMOS6502::Opcode0xFC() {

}

void NMOS6502::Opcode0xFD() {

}

void NMOS6502::Opcode0xFE() {

}

void NMOS6502::Opcode0xFF() {

}

void NMOS6502::BindOpcodes() {
	this->Opcodes[0x00] = &NMOS6502::Opcode0x00;
	this->Opcodes[0x01] = &NMOS6502::Opcode0x01;
	this->Opcodes[0x02] = &NMOS6502::Opcode0x02;
	this->Opcodes[0x03] = &NMOS6502::Opcode0x03;
	this->Opcodes[0x04] = &NMOS6502::Opcode0x04;
	this->Opcodes[0x05] = &NMOS6502::Opcode0x05;
	this->Opcodes[0x06] = &NMOS6502::Opcode0x06;
	this->Opcodes[0x07] = &NMOS6502::Opcode0x07;
	this->Opcodes[0x08] = &NMOS6502::Opcode0x08;
	this->Opcodes[0x09] = &NMOS6502::Opcode0x09;
	this->Opcodes[0x0A] = &NMOS6502::Opcode0x0A;
	this->Opcodes[0x0B] = &NMOS6502::Opcode0x0B;
	this->Opcodes[0x0C] = &NMOS6502::Opcode0x0C;
	this->Opcodes[0x0D] = &NMOS6502::Opcode0x0D;
	this->Opcodes[0x0E] = &NMOS6502::Opcode0x0E;
	this->Opcodes[0x0F] = &NMOS6502::Opcode0x0F;
	this->Opcodes[0x10] = &NMOS6502::Opcode0x10;
	this->Opcodes[0x11] = &NMOS6502::Opcode0x11;
	this->Opcodes[0x12] = &NMOS6502::Opcode0x12;
	this->Opcodes[0x13] = &NMOS6502::Opcode0x13;
	this->Opcodes[0x14] = &NMOS6502::Opcode0x14;
	this->Opcodes[0x15] = &NMOS6502::Opcode0x15;
	this->Opcodes[0x16] = &NMOS6502::Opcode0x16;
	this->Opcodes[0x17] = &NMOS6502::Opcode0x17;
	this->Opcodes[0x18] = &NMOS6502::Opcode0x18;
	this->Opcodes[0x19] = &NMOS6502::Opcode0x19;
	this->Opcodes[0x1A] = &NMOS6502::Opcode0x1A;
	this->Opcodes[0x1B] = &NMOS6502::Opcode0x1B;
	this->Opcodes[0x1C] = &NMOS6502::Opcode0x1C;
	this->Opcodes[0x1D] = &NMOS6502::Opcode0x1D;
	this->Opcodes[0x1E] = &NMOS6502::Opcode0x1E;
	this->Opcodes[0x1F] = &NMOS6502::Opcode0x1F;
	this->Opcodes[0x20] = &NMOS6502::Opcode0x20;
	this->Opcodes[0x21] = &NMOS6502::Opcode0x21;
	this->Opcodes[0x22] = &NMOS6502::Opcode0x22;
	this->Opcodes[0x23] = &NMOS6502::Opcode0x23;
	this->Opcodes[0x24] = &NMOS6502::Opcode0x24;
	this->Opcodes[0x25] = &NMOS6502::Opcode0x25;
	this->Opcodes[0x26] = &NMOS6502::Opcode0x26;
	this->Opcodes[0x27] = &NMOS6502::Opcode0x27;
	this->Opcodes[0x28] = &NMOS6502::Opcode0x28;
	this->Opcodes[0x29] = &NMOS6502::Opcode0x29;
	this->Opcodes[0x2A] = &NMOS6502::Opcode0x2A;
	this->Opcodes[0x2B] = &NMOS6502::Opcode0x2B;
	this->Opcodes[0x2C] = &NMOS6502::Opcode0x2C;
	this->Opcodes[0x2D] = &NMOS6502::Opcode0x2D;
	this->Opcodes[0x2E] = &NMOS6502::Opcode0x2E;
	this->Opcodes[0x2F] = &NMOS6502::Opcode0x2F;
	this->Opcodes[0x30] = &NMOS6502::Opcode0x30;
	this->Opcodes[0x31] = &NMOS6502::Opcode0x31;
	this->Opcodes[0x32] = &NMOS6502::Opcode0x32;
	this->Opcodes[0x33] = &NMOS6502::Opcode0x33;
	this->Opcodes[0x34] = &NMOS6502::Opcode0x34;
	this->Opcodes[0x35] = &NMOS6502::Opcode0x35;
	this->Opcodes[0x36] = &NMOS6502::Opcode0x36;
	this->Opcodes[0x37] = &NMOS6502::Opcode0x37;
	this->Opcodes[0x38] = &NMOS6502::Opcode0x38;
	this->Opcodes[0x39] = &NMOS6502::Opcode0x39;
	this->Opcodes[0x3A] = &NMOS6502::Opcode0x3A;
	this->Opcodes[0x3B] = &NMOS6502::Opcode0x3B;
	this->Opcodes[0x3C] = &NMOS6502::Opcode0x3C;
	this->Opcodes[0x3D] = &NMOS6502::Opcode0x3D;
	this->Opcodes[0x3E] = &NMOS6502::Opcode0x3E;
	this->Opcodes[0x3F] = &NMOS6502::Opcode0x3F;
	this->Opcodes[0x40] = &NMOS6502::Opcode0x40;
	this->Opcodes[0x41] = &NMOS6502::Opcode0x41;
	this->Opcodes[0x42] = &NMOS6502::Opcode0x42;
	this->Opcodes[0x43] = &NMOS6502::Opcode0x43;
	this->Opcodes[0x44] = &NMOS6502::Opcode0x44;
	this->Opcodes[0x45] = &NMOS6502::Opcode0x45;
	this->Opcodes[0x46] = &NMOS6502::Opcode0x46;
	this->Opcodes[0x47] = &NMOS6502::Opcode0x47;
	this->Opcodes[0x48] = &NMOS6502::Opcode0x48;
	this->Opcodes[0x49] = &NMOS6502::Opcode0x49;
	this->Opcodes[0x4A] = &NMOS6502::Opcode0x4A;
	this->Opcodes[0x4B] = &NMOS6502::Opcode0x4B;
	this->Opcodes[0x4C] = &NMOS6502::Opcode0x4C;
	this->Opcodes[0x4D] = &NMOS6502::Opcode0x4D;
	this->Opcodes[0x4E] = &NMOS6502::Opcode0x4E;
	this->Opcodes[0x4F] = &NMOS6502::Opcode0x4F;
	this->Opcodes[0x50] = &NMOS6502::Opcode0x50;
	this->Opcodes[0x51] = &NMOS6502::Opcode0x51;
	this->Opcodes[0x52] = &NMOS6502::Opcode0x52;
	this->Opcodes[0x53] = &NMOS6502::Opcode0x53;
	this->Opcodes[0x54] = &NMOS6502::Opcode0x54;
	this->Opcodes[0x55] = &NMOS6502::Opcode0x55;
	this->Opcodes[0x56] = &NMOS6502::Opcode0x56;
	this->Opcodes[0x57] = &NMOS6502::Opcode0x57;
	this->Opcodes[0x58] = &NMOS6502::Opcode0x58;
	this->Opcodes[0x59] = &NMOS6502::Opcode0x59;
	this->Opcodes[0x5A] = &NMOS6502::Opcode0x5A;
	this->Opcodes[0x5B] = &NMOS6502::Opcode0x5B;
	this->Opcodes[0x5C] = &NMOS6502::Opcode0x5C;
	this->Opcodes[0x5D] = &NMOS6502::Opcode0x5D;
	this->Opcodes[0x5E] = &NMOS6502::Opcode0x5E;
	this->Opcodes[0x5F] = &NMOS6502::Opcode0x5F;
	this->Opcodes[0x60] = &NMOS6502::Opcode0x60;
	this->Opcodes[0x61] = &NMOS6502::Opcode0x61;
	this->Opcodes[0x62] = &NMOS6502::Opcode0x62;
	this->Opcodes[0x63] = &NMOS6502::Opcode0x63;
	this->Opcodes[0x64] = &NMOS6502::Opcode0x64;
	this->Opcodes[0x65] = &NMOS6502::Opcode0x65;
	this->Opcodes[0x66] = &NMOS6502::Opcode0x66;
	this->Opcodes[0x67] = &NMOS6502::Opcode0x67;
	this->Opcodes[0x68] = &NMOS6502::Opcode0x68;
	this->Opcodes[0x69] = &NMOS6502::Opcode0x69;
	this->Opcodes[0x6A] = &NMOS6502::Opcode0x6A;
	this->Opcodes[0x6B] = &NMOS6502::Opcode0x6B;
	this->Opcodes[0x6C] = &NMOS6502::Opcode0x6C;
	this->Opcodes[0x6D] = &NMOS6502::Opcode0x6D;
	this->Opcodes[0x6E] = &NMOS6502::Opcode0x6E;
	this->Opcodes[0x6F] = &NMOS6502::Opcode0x6F;
	this->Opcodes[0x70] = &NMOS6502::Opcode0x70;
	this->Opcodes[0x71] = &NMOS6502::Opcode0x71;
	this->Opcodes[0x72] = &NMOS6502::Opcode0x72;
	this->Opcodes[0x73] = &NMOS6502::Opcode0x73;
	this->Opcodes[0x74] = &NMOS6502::Opcode0x74;
	this->Opcodes[0x75] = &NMOS6502::Opcode0x75;
	this->Opcodes[0x76] = &NMOS6502::Opcode0x76;
	this->Opcodes[0x77] = &NMOS6502::Opcode0x77;
	this->Opcodes[0x78] = &NMOS6502::Opcode0x78;
	this->Opcodes[0x79] = &NMOS6502::Opcode0x79;
	this->Opcodes[0x7A] = &NMOS6502::Opcode0x7A;
	this->Opcodes[0x7B] = &NMOS6502::Opcode0x7B;
	this->Opcodes[0x7C] = &NMOS6502::Opcode0x7C;
	this->Opcodes[0x7D] = &NMOS6502::Opcode0x7D;
	this->Opcodes[0x7E] = &NMOS6502::Opcode0x7E;
	this->Opcodes[0x7F] = &NMOS6502::Opcode0x7F;
	this->Opcodes[0x80] = &NMOS6502::Opcode0x80;
	this->Opcodes[0x81] = &NMOS6502::Opcode0x81;
	this->Opcodes[0x82] = &NMOS6502::Opcode0x82;
	this->Opcodes[0x83] = &NMOS6502::Opcode0x83;
	this->Opcodes[0x84] = &NMOS6502::Opcode0x84;
	this->Opcodes[0x85] = &NMOS6502::Opcode0x85;
	this->Opcodes[0x86] = &NMOS6502::Opcode0x86;
	this->Opcodes[0x87] = &NMOS6502::Opcode0x87;
	this->Opcodes[0x88] = &NMOS6502::Opcode0x88;
	this->Opcodes[0x89] = &NMOS6502::Opcode0x89;
	this->Opcodes[0x8A] = &NMOS6502::Opcode0x8A;
	this->Opcodes[0x8B] = &NMOS6502::Opcode0x8B;
	this->Opcodes[0x8C] = &NMOS6502::Opcode0x8C;
	this->Opcodes[0x8D] = &NMOS6502::Opcode0x8D;
	this->Opcodes[0x8E] = &NMOS6502::Opcode0x8E;
	this->Opcodes[0x8F] = &NMOS6502::Opcode0x8F;
	this->Opcodes[0x90] = &NMOS6502::Opcode0x90;
	this->Opcodes[0x91] = &NMOS6502::Opcode0x91;
	this->Opcodes[0x92] = &NMOS6502::Opcode0x92;
	this->Opcodes[0x93] = &NMOS6502::Opcode0x93;
	this->Opcodes[0x94] = &NMOS6502::Opcode0x94;
	this->Opcodes[0x95] = &NMOS6502::Opcode0x95;
	this->Opcodes[0x96] = &NMOS6502::Opcode0x96;
	this->Opcodes[0x97] = &NMOS6502::Opcode0x97;
	this->Opcodes[0x98] = &NMOS6502::Opcode0x98;
	this->Opcodes[0x99] = &NMOS6502::Opcode0x99;
	this->Opcodes[0x9A] = &NMOS6502::Opcode0x9A;
	this->Opcodes[0x9B] = &NMOS6502::Opcode0x9B;
	this->Opcodes[0x9C] = &NMOS6502::Opcode0x9C;
	this->Opcodes[0x9D] = &NMOS6502::Opcode0x9D;
	this->Opcodes[0x9E] = &NMOS6502::Opcode0x9E;
	this->Opcodes[0x9F] = &NMOS6502::Opcode0x9F;
	this->Opcodes[0xA0] = &NMOS6502::Opcode0xA0;
	this->Opcodes[0xA1] = &NMOS6502::Opcode0xA1;
	this->Opcodes[0xA2] = &NMOS6502::Opcode0xA2;
	this->Opcodes[0xA3] = &NMOS6502::Opcode0xA3;
	this->Opcodes[0xA4] = &NMOS6502::Opcode0xA4;
	this->Opcodes[0xA5] = &NMOS6502::Opcode0xA5;
	this->Opcodes[0xA6] = &NMOS6502::Opcode0xA6;
	this->Opcodes[0xA7] = &NMOS6502::Opcode0xA7;
	this->Opcodes[0xA8] = &NMOS6502::Opcode0xA8;
	this->Opcodes[0xA9] = &NMOS6502::Opcode0xA9;
	this->Opcodes[0xAA] = &NMOS6502::Opcode0xAA;
	this->Opcodes[0xAB] = &NMOS6502::Opcode0xAB;
	this->Opcodes[0xAC] = &NMOS6502::Opcode0xAC;
	this->Opcodes[0xAD] = &NMOS6502::Opcode0xAD;
	this->Opcodes[0xAE] = &NMOS6502::Opcode0xAE;
	this->Opcodes[0xAF] = &NMOS6502::Opcode0xAF;
	this->Opcodes[0xB0] = &NMOS6502::Opcode0xB0;
	this->Opcodes[0xB1] = &NMOS6502::Opcode0xB1;
	this->Opcodes[0xB2] = &NMOS6502::Opcode0xB2;
	this->Opcodes[0xB3] = &NMOS6502::Opcode0xB3;
	this->Opcodes[0xB4] = &NMOS6502::Opcode0xB4;
	this->Opcodes[0xB5] = &NMOS6502::Opcode0xB5;
	this->Opcodes[0xB6] = &NMOS6502::Opcode0xB6;
	this->Opcodes[0xB7] = &NMOS6502::Opcode0xB7;
	this->Opcodes[0xB8] = &NMOS6502::Opcode0xB8;
	this->Opcodes[0xB9] = &NMOS6502::Opcode0xB9;
	this->Opcodes[0xBA] = &NMOS6502::Opcode0xBA;
	this->Opcodes[0xBB] = &NMOS6502::Opcode0xBB;
	this->Opcodes[0xBC] = &NMOS6502::Opcode0xBC;
	this->Opcodes[0xBD] = &NMOS6502::Opcode0xBD;
	this->Opcodes[0xBE] = &NMOS6502::Opcode0xBE;
	this->Opcodes[0xBF] = &NMOS6502::Opcode0xBF;
	this->Opcodes[0xC0] = &NMOS6502::Opcode0xC0;
	this->Opcodes[0xC1] = &NMOS6502::Opcode0xC1;
	this->Opcodes[0xC2] = &NMOS6502::Opcode0xC2;
	this->Opcodes[0xC3] = &NMOS6502::Opcode0xC3;
	this->Opcodes[0xC4] = &NMOS6502::Opcode0xC4;
	this->Opcodes[0xC5] = &NMOS6502::Opcode0xC5;
	this->Opcodes[0xC6] = &NMOS6502::Opcode0xC6;
	this->Opcodes[0xC7] = &NMOS6502::Opcode0xC7;
	this->Opcodes[0xC8] = &NMOS6502::Opcode0xC8;
	this->Opcodes[0xC9] = &NMOS6502::Opcode0xC9;
	this->Opcodes[0xCA] = &NMOS6502::Opcode0xCA;
	this->Opcodes[0xCB] = &NMOS6502::Opcode0xCB;
	this->Opcodes[0xCC] = &NMOS6502::Opcode0xCC;
	this->Opcodes[0xCD] = &NMOS6502::Opcode0xCD;
	this->Opcodes[0xCE] = &NMOS6502::Opcode0xCE;
	this->Opcodes[0xCF] = &NMOS6502::Opcode0xCF;
	this->Opcodes[0xD0] = &NMOS6502::Opcode0xD0;
	this->Opcodes[0xD1] = &NMOS6502::Opcode0xD1;
	this->Opcodes[0xD2] = &NMOS6502::Opcode0xD2;
	this->Opcodes[0xD3] = &NMOS6502::Opcode0xD3;
	this->Opcodes[0xD4] = &NMOS6502::Opcode0xD4;
	this->Opcodes[0xD5] = &NMOS6502::Opcode0xD5;
	this->Opcodes[0xD6] = &NMOS6502::Opcode0xD6;
	this->Opcodes[0xD7] = &NMOS6502::Opcode0xD7;
	this->Opcodes[0xD8] = &NMOS6502::Opcode0xD8;
	this->Opcodes[0xD9] = &NMOS6502::Opcode0xD9;
	this->Opcodes[0xDA] = &NMOS6502::Opcode0xDA;
	this->Opcodes[0xDB] = &NMOS6502::Opcode0xDB;
	this->Opcodes[0xDC] = &NMOS6502::Opcode0xDC;
	this->Opcodes[0xDD] = &NMOS6502::Opcode0xDD;
	this->Opcodes[0xDE] = &NMOS6502::Opcode0xDE;
	this->Opcodes[0xDF] = &NMOS6502::Opcode0xDF;
	this->Opcodes[0xE0] = &NMOS6502::Opcode0xE0;
	this->Opcodes[0xE1] = &NMOS6502::Opcode0xE1;
	this->Opcodes[0xE2] = &NMOS6502::Opcode0xE2;
	this->Opcodes[0xE3] = &NMOS6502::Opcode0xE3;
	this->Opcodes[0xE4] = &NMOS6502::Opcode0xE4;
	this->Opcodes[0xE5] = &NMOS6502::Opcode0xE5;
	this->Opcodes[0xE6] = &NMOS6502::Opcode0xE6;
	this->Opcodes[0xE7] = &NMOS6502::Opcode0xE7;
	this->Opcodes[0xE8] = &NMOS6502::Opcode0xE8;
	this->Opcodes[0xE9] = &NMOS6502::Opcode0xE9;
	this->Opcodes[0xEA] = &NMOS6502::Opcode0xEA;
	this->Opcodes[0xEB] = &NMOS6502::Opcode0xEB;
	this->Opcodes[0xEC] = &NMOS6502::Opcode0xEC;
	this->Opcodes[0xED] = &NMOS6502::Opcode0xED;
	this->Opcodes[0xEE] = &NMOS6502::Opcode0xEE;
	this->Opcodes[0xEF] = &NMOS6502::Opcode0xEF;
	this->Opcodes[0xF0] = &NMOS6502::Opcode0xF0;
	this->Opcodes[0xF1] = &NMOS6502::Opcode0xF1;
	this->Opcodes[0xF2] = &NMOS6502::Opcode0xF2;
	this->Opcodes[0xF3] = &NMOS6502::Opcode0xF3;
	this->Opcodes[0xF4] = &NMOS6502::Opcode0xF4;
	this->Opcodes[0xF5] = &NMOS6502::Opcode0xF5;
	this->Opcodes[0xF6] = &NMOS6502::Opcode0xF6;
	this->Opcodes[0xF7] = &NMOS6502::Opcode0xF7;
	this->Opcodes[0xF8] = &NMOS6502::Opcode0xF8;
	this->Opcodes[0xF9] = &NMOS6502::Opcode0xF9;
	this->Opcodes[0xFA] = &NMOS6502::Opcode0xFA;
	this->Opcodes[0xFB] = &NMOS6502::Opcode0xFB;
	this->Opcodes[0xFC] = &NMOS6502::Opcode0xFC;
	this->Opcodes[0xFD] = &NMOS6502::Opcode0xFD;
	this->Opcodes[0xFE] = &NMOS6502::Opcode0xFE;
	this->Opcodes[0xFF] = &NMOS6502::Opcode0xFF;
}