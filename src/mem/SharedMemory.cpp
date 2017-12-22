#include "include/mem/SharedMemory.hpp"

SharedMemory::SharedMemory(size_t size)
	: memoryBuffer(size)
{
	;
}
SharedMemory::SharedMemory(pAbstractFread reader)
	: memoryBuffer(reader->size())
{
	reader->read(memoryBuffer.data(),reader->size());
}
SharedMemory::SharedMemory(sAbstractFread reader)
	: memoryBuffer(reader->size())
{
	reader->read(memoryBuffer.data(),reader->size());
}
void SharedMemory::dumpMemory(pAbstractFwrite writer)
{
	writer->write(memoryBuffer.data(),memoryBuffer.size());
}
void SharedMemory::dumpMemory(sAbstractFwrite writer)
{
	writer->write(memoryBuffer.data(),memoryBuffer.size());
}
void SharedMemory::resize(size_t newsize)
{
	memoryBuffer.resize(newsize);
}
void* SharedMemory::getByteAddress(size_t offset)
{
	return &(memoryBuffer[offset]);
}
