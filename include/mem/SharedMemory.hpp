#ifndef SHAREDMEMORY_HPP
#define SHAREDMEMORY_HPP
#include <vector>
#include "Bitbuffer.hpp"
#include <memory>
#include "include/abstract/AbstractFread.hpp"
#include "include/abstract/AbstractFwrite.hpp"

class SharedMemory;
typedef std::shared_ptr<SharedMemory> SharedMemoryBuffer;

class SharedMemory
{
private:
	std::vector<uint8_t> memoryBuffer;
public:
	SharedMemory(size_t size);
	SharedMemory(pAbstractFread reader);
	SharedMemory(sAbstractFread reader);
	void dumpMemory(pAbstractFwrite writer);
	void dumpMemory(sAbstractFwrite writer);
	void resize(size_t newsize);
	void* getByteAddress(size_t offset);
};

#endif // SHAREDMEMORY_HPP
