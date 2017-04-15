#ifndef ABSTRACTPROCESSOR_ARCH_HPP
#define ABSTRACTPROCESSOR_ARCH_HPP
#include "AbstractProcessorCore.hpp"
#include <map>
namespace Psecom {

enum Pstate
{
	KEEP_GOING,
	STOP,
	PANIC
};

template <typename OpcodeSize, typename OperandSize> class AbstractProcessorArchitecture //: public AbstractProcessorCore<OperandSize>
{
public:
	typedef AbstractProcessorCore<OperandSize>* RegisterStorage;
	//const RegisterStorage CastBack() { return static_cast<RegisterStorage>(this); }
	typedef Pstate (*func_ptr)(RegisterStorage);
private:
	std::map<OpcodeSize,func_ptr> Instructions;
public:
	void RegisterInstruction(func_ptr ptr,OpcodeSize InstructionCode) { Instructions[InstructionCode] = ptr; }
	int Run(RegisterStorage storage);

	AbstractProcessorArchitecture()
	{
		//CastBack()->PushState();
	}
};

#define AbsProcFUNC(rettype,fname) template <typename OpcodeSize, typename OperandSize> rettype AbstractProcessorArchitecture<OpcodeSize,OperandSize>::fname

AbsProcFUNC(int,Run)(RegisterStorage storage)
{
	Pstate status = KEEP_GOING;
	//RegisterStorage storage = CastBack();
	do{
	OpcodeSize* ipointer = static_cast<OpcodeSize*>(storage->AccessMemoryAtPC());
	if(!ipointer) return -1;
	storage->IncrementProgramCounter(sizeof(OpcodeSize));
	status = Instructions[*ipointer](storage);
	if(status == PANIC) return -1;
	}while(status == KEEP_GOING);
	return 0;
}

}
#endif // ABSTRACTPROCESSOR_HPP
