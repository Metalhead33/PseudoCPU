#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP
#include "InstructionSet.hpp"
#include <stdexcept>
#include <cstdio>
#include <ctime>

template<typename OpcodeSize, typename RegisterSize, typename AddressSize> class Processor
{
public:
	typedef InstructionSet<OpcodeSize, RegisterSize, AddressSize> instSET;
	typedef typename instSET::Instruction Instruction;
	typedef typename instSET::State State;
	typedef typename instSET::sInstructionSet sinstructionSet;
private:
	State processorState;
	sinstructionSet instructionSet;
	timespec waitingTime;
	timespec timer;
public:
	Processor(size_t size, sinstructionSet newSet, timespec timetoWait)
		: processorState(size), instructionSet(newSet)
	{
		waitingTime = timetoWait;
	}
	Processor(SharedMemoryBuffer originalMemory, sinstructionSet newSet, timespec timetoWait)
		: processorState(originalMemory), instructionSet(newSet)
	{
		waitingTime = timetoWait;
	}
	long getWaitingTime() { return waitingTime; }
	void setWaitingTime(long setto) { waitingTime = setto; }
	State* getState() { return &processorState; }
	void startProcessing()
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
		do {
			// Useless now, previously used for debugging: // printf("Program Counter: 0x%04X |\t", processorState.getProgramCounter().org);
			OpcodeSize opcode = *static_cast<OpcodeSize*>(processorState.getMemoryPoint(processorState.getProgramCounter().org));
			// Useless now, previously used for debugging: // printf("Executing Opcode 0x%04X!\n", opcode);
			Instruction temporaryInstruction = instructionSet->fetchInstruction(opcode);
			if(temporaryInstruction)
			{
				ComputerState tempState = (*temporaryInstruction)(&processorState);
				switch(tempState)
				{
				case GO_ON:
				{
					toExit = false;
					// processorState.setProgramCounter(processorState.getProgramCounter().org+1);
					processorState.IncrementPC(sizeof(OpcodeSize));
					break;
				}
				case GO_TO:
				{
					toExit = false;
					break;
				}
				case SHUTDOWN:
				{
					toExit = true;
					break;
				}
				case ERROR:
				{
					toExit = true;
					throw std::runtime_error("Error encountered while processing!");
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
};

#endif // PROCESSOR_HPP
