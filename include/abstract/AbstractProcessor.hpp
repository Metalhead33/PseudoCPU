#ifndef ABSTRACTPROCESSOR_HPP
#define ABSTRACTPROCESSOR_HPP
#include "AbstractProcessorArchitecture.hpp"
//#include "AbstractProcessorCore.hpp"

namespace Psecom {

template <typename OpcodeSize, typename OperandSize> class AbstractProcessor : public AbstractProcessorCore<OperandSize>
{
public:
	typedef AbstractProcessorCore<OperandSize> CoreType;
	typedef AbstractProcessorArchitecture<OpcodeSize,OperandSize> ArchitectureType;
	typedef CoreType* pCore;
	typedef std::shared_ptr<ArchitectureType> sArch;
private:
	sArch m_arch;
public:
	const pCore CastBack() { return static_cast<pCore>(this); }
	int Run() { return m_arch->Run(CastBack() ); }

	AbstractProcessor(sArch architecture, Memory::sAbstractMemoryHandler setmem, sf::Time newspeed)
		: CoreType(setmem,newspeed)
	{
		m_arch = architecture;
	}
	AbstractProcessor(sArch architecture, Memory::sAbstractMemoryHandler setmem, double mips)
		: CoreType(setmem,mips)
	{
		m_arch = architecture;
	}
	AbstractProcessor(sArch architecture, Memory::sAbstractMemoryHandler setmem, double mips_at_mhz,double mhz)
		: CoreType(setmem,mips_at_mhz,mhz)
	{
		m_arch = architecture;
	}

};

}
#endif // ABSTRACTPROCESSOR_HPP
