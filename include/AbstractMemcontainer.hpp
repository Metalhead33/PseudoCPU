#ifndef ABSTRACTMEMCONTAINER_HPP
#define ABSTRACTMEMCONTAINER_HPP
#include <vector>
#include <cstdint>
#include <cstdlib>
#include <memory>
#include "AbstractFread.hpp"
#include "AbstractFwrite.hpp"

typedef std::vector<uint8_t> RawMemoryBuffer;
typedef std::shared_ptr<RawMemoryBuffer> SharedMemory;

template <typename RegisterSize> class AbstractMemcontainer
{
private:
	SharedMemory memspace;
	RegisterSize m_memsize;
	RegisterSize m_pc; // Program Counter
	RegisterSize m_acr; // Accumulator Register
	RegisterSize m_arr; // Argument Register
public:
	void* AccessMemory(RegisterSize offset);
	void* AccessMemAtPC();
	template <typename T> T* CastAccessMemory(RegisterSize offset) { return static_cast<T*>(AccessMemory(offset)); }
	template <typename T> T* CastAccessMemAtPC() { return static_cast<T*>(AccessMemAtPC() ); }
	//Simple getters-setters
	RegisterSize GetMemsize() const { return m_memsize; }
	RegisterSize GetPC() const { return m_pc; }
	RegisterSize GetACR() const { return m_acr; }
	RegisterSize GetARR() const { return m_arr; }
	void SetPC(RegisterSize setto) { m_pc = setto % m_memsize; }
	void IncrementPC(RegisterSize setto) { m_pc += setto; }
	void SetACR(RegisterSize setto) { m_acr = setto; }
	void SetARR(RegisterSize setto) { m_arr = setto; }
	void SwitchRegisters();

	void MemoryDump(AbstractFwrite* writer);

	AbstractMemcontainer(RegisterSize memsize) // New memory from scratch
		: memspace(new RawMemoryBuffer((size_t)memsize))
	{
		m_memsize = memsize;
		m_pc = 0;
		m_acr = 0;
		m_arr = 0;
		//memspace->resize(memsize);
		for(int i = 0;i < memsize;++i) memspace->at(i) = 0;
	}
	AbstractMemcontainer(uint8_t* extmem, RegisterSize memsize) // Copying from existing memory
		: memspace(new RawMemoryBuffer((size_t)memsize))
	{
		m_memsize = memsize;
		m_pc = 0;
		m_acr = 0;
		m_arr = 0;
		//memspace->resize(memsize);
		for(int i = 0;i < memsize;++i) memspace->at(i) = extmem[i];
	}
	AbstractMemcontainer(SharedMemory shared_mem, RegisterSize memsize) // Sharing memory with another container
		: memspace(shared_mem)
	{
		m_memsize = memsize;
		m_pc = 0;
		m_acr = 0;
		m_arr = 0;
		//memspace = shared_mem;
	}
	AbstractMemcontainer(AbstractFread* fileread) // Reading from a file.
		: memspace(new RawMemoryBuffer(fileread->size()))
	{
		m_memsize = fileread->size();
		m_pc = 0;
		m_acr = 0;
		m_arr = 0;
		fileread->read(AccessMemory(0),fileread->size());
		//memspace = shared_mem;
	}
	/*AbstractMemcontainer(const AbstractMemcontainer& origins) // Copy constructor
		: memspace(origins->memspace)
	{
		m_memsize = origins->m_memsize;
		m_pc = origins->m_pc;
		m_acr = origins->m_acr;
		m_arr = origins->m_arr;
	}*/
};
#define AbsMemFUNC(rettype,fname) template <typename RegisterSize> rettype AbstractMemcontainer<RegisterSize>::fname

//template <typename isize,typename rsize> void* AbstractMemcontainer<isize,rsize>::AccessMemory(size_t offset)
AbsMemFUNC(void*,AccessMemory)(RegisterSize offset)
{
	return static_cast<void*>(&memspace->at(offset));
}
AbsMemFUNC(void*,AccessMemAtPC)()
{
	return static_cast<void*>(&memspace->at(m_pc));
}
AbsMemFUNC(void,SwitchRegisters)()
{
	RegisterSize tmp = m_acr;
	m_acr = m_arr;
	m_arr = tmp;
}
AbsMemFUNC(void,MemoryDump)(AbstractFwrite* writer)
{
	writer->write(AccessMemory(0),memspace->size());
}

#endif // ABSTRACTMEMCONTAINER_HPP
