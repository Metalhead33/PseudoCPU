#ifndef ABSTRACTPROCESSOR_HPP
#define ABSTRACTPROCESSOR_HPP
#include <map>
#include <iostream>

namespace Fcom {

enum Pstate
{
	KEEP_GOING,
	STOP,
	PANIC
};

template <typename rsize> struct Cstate
{
	char* memory_space;
	char* memory_pointer;
	char** bank_pointer;
	rsize AccumulatorRegister;
	rsize ProgramCounter;
	rsize BankCounter;
	size_t memsize;
	size_t banksize;
	size_t bank_num;

	void* GetDirectAddress(size_t offset) { return memory_space + (offset%memsize) ; }
	void* GetAddress(rsize offset) { return &bank_pointer[BankCounter][offset % banksize]; }
	rsize GetValue(rsize offset) { return *((rsize*)GetAddress(offset)); }
	rsize GetDirectValue(size_t offset) { return *((rsize*)GetDirectAddress(offset)); }
	void* MemoryJumpDirect(size_t offset) { return GetDirectAddress((size_t)GetDirectValue(offset)); }
	void* MemoryJump(rsize offset) { return GetAddress(GetValue(offset) ); }
	rsize MemoryJumpValue(rsize offset) { return GetValue(GetValue(offset)); }

	void AdjustPointer() { memory_pointer = &bank_pointer[BankCounter][ProgramCounter]; }
	void IncrementPC(rsize incr) { ProgramCounter += incr; ProgramCounter %= banksize;AdjustPointer(); }

};

template <typename isize,typename osize> class AbstractProcessor
{
public:
	typedef Cstate<osize>* RegisterStorage;
	typedef Pstate (*func_ptr)(RegisterStorage,osize);
private:
	RegisterStorage Registers;
	std::map<isize,func_ptr> Instructions;
	//std::map<isize,func_ptr>::iterator it;

public:
	//void AdjustMempointer() { Registers->memory_pointer = Registers->bank_pointer[Registers->BankCounter] + ((size_t)Registers->ProgramCounter % Registers->banksize); }
	//void IncrementPC(osize arg) { Registers->ProgramCounter+= arg;AdjustMempointer(); }
	int Run() {
		Pstate status = KEEP_GOING;
		do
		{
			isize* ipointer = (isize*)Registers->memory_pointer;
			//std::cout << "Instruction - [" << (size_t)ipointer << "] = " << (size_t)*ipointer <<std::endl;
			Registers->IncrementPC(sizeof(isize) );
			osize* opointer = (osize*)Registers->memory_pointer;
			//std::cout << "Operand - [" << (size_t)opointer << "] = " << (size_t)*opointer <<std::endl;
			Registers->IncrementPC(sizeof(osize) );
			//it = Instructions.find(*ipointer);
			//if(it == Instructions.end()) return -1; //illegal instruction
			if(!ipointer) return -1;
			if (!Instructions[*ipointer]) return -1;
			status = Instructions[*ipointer](Registers,*opointer);
			if(status == PANIC) return -1;
		}
		while(status == KEEP_GOING);
		return 0;
	}
	Cstate<osize>* GetRegister() { return Registers; }
	//void* GetMemoryAddressDir(size_t memaddr) { return &Registers->memory_space[memaddr]; }
	//void* GetMemoryAddress(size_t memaddr) { return &Registers->bank_pointer[Registers->BankCounter][memaddr]; }
	//osize GetMemData(size_t memaddr) { return *((osize*)GetMemoryAddress(memaddr)); }
	//void* MemoryJump(size_t memaddr) { return GetMemoryAddress( (size_t)GetMemData(memaddr) );  }
	void RegisterInstruction(func_ptr ptr,isize incode) { Instructions[incode] = ptr; }

	AbstractProcessor(osize banksize, osize banknum)
	{
		Registers = new Cstate<osize>;
		Registers->bank_num = (size_t)banknum+1;
		Registers->banksize = (size_t)banksize+1;
		Registers->memsize = Registers->bank_num * Registers->banksize;
		Registers->memory_space = new char[Registers->memsize];
		//Registers->memory_space = new char[Registers->memsize];
		Registers->bank_pointer = new char*[Registers->bank_num];
		for(size_t i=0;i<(banknum+1);++i) Registers->bank_pointer[i] = Registers->memory_space + (i*(banksize+1));
		Registers->AccumulatorRegister = 0;
		Registers->ProgramCounter = 0;
		Registers->BankCounter = 0;
		Registers->AdjustPointer();
	}
	virtual ~AbstractProcessor()
	{
		delete Registers->memory_space;
		delete Registers->bank_pointer;
		delete Registers;
	}
};

/*template <typename isize,typename osize> class AbstractProcessor
{
public:
	typedef Cstate (AbstractProcessor::*func_ptr)(osize);
private:
	std::map<isize,func_ptr> Instructions;
	char* MemorySpace;
	void* MemoryPointer; // Where are we now?
	osize ProgramCounter;
	osize AccumulatorRegister;
	osize ArgumentRegister;
	osize CounterRegister;
public:
	AbstractProcessor() {;}
	osize GetProgramCounter() const {return ProgramCounter;}
	osize GetAccumulatorRegister() const {return AccumulatorRegister;}
	osize GetArgumentRegister() const {return ArgumentRegister;}
	osize GetCounterRegister() const {return CounterRegister;}
	void SetProgramCounter(osize setto) {ProgramCounter = setto;}
	void SetAccumulatorRegister(osize setto) {AccumulatorRegister = setto;}
	void SetArgumentRegister(osize setto) {ArgumentRegister = setto;}
	void SetCounterRegister(osize setto) {CounterRegister = setto;}
	void RegisterInstruction(isize code, func_ptr function) { Instructions[code] = function; }

	void* GetMemspace() const { return MemorySpace; }
	void* GetMempointer() const { return MemoryPointer; }
	void SetMemorypointer(size_t part) { MemoryPointer = MemorySpace + part; }
	template<typename T> T* GetMemory(size_t place) const { return (T*)(&MemorySpace[place]); }
	virtual void IncrementPC(osize setto) {ProgramCounter += setto; SetMemorypointer(ProgramCounter); }

	osize GetMemoryJump(size_t part) { return *(GetMemory<osize>(part)); }

	int Run()
	{
		Cstate state = KEEP_GOING;
		do
		{
			void* instruction_place = MemoryPointer;
			IncrementPC(sizeof(isize));
			void* operand_place = MemoryPointer;
			IncrementPC(sizeof(osize));
			state = *Instructions[*((isize*)instruction_place)](*((osize*)operand_place));
			if(state == PANIC) return -1;
		}
		while(state != STOP);
		return 0;
	}
};*/

}

#endif // ABSTRACTPROCESSOR_HPP
