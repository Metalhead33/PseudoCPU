#include "include/arch/Arrpee8.hpp"
#include "include/ArithmeticalInstructions.hpp"
#include "include/ControlFlowInstructions.hpp"
sAbstractArchitecture Arrpee8::singleton = 0;
sAbstractArchitecture Arrpee8::getSingleton()
{
	if(singleton) return singleton;
	else
	{
		singleton = sAbstractArchitecture(new Arrpee8);
		return singleton;
	}
}

Arrpee8::Arrpee8()
	: AbstractArchitecture(PAD)
{
	RegisterArrpe8(this);
}
void  Arrpee8::RegisterArrpe8(pAbstractArchitecture arch)
{
	arch->registerInstruction(ControlFlow::Nope, NOPE);
	arch->registerInstruction(ControlFlow::Ret, RET);
	arch->registerInstruction(ControlFlow::Freeze, FRZ);
	arch->registerInstruction(ControlFlow::Poweroff, OFF);
	arch->registerInstruction(ControlFlow::Panic, ERR);
	arch->registerInstruction(Arithmetic::Add, ADD);
	arch->registerInstruction(Arithmetic::Subtract, SUB);
	arch->registerInstruction(Arithmetic::Multiplicate, MUL);
	arch->registerInstruction(Arithmetic::Divide, DIV);
	arch->registerInstruction(Arithmetic::Modulo, MOD);
	arch->registerInstruction(Arithmetic::LogicalNot, LNOT);
	arch->registerInstruction(Arithmetic::LogicalAnd, LAND);
	arch->registerInstruction(Arithmetic::LogicalInclusiveOr, LIOR);
	arch->registerInstruction(Arithmetic::LogicalExclusiveOr, LXOR);
	arch->registerInstruction(Arithmetic::BitwiseNot, BNOT);
	arch->registerInstruction(Arithmetic::BitwiseAnd, BAND);
	arch->registerInstruction(Arithmetic::BitwiseInclusiveOr, BIOR);
	arch->registerInstruction(Arithmetic::BitwisexclusiveOr, BXOR);
	arch->registerInstruction(Arithmetic::BitwiseLeftShift, BLSH);
	arch->registerInstruction(Arithmetic::BitwiseRightShift, BRSH);
	arch->registerInstruction(ControlFlow::GeneralMove, GMOV);
	arch->registerInstruction(ControlFlow::GeneralShuffle, GSHF);
	arch->registerInstruction(ControlFlow::AddressMove, AMOV);
	arch->registerInstruction(ControlFlow::AddressShuffle, ASHF);
	arch->registerInstruction(ControlFlow::GotoRptr, RGOTO);
	arch->registerInstruction(ControlFlow::SubrRptr, RSUBR);
	arch->registerInstruction(ControlFlow::JSubrRptr, RJSUBR);
	arch->registerInstruction(ControlFlow::ConGotoRptr, RCGOTO);
	arch->registerInstruction(ControlFlow::ConSubrRptr, RCSUBR);
	arch->registerInstruction(ControlFlow::ConJSubrRptr, RCJSUBR);
	arch->registerInstruction(ControlFlow::Goto8, P8GOTO);
	arch->registerInstruction(ControlFlow::Subr8, P8SUBR);
	arch->registerInstruction(ControlFlow::JSubr8, P8JSUBR);
	arch->registerInstruction(ControlFlow::GLoadConstWord8, LCG8);
	arch->registerInstruction(ControlFlow::ALoadConstWord8, LCA8);
	arch->registerInstruction(ControlFlow::GLoadPtr8by8, LP8G8);
	arch->registerInstruction(ControlFlow::ALoadPtr8by8, LP8A8);
	arch->registerInstruction(ControlFlow::GLoadRpointerWord8, LR8G);
	arch->registerInstruction(ControlFlow::ALoadRpointerWord8, LR8A);
	arch->registerInstruction(ControlFlow::PSaveWord8by8, SP8G8);
	arch->registerInstruction(ControlFlow::ASavePtr8by8, SP8A8);
	arch->registerInstruction(ControlFlow::RSaveGWord8, SR8G);
	arch->registerInstruction(ControlFlow::RSaveAWord8, SR8A);
}
