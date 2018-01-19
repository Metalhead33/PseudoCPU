#pragma once
#include "AbstractArchitecture.hpp"
#include "AbstractProcessor.hpp"

DEFINE_CLASS(AbstractExtendedArchitecture)
class AbstractExtendedArchitecture : public AbstractArchitecture
{
private:
	std::vector<Instruction> extraInstructionSet;
protected:
	void registerExtraInstruction(Instruction inst, size_t opcode);
public:
	AbstractExtendedArchitecture(size_t maxOpcode, size_t maxExtraOpcode);
	Instruction fetchExtraInstruction(size_t opcode);
	static ProcessorState ExtendedInstruction(pAbstractProcessor proc);
};
