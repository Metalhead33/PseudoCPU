#include <cstdio>
#include "StdStream.hpp"
#include <cstring>
#include <cstdio>
#include "include/arch/Arrpee8.hpp"
#include "include/mem/SharedMemoryBuffer.hpp"
#include <cstring>

uint8_t loadedProgram[] =
{
	Arrpee8::LCG8,
	0,
	8,
	Arrpee8::LCG8,
	1,
	4,
	Arrpee8::ADD,
	0x01,
	Arrpee8::SP8G8,
	0,
	128,
	Arrpee8::SP8G8,
	1,
	129,
	Arrpee8::OFF
};
Arrpee8_Machine* cpu;

int main(void)
{
	sAbstractFwrite writer = StdStream::createWriter("/tmp/ass");
	timespec waitingTime;
	waitingTime.tv_nsec = 500;
	sAbstractMemoryDevice mem = sAbstractMemoryDevice(new SharedMemoryBuffer(256));
	memcpy(mem->accessMemoryAt(0),loadedProgram,sizeof(loadedProgram));
	cpu = new Arrpee8_Machine(mem,waitingTime);
	cpu->startProcessing();
	mem->dumpMemory(writer);
	return 0;
}
