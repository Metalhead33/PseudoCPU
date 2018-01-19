#pragma once
#include "include/abstract/AbstractMemoryDevice.hpp"
#include <vector>

class SharedMemoryBuffer : public AbstractMemoryDevice
{
public:
	typedef std::vector<uint8_t> ByteBuffer;
	typedef std::shared_ptr<ByteBuffer> SharedBuffer;
private:
	SharedBuffer buf;
public:
	virtual void* accessMemoryAt(size_t offset);
	virtual size_t getMemorySize() const;
	virtual void resizeMemory(size_t setto);
	SharedMemoryBuffer(size_t size);
	SharedMemoryBuffer(ByteBuffer& orbuff);
	SharedMemoryBuffer(SharedBuffer orbuff);
};
