#include "include/abstract/AbstractProcessor.hpp"
#include "include/abstract/AbstractMemoryDevice.hpp"
#include "include/abstract/AbstractArchitecture.hpp"
#include <cstring>

sAbstractMemoryDevice AbstractProcessor::getMemory() const
{
	return memory;
}
void AbstractProcessor::setMemory(sAbstractMemoryDevice newMemory)
{
	memory = newMemory;
}
void* AbstractProcessor::accessMemoryAt(size_t offset)
{
	return memory->accessMemoryAt(getAccessRegister(JAIL) + offset);
}
void*  AbstractProcessor::rawAccessMemoryAt(size_t offset)
{
	return memory->accessMemoryAt(offset);
}

void AbstractProcessor::swapGeneralRegisters(uint8_t rega, uint8_t regb)
{
	size_t backup = getGeneralRegister(rega);
	setGeneralRegister(rega,getGeneralRegister(regb));
	setGeneralRegister(regb,backup);
}
sAbstractArchitecture AbstractProcessor::getArchitecture() const
{
	return architecture;
}
void AbstractProcessor::setArchitecture(sAbstractArchitecture newArch)
{
	architecture = newArch;
}
void AbstractProcessor::swapGeneralRegisters(nibbles regs)
{
	swapGeneralRegisters(regs.lower, regs.upper);
}
void AbstractProcessor::swapGeneralRegisters(uint8_t regs)
{
	nibbles tmp;
	*(reinterpret_cast<uint8_t*>(&tmp)) = regs;
	swapGeneralRegisters(tmp);
}
void AbstractProcessor::swapAddressRegisters(uint8_t rega, uint8_t regb)
{
	size_t backup = getAccessRegister(rega);
	setAccessRegister(rega,getAccessRegister(regb));
	setAccessRegister(regb,backup);
}
void AbstractProcessor::swapAddressRegisters(nibbles regs)
{
	swapAddressRegisters(regs.lower, regs.upper);
}
void AbstractProcessor::swapAddressRegisters(uint8_t regs)
{
	nibbles tmp;
	*(reinterpret_cast<uint8_t*>(&tmp)) = regs;
	swapAddressRegisters(tmp);
}
void AbstractProcessor::movGeneralRegisters(uint8_t rega, uint8_t regb)
{
	setGeneralRegister(regb,getGeneralRegister(rega));
}
void AbstractProcessor::movGeneralRegisters(nibbles regs)
{
	movGeneralRegisters(regs.lower, regs.upper);
}
void AbstractProcessor::movGeneralRegisters(uint8_t regs)
{
	nibbles tmp;
	*(reinterpret_cast<uint8_t*>(&tmp)) = regs;
	movGeneralRegisters(tmp);
}
void AbstractProcessor::movAddressRegisters(uint8_t rega, uint8_t regb)
{
	setAccessRegister(regb,getAccessRegister(rega));
}
void AbstractProcessor::movAddressRegisters(nibbles regs)
{
	movAddressRegisters(regs.lower, regs.upper);
}
void AbstractProcessor::movAddressRegisters(uint8_t regs)
{
	nibbles tmp;
	*(reinterpret_cast<uint8_t*>(&tmp)) = regs;
	movAddressRegisters(tmp);
}
timespec& AbstractProcessor::getWaitingTime()
{
	return waitingTime;
}
void AbstractProcessor::setWaitingTime(timespec& newWaitingTime)
{
	waitingTime.tv_sec = newWaitingTime.tv_sec;
	waitingTime.tv_nsec = newWaitingTime.tv_nsec;
}
timespec& AbstractProcessor::getTimer()
{
	return timer;
}

AbstractProcessor::AbstractProcessor(sAbstractMemoryDevice newMemory, sAbstractArchitecture newArch, timespec& newWaitingTime)
	: memory(newMemory), architecture(newArch)
{
	waitingTime.tv_sec = newWaitingTime.tv_sec;
	waitingTime.tv_nsec = newWaitingTime.tv_nsec;
}
void AbstractProcessor::IncrementPC(size_t inc)
{
	setAccessRegister(PROGRAM_COUNTER,getAccessRegister(PROGRAM_COUNTER) + inc);
}
size_t AbstractProcessor::getStackCurrentPosition() const
{
	return getAccessRegister(STACK_POINTER) + (getAccessRegister(STACK_CUR_SIZE) * (getAddressSize() + 1) );
}
size_t AbstractProcessor::getJailBoolAddress() const
{
	return getStackCurrentPosition() + getAddressSize();
}
void* AbstractProcessor::accessStackCurrentPos()
{
	return memory->accessMemoryAt(getStackCurrentPosition());
}
bool* AbstractProcessor::accessJailBoolPos()
{
	return reinterpret_cast<bool*>(memory->accessMemoryAt(getJailBoolAddress()) );
}
void AbstractProcessor::startNormalSubroutine(size_t offset)
{
	size_t curPos = getAccessRegister(PROGRAM_COUNTER) - getAccessRegister(JAIL);
	setAccessRegister(STACK_CUR_SIZE,getAccessRegister(STACK_CUR_SIZE) + 1); // Increment stack size.
	memcpy(accessStackCurrentPos(),&curPos,getAddressSize()); // Copy address
	*(accessJailBoolPos()) = false; // No jail
	setAccessRegister(PROGRAM_COUNTER,getAccessRegister(JAIL) + offset); // Go to the position
}
void AbstractProcessor::startJailedSubroutine(size_t offset)
{
	size_t curPos = getAccessRegister(PROGRAM_COUNTER) - getAccessRegister(JAIL);
	setAccessRegister(STACK_CUR_SIZE,getAccessRegister(STACK_CUR_SIZE) + 1); // Increment stack size.
	memcpy(accessStackCurrentPos(),&curPos,getAddressSize()); // Copy address
	*(accessJailBoolPos()) = true; // No jail
	setAccessRegister(JAIL,getAccessRegister(JAIL) + offset); // Increment the jail
	setAccessRegister(PROGRAM_COUNTER,getAccessRegister(JAIL) + offset); // Go to the position
}
void AbstractProcessor::startProcessing()
{
	clockid_t clock;
	timespec remainer;
	timespec nullClock;
	timer.tv_nsec = 0;
	timer.tv_sec = 0;
	remainer.tv_nsec = 0;
	remainer.tv_sec = 0;
	nullClock.tv_nsec = 0;
	nullClock.tv_sec = 0;
	clock_getcpuclockid(0,&clock);
	clock_settime(clock,&nullClock);
	bool toExit = false;
	do
	{
		ByteField<size_t> opcode;
		opcode.org = getOpcodeAtPC();
		IncrementPC(getOpcodeSize());
		Instruction temporaryInstruction = architecture->fetchInstruction(opcode.org);
		if(temporaryInstruction)
		{
			ProcessorState state = (*temporaryInstruction)(this);
			switch(state)
			{
			case PROCEED:
			{
				toExit = false;
				break;
			}
			case RETURN:
			{
				if( *(accessJailBoolPos()) )
				{
					size_t jailOffset = 0;
					memcpy(&jailOffset,accessStackCurrentPos(),getAddressSize());
					setAccessRegister(JAIL,getAccessRegister(JAIL) - jailOffset);
				}
				setAccessRegister(STACK_CUR_SIZE,getAccessRegister(STACK_CUR_SIZE) -1); // Decrement stack size.
				size_t newPos = 0;
				memcpy(&newPos,accessStackCurrentPos(),getAddressSize());
				setAccessRegister(PROGRAM_COUNTER,getAccessRegister(JAIL) + newPos);
				toExit = false;
				break;
			}
			case POWEROFF:
			{
				toExit = true;
				break;
			}
			case IDLE:
			{
				toExit = true;
				break;
			}
			case PANIC:
			{
				toExit = true;
				break;
			}
			}
		}
		else toExit = true;
		clock_gettime(clock,&timer);
		if(timer.tv_nsec < waitingTime.tv_nsec)
		{
			remainer.tv_nsec = waitingTime.tv_nsec - timer.tv_nsec;
			nanosleep(&remainer,0);
		}
		clock_settime(clock,&nullClock);
	} while(!toExit);
}
