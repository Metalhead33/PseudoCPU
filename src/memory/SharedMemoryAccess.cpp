#include "memory/SharedMemoryAccess.hpp"

namespace Psecom {
namespace Memory {

void* SharedMemoryAccess::AccessMemoryAt(size_t loc)
{
	if(loop) return static_cast<void*>(&memspace->at(loc % memspace->size()));
	else
	{
		if(loc >= memspace->size())
		{
			std::string error = "Location (" + std::to_string(loc) + ") is larger than the size of memory space (" + std::to_string(memspace->size()) + ").";
			throw std::out_of_range(error);
		}
		else return static_cast<void*>(&memspace->at(loc));
	}
}
bool SharedMemoryAccess::GetLoop()
{
	return loop;
}
void SharedMemoryAccess::SetLoop(bool setto)
{
	loop = setto;
}
size_t SharedMemoryAccess::GetSize()
{
	return memspace->size();
}

void SharedMemoryAccess::MemoryDump(Io::sAbstractFwrite writer)
{
	writer->write(AccessMemoryAt(0),memspace->size());
}
SharedMemoryAccess::SharedMemoryAccess(size_t memsize, bool loopornot)
	: memspace(new RawMemoryBuffer(memsize))
{
	loop = loopornot;
	for(size_t i = 0;i < memsize;++i) memspace->at(i) = 0;
}
SharedMemoryAccess::SharedMemoryAccess(const uint8_t* extmem, size_t memsize, bool loopornot)
	: memspace(new RawMemoryBuffer(memsize))
{
	loop = loopornot;
	for(size_t i = 0;i < memsize;++i) memspace->at(i) = extmem[i];
}
SharedMemoryAccess::SharedMemoryAccess(SharedMemory extmem, bool loopornot)
	: memspace(extmem)
{
	loop = loopornot;
}
SharedMemoryAccess::SharedMemoryAccess(Io::sAbstractFread reader, bool loopornot)
	: memspace(new RawMemoryBuffer(reader->size() ))
{
	reader->read(AccessMemoryAt(0),reader->size());
	loop = loopornot;
}
sDirectMemoryAccess SharedMemoryAccess::GrantDMA(size_t beginning, size_t size, bool loopornot)
{
	return sDirectMemoryAccess(new DirectMemoryAccess(memspace,beginning,size,loopornot));
}
SharedMemory SharedMemoryAccess::GetMemspace()
{
	return memspace;
}

}
}
