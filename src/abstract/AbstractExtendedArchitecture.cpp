#include "include/abstract/AbstractExtendedArchitecture.hpp"

void AbstractExtendedArchitecture::registerExtraInstruction(Instruction inst, size_t opcode)
{
	if(opcode < extraInstructionSet.size()) extraInstructionSet[opcode] = inst;
}
AbstractExtendedArchitecture::AbstractExtendedArchitecture(size_t maxOpcode, size_t maxExtraOpcode)
	: AbstractArchitecture(maxOpcode), extraInstructionSet(maxExtraOpcode)
{
	;
}
Instruction AbstractExtendedArchitecture::fetchExtraInstruction(size_t opcode)
{
	if(opcode > extraInstructionSet.size()) return 0;
	else return extraInstructionSet[opcode];
}
ProcessorState AbstractExtendedArchitecture::ExtendedInstruction(pAbstractProcessor proc)
{
	size_t xtOpcode = proc->getOpcodeAtPC();
	pAbstractExtendedArchitecture arch = dynamic_cast<pAbstractExtendedArchitecture>(proc->getArchitecture().get());
	if(arch)
	{
		Instruction tmpInstruction = arch->fetchExtraInstruction(xtOpcode);
		if(tmpInstruction) return tmpInstruction(proc);
		else return PANIC;
	}
	else return PANIC;
}
