#ifndef DIRECTMEMORYACCESS_HPP
#define DIRECTMEMORYACCESS_HPP
#include "Global.hpp"
DEFINE_CLASS(DirectMemoryAccess)

class DirectMemoryAccess
{
private:
	uint8_t* mem_start;
	size_t memsize;
public:
	DirectMemoryAccess(SharedMemory memblock,size_t start, size_t end);
	DirectMemoryAccess(void* memblock,size_t size);
	uint8_t* AccessMemory(size_t offset);
	template <typename T> T* CastMemory(size_t offset) { return static_cast<T*>(AccessMemory(offset));}
};

#endif // DIRECTMEMORYACCESS_HPP
