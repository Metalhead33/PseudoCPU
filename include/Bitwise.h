#ifndef BITWISE_H
#define BITWISE_H
#include <stdint.h>
/*uint8_t exact_bits[] = {
	0x80, // 1000 0000
	0x40, // 0100 0000
	0x20, // 0010 0000
	0x10, // 0001 0000
	0x08, // 0000 1000
	0x04, // 0000 0100
	0x02, // 0000 0010
	0x01 // 0000 0001
};*/

const uint8_t GetExactBit(uint8_t pos);
uint8_t CheckBit(uint8_t byte, uint8_t pos);

uint8_t PackBits(uint8_t* booleans);
uint8_t* ExtractBits(uint8_t byte);

void ChangeBitP(uint8_t* byte_ptr, uint8_t pos, uint8_t val);
uint8_t ChangeBitA(uint8_t base, uint8_t pos, uint8_t val);

#endif
