#include "Bitwise.h"
#include <stdlib.h>
const uint8_t GetExactBit(uint8_t pos)
{
	return (0x80 >> (pos % 8));
}

uint8_t CheckBit(uint8_t byte, uint8_t pos)
{
	return ((byte & (0x80 >> (pos % 8))) != 0);
}

uint8_t PackBits(uint8_t* booleans)
{
	int i;
	uint8_t tmp = 0;
	for(i = 0;i < 8;++i)
	{
		if(booleans[i]) tmp = tmp | (0x80 >> (i % 8));
	}
	return tmp;
}
uint8_t* ExtractBits(uint8_t byte)
{
	int i;
	uint8_t* temp = (uint8_t*)malloc(sizeof(uint8_t) * 8);
	for(i = 0;i < 8;++i) temp[i] = CheckBit(byte,i);
	return temp;
}

void ChangeBitP(uint8_t* byte_ptr, uint8_t pos, uint8_t val)
{
	if(val) *byte_ptr = *byte_ptr | (0x80 >> (pos % 8));
	else *byte_ptr = ~(~(*byte_ptr) | (0x80 >> (pos % 8)));
}
uint8_t ChangeBitA(uint8_t base, uint8_t pos, uint8_t val)
{
	uint8_t tmp = base;
	ChangeBitP(&tmp,pos,val);
	return tmp;
}
