#pragma once
#include <iostream>
#include <cstdint>
#include <vector>
#include <algorithm>

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;

class NMOS6502 {
public:
	NMOS6502();
	~NMOS6502();
	std::vector<u8> Memory;
	u8 A, X, Y;
	u16 SP, PC;

	void Reset();
};