#ifndef BITBUFFER_H
#define BITBUFFER_H
#include <cstdint>

template <typename T> union BitBuffer
{
	T org;
	uint8_t buf[sizeof(T)];
};

#endif // BITBUFFER_H
