#include "include/DirectMemoryAccess.hpp"

DirectMemoryAccess::DirectMemoryAccess(SharedMemory memblock,size_t start, size_t end)
{
	mem_start = &memblock->at(start);
	memsize = end - start;
}
DirectMemoryAccess::DirectMemoryAccess(void* memblock,size_t size)
{
	mem_start = static_cast<uint8_t*>(memblock);
	memsize = size;
}
uint8_t* DirectMemoryAccess::AccessMemory(size_t offset)
{
	return mem_start + offset;
}
