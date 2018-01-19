#include "include/mem/SharedMemoryBuffer.hpp"
#include <cstring>

void* SharedMemoryBuffer::accessMemoryAt(size_t offset)
{
	return &(buf->at(offset));
}
size_t SharedMemoryBuffer::getMemorySize() const
{
	return buf->size();
}
void SharedMemoryBuffer::resizeMemory(size_t setto)
{
	buf->resize(setto);
}
SharedMemoryBuffer::SharedMemoryBuffer(size_t size)
	: buf(new ByteBuffer(size))
{
	;
}
SharedMemoryBuffer::SharedMemoryBuffer(ByteBuffer& orbuff)
	: buf(new ByteBuffer(orbuff.size()))
{
	memcpy(buf->data(),orbuff.data(),orbuff.size());
}
SharedMemoryBuffer::SharedMemoryBuffer(SharedBuffer orbuff)
	: buf(orbuff)
{
	;
}
