#ifndef ABSTRACTMEMORYHANDLER_HPP
#define ABSTRACTMEMORYHANDLER_HPP
#include <memory>
#include <cstdint>
#include "Global.hpp"
namespace Psecom {
namespace Memory {
DEFINE_CLASS(AbstractMemoryHandler)

class AbstractMemoryHandler
{
public:
	virtual void* AccessMemoryAt(size_t loc) = 0;
	virtual size_t GetSize() = 0;
	template <typename T> T* CastAccessAt(size_t loc) { return static_cast<T*>(AccessMemoryAt(loc)); }
	template <typename T> T CastAccessData(size_t loc) { return *(CastAccessAt<T>(loc)); }

	// Copying - byte by byte
	void MemoryCopy(size_t destination, void* origin, size_t size);
	void MemoryCopy(size_t destination, size_t origin, size_t size);

	// Bitwise operations
	bool MemCheckBit(size_t byte, uint8_t pos);
	void MemPackBits(size_t byte, uint8_t* booleans);
	bool* MemExtractBits(size_t byte);
	void MemChangeBitP(size_t byte_ptr, uint8_t pos, bool val);
};
}
}
#endif // ABSTRACTMEMORYHANDLER_HPP
