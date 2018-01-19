#include "include/arch/Arrpee8plus.hpp"
#include "include/ControlFlowInstructions.hpp"
sAbstractArchitecture Arrpee8plus::singleton = 0;
sAbstractArchitecture Arrpee8plus::getSingleton()
{
	if(singleton) return singleton;
	else
	{
		singleton = sAbstractArchitecture(new Arrpee8plus);
		return singleton;
	}
}

Arrpee8plus::Arrpee8plus()
	: AbstractArchitecture(PAD)
{
	RegisterArrpe8plus(this);
}

void  Arrpee8plus::RegisterArrpe8plus(pAbstractArchitecture arch)
{
	Arrpee8::RegisterArrpe8(arch);
	arch->registerInstruction(ControlFlow::Goto16, P16GOTO);
	arch->registerInstruction(ControlFlow::Subr16, P16SUBR);
	arch->registerInstruction(ControlFlow::JSubr16, P16JSUBR);
	arch->registerInstruction(ControlFlow::ALoadConstWord16, LCA16);
	arch->registerInstruction(ControlFlow::GLoadPtr8by16, LP16G8);
	arch->registerInstruction(ControlFlow::ALoadPtr16by16, LP16A16);
	arch->registerInstruction(ControlFlow::ALoadRpointerWord16, LR16A);
	arch->registerInstruction(ControlFlow::PSaveWord8by16, SP16G8);
	arch->registerInstruction(ControlFlow::ASavePtr16by16, SP16A16);
	arch->registerInstruction(ControlFlow::RSaveAWord16, SR16A);
}
