#ifndef PROCESSOR_STATE_HPP
#define PROCESSOR_STATE_HPP
#include "include/mem/SharedMemory.hpp"
#include <iostream>

template<typename RegisterSize, typename AddressSize> class ProcessorState
{
public:
	typedef BitBuffer<RegisterSize> RWORD;
	typedef BitBuffer<AddressSize> AWORD;
private:
	SharedMemoryBuffer memSpace;
	RWORD ACCUMULATOR_REGISTER;
	RWORD ARGUMENT_REGISTER;
	AWORD STACK_POINTER;
	AWORD STACK_CUR_SIZE;
	AWORD STACK_MAX_SIZE;
	AWORD JAIL;
	AWORD PROGRAM_COUNTER;
public:
	void IncrementPC(AddressSize offset=1) { PROGRAM_COUNTER.org += offset; }
	ProcessorState(size_t size)
		: memSpace(new SharedMemory(size))
	{
		ACCUMULATOR_REGISTER.org = 0;
		ARGUMENT_REGISTER.org = 0;
		STACK_POINTER.org = 0;
		STACK_CUR_SIZE.org = 0;
		STACK_MAX_SIZE.org = 0;
		JAIL.org = 0;
		PROGRAM_COUNTER.org = 0;
	}
	ProcessorState(SharedMemoryBuffer originalMemory)
		: memSpace(originalMemory)
	{
		ACCUMULATOR_REGISTER.org = 0;
		ARGUMENT_REGISTER.org = 0;
		STACK_POINTER.org = 0;
		STACK_CUR_SIZE.org = 0;
		STACK_MAX_SIZE.org = 0;
		JAIL.org = 0;
		PROGRAM_COUNTER.org = 0;
	}
	void* getMemoryPoint(size_t offset)
	{
		return memSpace->getByteAddress(offset);
	}
	void* getMemoryPoint(AddressSize offset)
	{
		return memSpace->getByteAddress(static_cast<size_t>(offset));
	}
	void* getMemoryPoint(AWORD& offset)
	{
		return memSpace->getByteAddress(static_cast<size_t>(offset.org));
	}
	SharedMemoryBuffer gainDMA()
	{
		return memSpace;
	}
	RWORD& getAccumulator()
	{
		return ACCUMULATOR_REGISTER;
	}
	RWORD& getArgument()
	{
		return ARGUMENT_REGISTER;
	}
	AWORD& getStackPointer()
	{
		return STACK_POINTER;
	}
	AWORD& getStackMaxSize()
	{
		return STACK_MAX_SIZE;
	}
	AWORD& getStackCurSize()
	{
		return STACK_CUR_SIZE;
	}
	AWORD& getProgramCounter()
	{
		return PROGRAM_COUNTER;
	}
	void setAccumulator(RWORD& setto)
	{
		ACCUMULATOR_REGISTER.org = setto.org;
	}
	void setAccumulator(RegisterSize setto)
	{
		ACCUMULATOR_REGISTER.org = setto;
	}
	void setArgument(RWORD& setto)
	{
		ARGUMENT_REGISTER.org = setto.org;
	}
	void setArgument(RegisterSize setto)
	{
		ARGUMENT_REGISTER.org = setto;
	}
	void setStackPointer(AWORD& setto)
	{
		STACK_POINTER.org = setto.org;
	}
	void setStackPointer(AddressSize setto)
	{
		STACK_POINTER.org = setto;
	}
	void setStackMaxSize(AWORD& setto)
	{
		STACK_MAX_SIZE.org = setto.org;
	}
	void setStackMaxSize(AddressSize setto)
	{
		STACK_MAX_SIZE.org = setto;
	}
	void setStackCurSize(AWORD& setto)
	{
		STACK_CUR_SIZE.org = setto.org;
	}
	void setStackCurSize(AddressSize setto)
	{
		STACK_CUR_SIZE.org = setto;
	}
	void setProgramCounter(AWORD& setto)
	{
		PROGRAM_COUNTER.org = setto.org;
	}
	void setProgramCounter(AddressSize setto)
	{
		PROGRAM_COUNTER.org = setto;
	}
};

#endif // PROCESSOR_STATE_HPP
