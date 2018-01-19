#pragma once
#include "AbstractProcessor.hpp"
#include <vector>
template<typename WordSize, typename AddressSize, typename OpcodeSize> class Processor : public AbstractProcessor
{
public:
	typedef PaddedByteField<WordSize> WORD;
	typedef PaddedByteField<AddressSize> ADDR;
	typedef PaddedByteField<OpcodeSize> OPC;
private:
	std::vector<WORD> generalRegisters;
	std::vector<ADDR> addressRegisters;
public:
	virtual size_t getGeneralRegister(uint8_t reg) const
	{
		return generalRegisters[reg].padding;
	}
	virtual void setGeneralRegister(uint8_t reg, size_t setto)
	{
		generalRegisters[reg].padding = setto;
	}
	virtual size_t getAccessRegister(uint8_t reg) const
	{
		return addressRegisters[reg].padding;
	}
	virtual void setAccessRegister(uint8_t reg, size_t setto)
	{
		addressRegisters[reg].padding = setto;
	}

	virtual const size_t getWordSize() const { return sizeof(WordSize); }
	virtual const size_t getAddressSize() const { return sizeof(AddressSize); }
	virtual const size_t getOpcodeSize() const { return sizeof(OpcodeSize); }
	virtual size_t getOpcodeAtPC() const
	{
		OPC tmp;
		tmp.padding = 0;
		tmp.org.org = *(rawCastAccessMemoryAt<OpcodeSize>(addressRegisters[PROGRAM_COUNTER].padding));
		return tmp.padding;
	}
	Processor(sAbstractMemoryDevice newMemory, sAbstractArchitecture newArch, timespec& newWaitingTime, uint8_t gregs, uint8_t addregs=0)
		: AbstractProcessor(newMemory,newArch,newWaitingTime), generalRegisters(gregs), addressRegisters(PAD + addregs)
	{
		;
	}
};
