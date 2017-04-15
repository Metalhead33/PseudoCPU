#include "abstract/AbstractMemoryHandler.hpp"
extern "C" {
#include "Bitwise.h"
}
#include <cstdlib>
#include <cstring>
namespace Psecom {
namespace Memory {

/*AbstractMemoryHandler::AbstractMemoryHandler()
{

}*/
void AbstractMemoryHandler::MemoryCopy(size_t destination, void* origin, size_t size)
{
	memcpy(AccessMemoryAt(destination),origin,size);
}
void AbstractMemoryHandler::MemoryCopy(size_t destination, size_t origin, size_t size)
{
	memcpy(AccessMemoryAt(destination),AccessMemoryAt(origin),size);
}

bool AbstractMemoryHandler::MemCheckBit(size_t byte, uint8_t pos)
{
	return (bool)CheckBit(CastAccessData<uint8_t>(byte),pos);
}
void AbstractMemoryHandler::MemPackBits(size_t byte, uint8_t* booleans)
{
	*(CastAccessAt<uint8_t>(byte)) = PackBits(booleans);
}
bool* AbstractMemoryHandler::MemExtractBits(size_t byte)
{
	return reinterpret_cast<bool*>(ExtractBits(CastAccessData<uint8_t>(byte)));
}
void AbstractMemoryHandler::MemChangeBitP(size_t byte_ptr, uint8_t pos, bool val)
{
	ChangeBitP(CastAccessAt<uint8_t>(byte_ptr),pos,(uint8_t)val);
}

}
}
