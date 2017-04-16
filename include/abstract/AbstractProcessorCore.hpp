#ifndef ABSTRACTPROCESSORCORE_HPP
#define ABSTRACTPROCESSORCORE_HPP
#include <stack>
#include "AbstractMemoryHandler.hpp"
#include "AbstractProcessorState.hpp"
#include "AbstractInterruptHandler.hpp"
#include <SFML/System/Time.hpp>

namespace Psecom {

template <typename RegisterSize> class AbstractProcessorCore : public Peripheria::AbstractInterruptHandler
{
public:
	typedef AbstractProcessorState<RegisterSize> RawState;
	typedef std::shared_ptr<RawState> State;
private:
	Memory::sAbstractMemoryHandler memory;
	std::stack<State> states;
	sf::Time speed;
	//sf::Clock last_check;
public:
	// Clock access

	sf::Time GetSpeed() { return speed; }
	void SetSpeed(sf::Time setto) {speed = setto;}
	//sf::Time CheckRuntime() { return last_check.getElapsedTime(); }
	//sf::Time RestartRuntime() { return last_check.restart(); }

	// Basic access
	Memory::sAbstractMemoryHandler GetMemory() { return memory; }
	void SetMemory(Memory::sAbstractMemoryHandler setto) { memory = setto; }
	State GetTopState() { return states.top(); }
	void PopState() {
		states.pop();
		if(states.empty()) states.push(State(new AbstractProcessorState<RegisterSize>()) );
	}
	void PushState(State newstate) { states.push(newstate); }
	void PushState(RegisterSize Accumulator=0,RegisterSize Argument=0, RegisterSize ProgramCounter=0,RegisterSize MemBegin=0,bool maskability=true) {
		states.push(State(new AbstractProcessorState<RegisterSize>(Accumulator,Argument,ProgramCounter,MemBegin,maskability)) );
	}
	void Return()
	{
		RegisterSize Accumulator = states.top()->GetAccumulatorRegister();
		RegisterSize Argument = states.top()->GetArgumentRegister();
		PopState();
		states.top()->SetAccumulatorRegister(Accumulator);
		states.top()->SetArgumentRegister(Argument);
	}

	// Registers
	RegisterSize GetAccumulatorRegister() { return states.top()->GetAccumulatorRegister(); }
	RegisterSize GetArgumentRegister() { return states.top()->GetArgumentRegister(); }
	RegisterSize GetProgramCounter() { return states.top()->GetProgramCounter(); }
	RegisterSize GetMemBegin() { return states.top()->GetMemBegin(); }
	bool GetMaskability() { return states.top()->GetMaskability(); }
	void SetAccumulatorRegister(RegisterSize setto) { states.top()->SetAccumulatorRegister(setto); }
	void SetArgumentRegister(RegisterSize setto) { states.top()->SetArgumentRegister(setto); }
	void SetProgramCounter(RegisterSize setto) { states.top()->SetProgramCounter(setto); }
	void IncrementProgramCounter(RegisterSize setto) { states.top()->IncrementProgramCounter(setto); }
	void SetMemBegin(RegisterSize setto) { states.top()->SetMemBegin(setto); }
	void SetMaskability(bool setto) { states.top()->SetMaskability(setto); }

	// Memory
	void* AccessMemoryAt(RegisterSize loc) { return memory->AccessMemoryAt((size_t)(loc + GetMemBegin())); }
	RegisterSize* GetMempointerAt(RegisterSize loc) { return memory->CastAccessAt<RegisterSize>((size_t)(loc + GetMemBegin())); }
	RegisterSize GetDataAt(RegisterSize loc) { return memory->CastAccessData<RegisterSize>((size_t)(loc + GetMemBegin())); }
	void MemoryCopy(RegisterSize destination, void* origin, RegisterSize size) {
		memory->MemoryCopy((size_t)(destination + GetMemBegin()),origin,(size_t)size);
	}
	void MemoryCopy(RegisterSize destination, RegisterSize origin, RegisterSize size) {
		memory->MemoryCopy((size_t)(destination + GetMemBegin()),(size_t)(origin + GetMemBegin()),(size_t)size);
	}
	bool MemCheckBit(RegisterSize byte, RegisterSize pos) { return memory->MemCheckBit((size_t)byte,(uint8_t)pos); }
	void MemChangeBitP(RegisterSize byte_ptr, RegisterSize pos, RegisterSize val) {
		memory->MemChangeBitP((size_t)byte_ptr,(uint8_t)pos,val >= 1);
	}
	void LoadIntoAccRegister(RegisterSize loc) { SetAccumulatorRegister(GetDataAt((loc + GetMemBegin()))); }
	void LoadIntoArgRegister(RegisterSize loc) { SetArgumentRegister(GetDataAt((loc + GetMemBegin()))); }
	void StoreFromAccRegister(RegisterSize loc) { *(memory->CastAccessAt<RegisterSize>((size_t)(loc + GetMemBegin()))) = GetAccumulatorRegister(); }
	void StoreFromArgRegister(RegisterSize loc) { *(memory->CastAccessAt<RegisterSize>((size_t)(loc + GetMemBegin()))) = GetArgumentRegister(); }

	void Goto(RegisterSize loc) { SetProgramCounter(GetMemBegin() + loc); }
	void* AccessMemoryAtPC() { return AccessMemoryAt(GetProgramCounter()); }

	// Interrupt
	void InterruptState(size_t memstart, size_t mempos, bool maskability) {
		while(GetMaskability()); // Wait until the last uninterruptable one is gone.
		PushState(0,0,(RegisterSize)mempos,(RegisterSize)memstart,maskability);
	}


	// Constructors
	AbstractProcessorCore(Memory::sAbstractMemoryHandler setmem, sf::Time newspeed)
		: memory(setmem)
	{
		speed = newspeed;
		PushState(0,0,0,false);
	}
};

}
#endif // ABSTRACTPROCESSORCORE_HPP
