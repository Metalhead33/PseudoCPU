#pragma once
#include "AbstractDeclarations.hpp"
#include <vector>

class AbstractArchitecture
{
private:
	std::vector<Instruction> instructionSet;
public:
	virtual ~AbstractArchitecture();
	AbstractArchitecture(size_t maxOpcode);
	Instruction fetchInstruction(size_t opcode);
	void registerInstruction(Instruction inst, size_t opcode);
	// virtual const size_t getOpcodeSize() const = 0;
};
