#ifndef ABSTRACTPROCESSOR_HPP
#define ABSTRACTPROCESSOR_HPP
#include "include/AbstractMemcontainer.hpp"
#include <map>

enum Pstate
{
	KEEP_GOING,
	STOP,
	PANIC
};

template <typename InstructionSize, typename OperandSize> class AbstractProcessor : public AbstractMemcontainer<OperandSize>
{
public:
	typedef AbstractMemcontainer<OperandSize>* RegisterStorage;
	typedef Pstate (*func_ptr)(RegisterStorage);
	const RegisterStorage CastBack() { return static_cast<AbstractMemcontainer<OperandSize>*>(this); }
private:
	std::map<InstructionSize,func_ptr> Instructions;
public:
	int Run();
	void RegisterInstruction(func_ptr ptr,InstructionSize InstructionCode) { Instructions[InstructionCode] = ptr; }
	AbstractProcessor(OperandSize memsize)
		: AbstractMemcontainer<OperandSize>(memsize)
	{
		;
	}
	AbstractProcessor(uint8_t* extmem, OperandSize memsize)
		: AbstractMemcontainer<OperandSize>(extmem,memsize)
	{
		;
	}
	AbstractProcessor(RawMemoryBuffer* shared_mem, OperandSize memsize)
		: AbstractMemcontainer<OperandSize>(shared_mem,memsize)
	{
		;
	}
};
#define AbsProcFUNC(rettype,fname) template <typename InstructionSize, typename OperandSize> rettype AbstractProcessor<InstructionSize,OperandSize>::fname

AbsProcFUNC(int,Run)()
{
	Pstate status = KEEP_GOING;
	RegisterStorage storage = CastBack();
	do
	{
		InstructionSize* ipointer = static_cast<InstructionSize*>(storage->AccessMemAtPC());
		status = Instructions(*ipointer,storage);
		if(status == PANIC) return -1;
		else storage->IncrementPC(sizeof(InstructionSize));
	}while(status == KEEP_GOING);
	return 0;
}

#endif // ABSTRACTPROCESSOR_HPP
