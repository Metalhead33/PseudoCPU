#include "include/abstract/AbstractMemoryDevice.hpp"
#include "include/abstract/AbstractFread.hpp"
#include "include/abstract/AbstractFwrite.hpp"

void AbstractMemoryDevice::dumpMemory(sAbstractFwrite writer)
{
	writer->write(accessMemoryAt(0),getMemorySize());
}
void AbstractMemoryDevice::readFromROM(sAbstractFread reader, bool allowResize)
{
	if(allowResize)
	{
		if(getMemorySize() < reader->size()) resizeMemory(reader->size());
		reader->read(accessMemoryAt(0),reader->size());
	}
	else
	{
		if(getMemorySize() < reader->size()) reader->read(accessMemoryAt(0),getMemorySize());
		else reader->read(accessMemoryAt(0),reader->size());
	}
}
