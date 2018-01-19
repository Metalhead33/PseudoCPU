#include "include/arch/Arrpee16plus.hpp"
#include "include/ControlFlowInstructions.hpp"
sAbstractArchitecture Arrpee16plus::singleton = 0;
sAbstractArchitecture Arrpee16plus::getSingleton()
{
	if(singleton) return singleton;
	else
	{
		singleton = sAbstractArchitecture(new Arrpee16plus);
		return singleton;
	}
}

Arrpee16plus::Arrpee16plus()
	: AbstractArchitecture(PAD)
{
	RegisterArrpee16plus(this);
}

void  Arrpee16plus::RegisterArrpee16plus(pAbstractArchitecture arch)
{
	Arrpee16::RegisterArrpe16(arch);
	arch->registerInstruction(ControlFlow::Goto24, P24GOTO);
	arch->registerInstruction(ControlFlow::Subr24, P24SUBR);
	arch->registerInstruction(ControlFlow::JSubr24, P24JSUBR);
	arch->registerInstruction(ControlFlow::ALoadConstWord24, LCA24);
	arch->registerInstruction(ControlFlow::GLoadPtr8by24, LP24G8);
	arch->registerInstruction(ControlFlow::GLoadPtr16by24, LP24G16);
	arch->registerInstruction(ControlFlow::ALoadPtr24by24, LP24A24);
	arch->registerInstruction(ControlFlow::ALoadRpointerWord24, LR24A);
	arch->registerInstruction(ControlFlow::PSaveWord8by24, SP8G24);
	arch->registerInstruction(ControlFlow::PSaveWord16by24, SP16G24);
	arch->registerInstruction(ControlFlow::ASavePtr24by24, SP24A24);
	arch->registerInstruction(ControlFlow::RSaveAWord24, SR24A);
}


