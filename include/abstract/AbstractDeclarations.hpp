#pragma once
#include "Global.hpp"


enum ProcessorState : uint8_t
{
	PROCEED, // The program counter is automatically incremented by the opcode size, every other incrementation is done manually by the instruction itself
	RETURN, // Decrement the stack, move back on the stack.
	POWEROFF, // Computer turns off
	IDLE, // Temporary freeze, must be unfrozen manually
	PANIC // Error report
};
DEFINE_CLASS(AbstractMemoryDevice)
DEFINE_CLASS(AbstractArchitecture)
DEFINE_CLASS(AbstractProcessor)
DEFINE_CLASS(AbstractFread)
DEFINE_CLASS(AbstractFwrite)
typedef ProcessorState (*Instruction)(pAbstractProcessor);

template<typename T> union ByteField
{
	T org;
	uint8_t bytes[sizeof(T)];
	ByteField(ByteField& copy) { org = copy.org; }
	ByteField(T& copy) { org = copy; }
	ByteField() {
		for(size_t i = 0; i < sizeof(T); ++i) bytes[i] = 0;
	}
	uint8_t& operator[](size_t offset) { return bytes[offset % sizeof(T)]; }
};
template<typename T> union PaddedByteField
{
	size_t padding;
	ByteField<T> org;
	PaddedByteField() { padding = 0; }
	PaddedByteField(size_t copy) { padding = copy; }
	PaddedByteField(PaddedByteField& copy) { padding = copy.padding; }
	PaddedByteField(ByteField<T>& copy) { padding = 0; org.org = copy.org; }
	PaddedByteField(T& copy) { padding = 0; org.org = copy; }
	uint8_t& operator[](size_t offset) { return org.bytes[offset % sizeof(T)]; }
};

struct bitfield24 {
	 uint16_t lower;
	 uint8_t upper;
};
struct nibble {
	 uint8_t nib : 4;
};
struct nibbles {
	uint8_t upper : 4;
	uint8_t lower : 4;
};

typedef ByteField<uint8_t> word8;
typedef ByteField<nibbles> word8n;
typedef ByteField<uint16_t> word16;
typedef ByteField<bitfield24> word24;
typedef ByteField<uint32_t> word32;
typedef ByteField<size_t> sizefield;

typedef PaddedByteField<uint8_t> pword8;
typedef PaddedByteField<nibbles> pword8n;
typedef PaddedByteField<uint16_t> pword16;
typedef PaddedByteField<bitfield24> pword24;
typedef PaddedByteField<uint32_t> pword32;
