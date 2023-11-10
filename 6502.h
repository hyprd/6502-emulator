#pragma once
#include <iostream>
#include <cstdint>

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;

class NMOS6502 {
public:
	NMOS6502();
	~NMOS6502();
	u8 Memory[1024 * 16];
};