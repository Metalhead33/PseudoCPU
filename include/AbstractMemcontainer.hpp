#ifndef ABSTRACTMEMCONTAINER_HPP
#define ABSTRACTMEMCONTAINER_HPP
#include <vector>
#include <cstdint>
#include <cstdlib>
#include <memory>
#include "AbstractFread.hpp"
#include "AbstractFwrite.hpp"

template <typename isize,typename osize> class AbstractMemcontainer
{
private:
	std::shared_ptr<std::vector<uint8_t>> memspace;
	osize MemSize;
	osize ProgramCounter;
	osize AccumulatorRegister;
	osize ArgumentRegister;
public:
	void* AccessMemory(size_t offset);
	void* AccessMemAtPC();
	//Simple getters-setters
	osize GetMemsize() const { return MemSize; }
	osize GetPC() const { return ProgramCounter; }
	osize GetACR() const { return AccumulatorRegister; }
	osize GetARR() const { return ArgumentRegister; }
	void SetPC(osize setto) { ProgramCounter = setto % MemSize; }
	void IncrementPC(osize setto) { ProgramCounter += setto; }
	void SetACR(osize setto) { AccumulatorRegister = setto; }
	void SetARR(osize setto) { ArgumentRegister = setto; }
	void SwitchRegisters();

	void MemoryDump(AbstractFwrite* writer);

	AbstractMemcontainer(osize memsize) // New memory from scratch
		: memspace(new std::vector<uint8_t>((size_t)memsize))
	{
		MemSize = memsize;
		ProgramCounter = 0;
		AccumulatorRegister = 0;
		ArgumentRegister = 0;
		//memspace->resize(memsize);
		for(int i = 0;i < memsize;++i) memspace->at(i) = 0;
	}
	AbstractMemcontainer(uint8_t* extmem, osize memsize) // Copying from existing memory
		: memspace(new std::vector<uint8_t>((size_t)memsize))
	{
		MemSize = memsize;
		ProgramCounter = 0;
		AccumulatorRegister = 0;
		ArgumentRegister = 0;
		//memspace->resize(memsize);
		for(int i = 0;i < memsize;++i) memspace->at(i) = extmem[i];
	}
	AbstractMemcontainer(std::vector<uint8_t>* shared_mem, osize memsize) // Sharing memory with another container
		: memspace(shared_mem)
	{
		MemSize = memsize;
		ProgramCounter = 0;
		AccumulatorRegister = 0;
		ArgumentRegister = 0;
		//memspace = shared_mem;
	}
	AbstractMemcontainer(AbstractFread* fileread) // Reading from a file.
		: memspace(new std::vector<uint8_t>(fileread->size()))
	{
		MemSize = fileread->size();
		ProgramCounter = 0;
		AccumulatorRegister = 0;
		ArgumentRegister = 0;
		fileread->read(AccessMemory(0),fileread->size());
		//memspace = shared_mem;
	}
	/*AbstractMemcontainer(const AbstractMemcontainer& origins) // Copy constructor
		: memspace(origins->memspace)
	{
		MemSize = origins->MemSize;
		ProgramCounter = origins->ProgramCounter;
		AccumulatorRegister = origins->AccumulatorRegister;
		ArgumentRegister = origins->ArgumentRegister;
	}*/
};
#define AbsMemFUNC(rettype,fname) template <typename isize,typename osize> rettype AbstractMemcontainer<isize,osize>::fname

//template <typename isize,typename osize> void* AbstractMemcontainer<isize,osize>::AccessMemory(size_t offset)
AbsMemFUNC(void*,AccessMemory)(size_t offset)
{
	return static_cast<void*>(&memspace->at(offset));
}
AbsMemFUNC(void*,AccessMemAtPC)()
{
	return static_cast<void*>(&memspace->at(ProgramCounter));
}
AbsMemFUNC(void,SwitchRegisters)()
{
	osize tmp = AccumulatorRegister;
	AccumulatorRegister = ArgumentRegister;
	ArgumentRegister = tmp;
}
AbsMemFUNC(void,MemoryDump)(AbstractFwrite* writer)
{
	writer->write(AccessMemory(0),memspace->size());
}

#endif // ABSTRACTMEMCONTAINER_HPP
