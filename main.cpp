#include <cstdio>
#include "include/arch/Arrpee8.hpp"
#include "include/abstract/Processor.hpp"
#include "StdStream.hpp"
#include <cstring>
#include <cstdio>

uint8_t instructionCode[] = {
	Arrpee8::LDSPD16, // We set the stack pointer first
	127, // We set the stack pointer at 128
	0,
	Arrpee8::LDSMD16, // We need to also set the maximum size of stack
	63, // 63 is what we can achieve
	0,
	Arrpee8::LDACD8,
	25,
	Arrpee8::LDARD8,
	50,
	Arrpee8::ADD, // Let's add them. Result is supposed to be 75.
	Arrpee8::STAC8_16,
	60, // Store at address 125.
	0,
	Arrpee8::MEMCPY16,
	0,
	0,
	70,
	0,
	14,
	0,
	Arrpee8::POFF, // Power off
};

int main(void)
{
	timespec waitingTime;
	waitingTime.tv_nsec = 500;
	sAbstractFwrite writer = StdStream::createWriter("/tmp/ass");
	SharedMemoryBuffer mem = SharedMemoryBuffer(new SharedMemory(256));
	memcpy(mem->getByteAddress(0),instructionCode,sizeof(instructionCode));
	Processor<uint8_t, uint16_t,uint16_t> processor(mem,Arrpee8::getSingleton(),waitingTime);
	processor.startProcessing();
	printf("Processor data:\n\n\n");
	printf("Accumulator Register: 0x%04X\n", processor.getState()->getAccumulator().org);
	printf("Argument Register: 0x%04X\n", processor.getState()->getArgument().org);
	printf("Program Counter: 0x%04X\n", processor.getState()->getProgramCounter().org);
	printf("Stack Pointer: 0x%04X\n", processor.getState()->getStackPointer().org);
	printf("Stack Maximal Size: 0x%04X\n", processor.getState()->getStackMaxSize().org);
	printf("Stack Current Size: 0x%04X\n", processor.getState()->getStackCurSize().org);

	printf("Instruction addresses:\n\n");
	for(uint8_t i = 0; i < Arrpee8::PAD;++i)
	{
		printf("0x%02X\t-\t0x%08X\n",i,reinterpret_cast<size_t>(Arrpee8::getSingleton()->fetchInstruction(i)));
	}
	mem->dumpMemory(writer);
	return 0;
}
