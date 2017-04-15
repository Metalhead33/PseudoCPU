#include "memory/DirectMemoryAccess.hpp"
#include <stdexcept>
namespace Psecom {
namespace Memory {

DirectMemoryAccess::DirectMemoryAccess(void* memstart, size_t memsize, bool loopornot)
{
	start = static_cast<uint8_t*>(memstart);
	size = memsize;
	loop = loopornot;
}
DirectMemoryAccess::DirectMemoryAccess(SharedMemory memblock, size_t memstart, size_t memsize, bool loopornot)
{
	start = static_cast<u_int8_t*>(&memblock->at(memstart));
	size = memsize;
	loop = loopornot;
}
void* DirectMemoryAccess::AccessMemoryAt(size_t loc)
{
	if(loop)
	{
		return static_cast<void*>(&start[loc % size]);
	}
	else {
	if(loc >= size) throw std::out_of_range("Location larger than size of memory space.");
	else return static_cast<void*>(&start[loc]);
	}
}
bool DirectMemoryAccess::GetLoop()
{
	return loop;
}
void DirectMemoryAccess::SetLoop(bool setto)
{
	loop = setto;
}
size_t DirectMemoryAccess::GetSize()
{
	return size;
}
void* DirectMemoryAccess::GetStart()
{
	return static_cast<void*>(start);
}

}
}
