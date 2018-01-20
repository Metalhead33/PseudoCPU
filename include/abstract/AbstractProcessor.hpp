#pragma once
#include "AbstractDeclarations.hpp"
#include <ctime>

class AbstractProcessor
{
	private:
	sAbstractMemoryDevice memory;
	sAbstractArchitecture architecture;
	timespec waitingTime;
	timespec timer;

	public:
	virtual size_t getGeneralRegister(uint8_t reg) const = 0;
	virtual void setGeneralRegister(uint8_t reg, size_t setto) = 0;
	virtual size_t getAccessRegister(uint8_t reg) const = 0;
	virtual void setAccessRegister(uint8_t reg, size_t setto) = 0;

	virtual const size_t getWordSize() const = 0;
	virtual const size_t getAddressSize() const = 0;
	virtual const size_t getOpcodeSize() const = 0;
	virtual size_t getOpcodeAtPC() = 0;

	enum SpecialAddressRegister : uint8_t
	{
		PROGRAM_COUNTER,
		STACK_POINTER,
		STACK_MAX_SIZE,
		STACK_CUR_SIZE,
		JAIL,
		PAD // This is where it should start.
	};

	size_t getStackCurrentPosition() const;
	size_t getJailBoolAddress() const;
	void* accessStackCurrentPos();
	bool* accessJailBoolPos();
	void startNormalSubroutine(size_t offset);
	void startJailedSubroutine(size_t offset);

	void moveGeneralRegister(uint8_t rega, uint8_t regb);
	void moveGeneralRegister(nibbles regs);
	void moveGeneralRegister(uint8_t regs);

	timespec& getWaitingTime();
	void setWaitingTime(timespec& newWaitingTime);
	timespec& getTimer();

	void swapGeneralRegisters(uint8_t rega, uint8_t regb);
	void swapGeneralRegisters(nibbles regs);
	void swapGeneralRegisters(uint8_t regs);
	void swapAddressRegisters(uint8_t rega, uint8_t regb);
	void swapAddressRegisters(nibbles regs);
	void swapAddressRegisters(uint8_t regs);
	void movGeneralRegisters(uint8_t rega, uint8_t regb);
	void movGeneralRegisters(nibbles regs);
	void movGeneralRegisters(uint8_t regs);
	void movAddressRegisters(uint8_t rega, uint8_t regb);
	void movAddressRegisters(nibbles regs);
	void movAddressRegisters(uint8_t regs);

	void IncrementPC(size_t inc = 1);


	sAbstractMemoryDevice getMemory() const;
	void setMemory(sAbstractMemoryDevice newMemory);
	void* accessMemoryAt(size_t offset);
	template<typename T> T* castAccessMemoryAt(size_t offset)
	{
		return reinterpret_cast<T*>(accessMemoryAt(offset));
	}
	void* rawAccessMemoryAt(size_t offset);
	template<typename T> T* rawCastAccessMemoryAt(size_t offset)
	{
		return reinterpret_cast<T*>(rawAccessMemoryAt(offset));
	}

	sAbstractArchitecture getArchitecture() const;
	void setArchitecture(sAbstractArchitecture newArch);
	AbstractProcessor(sAbstractMemoryDevice newMemory, sAbstractArchitecture newArch, timespec& newWaitingTime);

	void startProcessing();
};
