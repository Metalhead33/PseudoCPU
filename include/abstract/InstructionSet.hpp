#ifndef INSTRUCTIONSET_HPP
#define INSTRUCTIONSET_HPP
#include "ProcessorState.hpp"
#include <map>
#include <vector>

enum ComputerState
{
	GO_ON, // Automatically increments program counter
	GO_TO, // Does not increment the program counter
	SHUTDOWN, // Shuts down the computer
	ERROR // Shuts down the computer
};

template<typename OpcodeSize, typename RegisterSize, typename AddressSize> class InstructionSet
{
public:
	typedef ProcessorState<RegisterSize,AddressSize> State;
	typedef State* StatePointer;
	typedef ComputerState (*Instruction)(StatePointer);
	typedef std::vector<Instruction> InstructionVector;

	typedef InstructionSet* pInstructionSet;
	typedef std::shared_ptr<InstructionSet> sInstructionSet;
private:
	InstructionVector instructions;
public:
	InstructionSet(OpcodeSize maxInstructionNumber)
		: instructions(maxInstructionNumber)
	{
	   std::fill(instructions.begin(), instructions.end(), reinterpret_cast<Instruction>(static_cast<size_t>(0)));
	}
	virtual ~InstructionSet() {;}
	Instruction fetchInstruction(OpcodeSize opcode)
	{
		if(opcode < instructions.size())
		return instructions[opcode];
		else return 0;
	}
	void uploadInstruction(OpcodeSize opcode, Instruction instruction)
	{
		if(opcode < instructions.size())
			instructions[opcode] = instruction;
	}
};

#endif // INSTRUCTIONSET_HPP
