#pragma once
#include "AbstractDeclarations.hpp"

class AbstractMemoryDevice
{
	protected:
	void readFromROM(sAbstractFread reader, bool allowResize);
	public:
	virtual void* accessMemoryAt(size_t offset) = 0;
	virtual size_t getMemorySize() const = 0;
	virtual void resizeMemory(size_t setto) = 0;
	void dumpMemory(sAbstractFwrite writer);
	template<typename T> T* castMemoryAccessAt(size_t offset)
	{
		return reinterpret_cast<T*>(accessMemoryAt(offset));
	}
};
