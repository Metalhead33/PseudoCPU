#ifndef ABSTRACTPROCESSOR_HPP
#define ABSTRACTPROCESSOR_HPP
#include "AbstractMemcontainer.hpp"
#include <map>
#include "Global.hpp"

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
	void RegisterInstruction(func_ptr ptr,InstructionSize InstructionCode);
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
	AbstractProcessor(SharedMemory shared_mem, OperandSize memsize)
		: AbstractMemcontainer<OperandSize>(shared_mem,memsize)
	{
		;
	}
	AbstractProcessor(AbstractFread* fileread)
		: AbstractMemcontainer<OperandSize>(fileread)
	{
		;
	}
};
#define AbsProcFUNC(rettype,fname) template <typename InstructionSize, typename OperandSize> rettype AbstractProcessor<InstructionSize,OperandSize>::fname

AbsProcFUNC(int,Run)()
{
	IF_DEBUG(
				std::cout << "Running!" << std::endl;
	)
	Pstate status = KEEP_GOING;
	RegisterStorage storage = CastBack();
	do
	{
		IF_DEBUG(
					std::cout << "Memory address: " << (int)storage->GetPC() << std::endl;
		)
		InstructionSize* ipointer = static_cast<InstructionSize*>(storage->AccessMemAtPC());
		IF_DEBUG(
					std::cout << "Instruction address: " << (size_t)ipointer << std::endl;
		)
		if(!ipointer) return -1;
		storage->IncrementPC(sizeof(InstructionSize));
		status = Instructions[*ipointer](storage);
		if(status == PANIC) return -1;
	}while(status == KEEP_GOING);
	return 0;
}
AbsProcFUNC(void, RegisterInstruction)(func_ptr ptr,InstructionSize InstructionCode)
{
	IF_DEBUG(
				std::cout << "Registering function: " << (size_t)ptr << " - code: " << (int)InstructionCode << std::endl;
	)
	Instructions[InstructionCode] = ptr;
}

#endif // ABSTRACTPROCESSOR_HPP
