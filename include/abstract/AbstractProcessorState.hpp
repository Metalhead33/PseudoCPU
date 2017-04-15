#ifndef ABSTRACTPROCESSORSTATE_HPP
#define ABSTRACTPROCESSORSTATE_HPP
//#include "AbstractMemoryHandler.hpp"
namespace Psecom {

template <typename RegisterSize> class AbstractProcessorState
{
private:
	//Memory::sAbstractMemoryHandler memory;
	RegisterSize rAccumulatorRegister;
	RegisterSize rARgumentRegister;
	RegisterSize rProgramCounter;
	RegisterSize rMemBegin;
	bool maskable;
public:
	//Memory::sAbstractMemoryHandler GetMemory() { return memory; }
	RegisterSize GetAccumulatorRegister() { return rAccumulatorRegister; }
	RegisterSize GetArgumentRegister() { return rARgumentRegister; }
	RegisterSize GetProgramCounter() { return rProgramCounter; }
	RegisterSize GetMemBegin() { return rMemBegin; }
	bool GetMaskability() { return maskable; }
	void SetAccumulatorRegister(RegisterSize setto) { rAccumulatorRegister = setto; }
	void SetArgumentRegister(RegisterSize setto) { rARgumentRegister = setto; }
	void SetProgramCounter(RegisterSize setto) { rProgramCounter = setto; }
	void IncrementProgramCounter(RegisterSize setto) { rProgramCounter += setto; }
	void SetMemBegin(RegisterSize setto) { rMemBegin = setto; }
	void SetMaskability(bool setto) { maskable = setto; }
	AbstractProcessorState(RegisterSize Accumulator=0,RegisterSize Argument=0, RegisterSize ProgramCounter=0,RegisterSize MemBegin=0,bool maskability=true)
	{
		rAccumulatorRegister = Accumulator;
		rARgumentRegister = Argument;
		rProgramCounter = ProgramCounter;
		rMemBegin = MemBegin;
		maskable = maskability;
	}
};

}
#endif // ABSTRACTPROCESSORCORE_HPP
