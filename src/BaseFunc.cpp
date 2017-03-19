#include "include/BaseFunc.hpp"

uint64_t quickpow(uint64_t base, uint64_t power)
{
	uint64_t temp = base;
	uint64_t i;
	for(i = 1;i < power;++i) temp *= temp;
	return temp;
}

template <typename T> T fullone()
{
	T temp;
	unsigned char* temp_ptr = &temp;
	for(int i = 0;i < sizeof(T);++i) temp_ptr[i] = 0xFF;
	return temp;
}
