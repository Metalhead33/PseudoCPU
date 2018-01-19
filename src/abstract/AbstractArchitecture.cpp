#include "include/abstract/AbstractArchitecture.hpp"

AbstractArchitecture::~AbstractArchitecture()
{
	;
}
void AbstractArchitecture::registerInstruction(Instruction inst, size_t opcode)
{
	if(opcode < instructionSet.size()) instructionSet[opcode] = inst;
}
Instruction AbstractArchitecture::fetchInstruction(size_t opcode)
{
	if(opcode > instructionSet.size()) return 0;
	else return instructionSet[opcode];
}
AbstractArchitecture::AbstractArchitecture(size_t maxOpcode)
	: instructionSet(maxOpcode)
{
	;
}
