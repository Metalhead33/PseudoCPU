#include "include/arch/Arrpee16.hpp"
#include "include/ControlFlowInstructions.hpp"
sAbstractArchitecture Arrpee16::singleton = 0;
sAbstractArchitecture Arrpee16::getSingleton()
{
	if(singleton) return singleton;
	else
	{
		singleton = sAbstractArchitecture(new Arrpee16);
		return singleton;
	}
}

Arrpee16::Arrpee16()
	: AbstractArchitecture(PAD)
{
	RegisterArrpe16(this);
}

void  Arrpee16::RegisterArrpe16(pAbstractArchitecture arch)
{
	Arrpee8plus::RegisterArrpe8plus(arch);
	arch->registerInstruction(ControlFlow::GLoadConstWord16, LCG16);
	arch->registerInstruction(ControlFlow::GLoadPtr16by16, LP16G16);
	arch->registerInstruction(ControlFlow::GLoadRpointerWord16, LR16G);
	arch->registerInstruction(ControlFlow::PSaveWord16by16, SP16G16);
	arch->registerInstruction(ControlFlow::RSaveGWord16, SR16G);
}
