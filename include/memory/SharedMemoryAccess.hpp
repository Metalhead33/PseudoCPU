#ifndef SHAREDMEMORYACCESS_HPP
#define SHAREDMEMORYACCESS_HPP
#include "abstract/AbstractMemoryHandler.hpp"
#include "abstract/AbstractFread.hpp"
#include "abstract/AbstractFwrite.hpp"
#include "DirectMemoryAccess.hpp"
namespace Psecom {
namespace Memory {
DEFINE_CLASS(SharedMemoryAccess)

class SharedMemoryAccess : public AbstractMemoryHandler
{
private:
	SharedMemory memspace;
	bool loop;
public:
	void* AccessMemoryAt(size_t loc);
	bool GetLoop();
	void SetLoop(bool setto);
	size_t GetSize();
	void MemoryDump(Io::sAbstractFwrite writer);
	SharedMemoryAccess(size_t memsize, bool loopornot=false); // New memory from scratch
	SharedMemoryAccess(const uint8_t* extmem, size_t memsize, bool loopornot=false); // Copying from existing memory
	SharedMemoryAccess(SharedMemory extmem, bool loopornot=false); // Sharing memory with another container
	SharedMemoryAccess(Io::sAbstractFread reader, bool loopornot=false); // Reading from a file

	sDirectMemoryAccess GrantDMA(size_t beginning, size_t size, bool loopornot=false);
	SharedMemory GetMemspace();
};

}
}

#endif // SHAREDMEMORYACCESS_HPP
