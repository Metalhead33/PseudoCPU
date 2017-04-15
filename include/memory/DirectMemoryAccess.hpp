#ifndef DIRECTMEMORYACCESS_HPP
#define DIRECTMEMORYACCESS_HPP
#include "abstract/AbstractMemoryHandler.hpp"
namespace Psecom {
namespace Memory {
DEFINE_CLASS(DirectMemoryAccess)

class DirectMemoryAccess : public AbstractMemoryHandler
{
private:
	uint8_t* start;
	size_t size;
	bool loop;
public:
	void* AccessMemoryAt(size_t loc);
	DirectMemoryAccess(void* memstart, size_t memsize, bool loopornot=false);
	DirectMemoryAccess(SharedMemory memblock, size_t memstart, size_t memsize, bool loopornot=false);


	bool GetLoop();
	void SetLoop(bool setto);
	size_t GetSize();
	void* GetStart();
};
}
}
#endif // DIRECTMEMORYACCESS_HPP
