#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP
#include "InstructionSet.hpp"

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
public:
	Processor(size_t size, sinstructionSet newSet)
		: processorState(size), instructionSet(newSet)
	{

	}
	Processor(SharedMemoryBuffer originalMemory, sinstructionSet newSet)
		: processorState(originalMemory), instructionSet(newSet)
	{

	}
	void startProcessing()
	{
		bool toExit = false;
		do {
			Instruction temporaryInstruction = instructionSet->fetchInstruction(*static_cast<OpcodeSize*>(processorState.getMemoryPoint(processorState.getProgramCounter())) );
			if(temporaryInstruction)
			{
				ComputerState tempState = temporaryInstruction(&processorState);
				switch(tempState)
				{
				case GO_ON:
				{
					toExit = false;
					processorState.setProgramCounter(processorState.getProgramCounter().org+1);
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
					break;
				}
				}
			}
			else toExit = true;
		} while(!toExit);
	}
};

#endif // PROCESSOR_HPP
