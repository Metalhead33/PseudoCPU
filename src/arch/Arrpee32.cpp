#include "include/arch/Arrpee32.hpp"
#include "include/ControlFlowInstructions.hpp"
#include "include/ArithmeticalInstructions.hpp"
sAbstractArchitecture Arrpee32::singleton = 0;
sAbstractArchitecture Arrpee32::getSingleton()
{
	if(singleton) return singleton;
	else
	{
		singleton = sAbstractArchitecture(new Arrpee32);
		return singleton;
	}
}

Arrpee32::Arrpee32()
	: AbstractArchitecture(PAD)
{
	RegisterArrpee32(this);
}

void  Arrpee32::RegisterArrpee32(pAbstractArchitecture arch)
{
	Arrpee16plus::RegisterArrpee16plus(arch);
	arch->registerInstruction(ControlFlow::Goto32, P32GOTO);
	arch->registerInstruction(ControlFlow::Subr32, P32SUBR);
	arch->registerInstruction(ControlFlow::JSubr32, P32JSUBR);
	arch->registerInstruction(ControlFlow::GLoadConstWord32, LCG32);
	arch->registerInstruction(ControlFlow::ALoadConstWord32, LCA32);
	arch->registerInstruction(ControlFlow::GLoadPtr8by32, LP32G8);
	arch->registerInstruction(ControlFlow::GLoadPtr16by32, LP32G16);
	arch->registerInstruction(ControlFlow::GLoadPtr32by32, LP32G32);
	arch->registerInstruction(ControlFlow::ALoadPtr32by32, LP32A32);
	arch->registerInstruction(ControlFlow::GLoadRpointerWord32, LR32G);
	arch->registerInstruction(ControlFlow::ALoadRpointerWord32, LR32A);
	arch->registerInstruction(ControlFlow::PSaveWord8by32, SP32G8);
	arch->registerInstruction(ControlFlow::PSaveWord16by32, SP32G16);
	arch->registerInstruction(ControlFlow::PSaveWord32by32, SP32G32);
	arch->registerInstruction(ControlFlow::ASavePtr32by32, SP32A32);
	arch->registerInstruction(ControlFlow::RSaveGWord32, SR32G);
	arch->registerInstruction(ControlFlow::RSaveAWord32, SR32A);
	arch->registerInstruction(Arithmetic::FloatAdd, FADD);
	arch->registerInstruction(Arithmetic::FloatSubtract, FSUB);
	arch->registerInstruction(Arithmetic::FloatMultiplicate, FMUL);
	arch->registerInstruction(Arithmetic::FloatDivide, FDIV);
}

