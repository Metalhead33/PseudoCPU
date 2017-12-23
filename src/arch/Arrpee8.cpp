#include "include/arch/Arrpee8.hpp"
#include <cstring>

Arrpee8::sInstructionSet Arrpee8::singleton = 0;
Arrpee8::sInstructionSet Arrpee8::getSingleton()
{
	if(!singleton) singleton = sInstructionSet(new Arrpee8());
	return singleton;
}
Arrpee8::Arrpee8()
	: InstructionSet<uint8_t,uint16_t,uint16_t>(PAD)
{
	uploadInstruction(NOP, __NOP);
	uploadInstruction(POFF, __POFF);
	uploadInstruction(ADD, __ADD);
	uploadInstruction(NEG, __NEG);
	uploadInstruction(MUL, __MUL);
	uploadInstruction(DIV, __DIV);
	uploadInstruction(MOD, __MOD);
	uploadInstruction(BSL, __BSL);
	uploadInstruction(BSR, __BSR);
	uploadInstruction(LAND, __LAND);
	uploadInstruction(BAND, __BAND);
	uploadInstruction(LIOR, __LIOR);
	uploadInstruction(BIOR, __BIOR);
	uploadInstruction(LXOR, __LXOR);
	uploadInstruction(BXOR, __BXOR);
	uploadInstruction(LNOT, __LNOT);
	uploadInstruction(BNOT, __BNOT);
	uploadInstruction(SHFA, __SHFA);
	uploadInstruction(LDACD8, __LDACD8);
	uploadInstruction(LDARD8, __LDARD8);
	uploadInstruction(LDACD16, __LDACD16);
	uploadInstruction(LDARD16, __LDARD16);
	uploadInstruction(LDSPD16, __LDSPD16);
	uploadInstruction(LDSMD16, __LDSMD16);
	uploadInstruction(LDSCD16, __LDSCD16);
	uploadInstruction(LDACP8_16, __LDACP8_16);
	uploadInstruction(LDARP8_16, __LDARP8_16);
	uploadInstruction(LDACP16_16, __LDACP16_16);
	uploadInstruction(LDARP16_16, __LDARP16_16);
	uploadInstruction(LDSPP16_16, __LDSPP16_16);
	uploadInstruction(LDSMP16_16, __LDSMP16_16);
	uploadInstruction(LDSCP16_16, __LDSCP16_16);
	uploadInstruction(STAC8_16, __STAC8_16);
	uploadInstruction(STAR8_16, __STAR8_16);
	uploadInstruction(STAC16_16, __STAC16_16);
	uploadInstruction(STAR16_16, __STAR16_16);
	uploadInstruction(STSP16_16, __STSP16_16);
	uploadInstruction(STSM16_16, __STSM16_16);
	uploadInstruction(STSC16_16, __STSC16_16);
	uploadInstruction(MEMCPY16, __MEMCPY16);
	uploadInstruction(IFEQ, __IFEQ);
	uploadInstruction(IFGR, __IFGR);
	uploadInstruction(IFGE, __IFGE);
	uploadInstruction(ILGR, __ILGR);
	uploadInstruction(ILGE, __ILGE);
	uploadInstruction(IFB, __IFB);
	uploadInstruction(STB, __STB);
	uploadInstruction(GOTO_16, __GOTO_16);
	uploadInstruction(IFJM_16, __IFJM_16);
	uploadInstruction(SUBR_16, __SUBR_16);
	uploadInstruction(RETURN, __RETURN);
}

ComputerState Arrpee8::__NOP(StatePointer STATE)
{
	return GO_ON;
}

ComputerState Arrpee8::__POFF(StatePointer STATE)
{
	return SHUTDOWN;
}

ComputerState Arrpee8::__ADD(StatePointer STATE)
{
	STATE->setAccumulator(STATE->getAccumulator().org + STATE->getArgument().org);
	return GO_ON;
}

ComputerState Arrpee8::__NEG(StatePointer STATE)
{
	STATE->setAccumulator(STATE->getAccumulator().org - STATE->getArgument().org);
	return GO_ON;
}

ComputerState Arrpee8::__MUL(StatePointer STATE)
{
	STATE->setAccumulator(STATE->getAccumulator().org * STATE->getArgument().org);
	return GO_ON;
}

ComputerState Arrpee8::__DIV(StatePointer STATE)
{
	STATE->setAccumulator(STATE->getAccumulator().org / STATE->getArgument().org);
	return GO_ON;
}

ComputerState Arrpee8::__MOD(StatePointer STATE)
{
	STATE->setAccumulator(STATE->getAccumulator().org % STATE->getArgument().org);
	return GO_ON;
}

ComputerState Arrpee8::__BSL(StatePointer STATE)
{
	STATE->setAccumulator(STATE->getAccumulator().org << STATE->getArgument().org);
	return GO_ON;
}

ComputerState Arrpee8::__BSR(StatePointer STATE)
{
	STATE->setAccumulator(STATE->getAccumulator().org >> STATE->getArgument().org);
	return GO_ON;
}

ComputerState Arrpee8::__LAND(StatePointer STATE)
{
	STATE->setAccumulator(STATE->getAccumulator().org && STATE->getArgument().org);
	return GO_ON;
}

ComputerState Arrpee8::__BAND(StatePointer STATE)
{
	STATE->setAccumulator(STATE->getAccumulator().org & STATE->getArgument().org);
	return GO_ON;
}

ComputerState Arrpee8::__LIOR(StatePointer STATE)
{
	STATE->setAccumulator(STATE->getAccumulator().org || STATE->getArgument().org);
	return GO_ON;
}

ComputerState Arrpee8::__BIOR(StatePointer STATE)
{
	STATE->setAccumulator(STATE->getAccumulator().org | STATE->getArgument().org);
	return GO_ON;
}

ComputerState Arrpee8::__LXOR(StatePointer STATE)
{
	STATE->setAccumulator(!STATE->getAccumulator().org != !STATE->getArgument().org);
	return GO_ON;
}

ComputerState Arrpee8::__BXOR(StatePointer STATE)
{
	STATE->setAccumulator(STATE->getAccumulator().org ^ STATE->getArgument().org);
	return GO_ON;
}

ComputerState Arrpee8::__LNOT(StatePointer STATE)
{
	STATE->setAccumulator(!STATE->getAccumulator().org);
	return GO_ON;
}

ComputerState Arrpee8::__BNOT(StatePointer STATE)
{
	STATE->setAccumulator(~STATE->getAccumulator().org);
	return GO_ON;
}

ComputerState Arrpee8::__SHFA(StatePointer STATE)
{
	uint16_t temp = STATE->getAccumulator().org;
	STATE->setAccumulator(STATE->getAccumulator());
	STATE->setArgument(temp);
	return GO_ON;
}

ComputerState Arrpee8::__LDACD8(StatePointer STATE)
{
	STATE->IncrementPC(sizeof(uint8_t));
	STATE->setAccumulator(*reinterpret_cast<uint8_t*>(STATE->getMemoryPoint(STATE->getProgramCounter().org)) );
	STATE->IncrementPC(sizeof(uint8_t));
	return GO_TO;
}

ComputerState Arrpee8::__LDARD8(StatePointer STATE)
{
	STATE->IncrementPC(sizeof(uint8_t));
	STATE->setArgument(*reinterpret_cast<uint8_t*>(STATE->getMemoryPoint(STATE->getProgramCounter().org)) );
	STATE->IncrementPC(sizeof(uint8_t));
	return GO_TO;
}

ComputerState Arrpee8::__LDACD16(StatePointer STATE)
{
	STATE->IncrementPC(sizeof(uint8_t));
	STATE->setAccumulator(*reinterpret_cast<uint16_t*>(STATE->getMemoryPoint(STATE->getProgramCounter().org)) );
	STATE->IncrementPC(sizeof(uint16_t));
	return GO_TO;
}

ComputerState Arrpee8::__LDARD16(StatePointer STATE)
{
	STATE->IncrementPC(sizeof(uint8_t));
	STATE->setArgument(*reinterpret_cast<uint16_t*>(STATE->getMemoryPoint(STATE->getProgramCounter().org)) );
	STATE->IncrementPC(sizeof(uint16_t));
	return GO_TO;
}

ComputerState Arrpee8::__LDSPD16(StatePointer STATE)
{
	STATE->IncrementPC(sizeof(uint8_t));
	STATE->setStackPointer(*reinterpret_cast<uint16_t*>(STATE->getMemoryPoint(STATE->getProgramCounter().org)) );
	STATE->IncrementPC(sizeof(uint16_t));
	return GO_TO;
}

ComputerState Arrpee8::__LDSMD16(StatePointer STATE)
{
	STATE->IncrementPC(sizeof(uint8_t));
	STATE->setStackMaxSize(*reinterpret_cast<uint16_t*>(STATE->getMemoryPoint(STATE->getProgramCounter().org)) );
	STATE->IncrementPC(sizeof(uint16_t));
	return GO_TO;
}

ComputerState Arrpee8::__LDSCD16(StatePointer STATE)
{
	STATE->IncrementPC(sizeof(uint8_t));
	STATE->setStackCurSize(*reinterpret_cast<uint16_t*>(STATE->getMemoryPoint(STATE->getProgramCounter().org)) );
	STATE->IncrementPC(sizeof(uint16_t));
	return GO_TO;
}

ComputerState Arrpee8::__LDACP8_16(StatePointer STATE)
{
	STATE->IncrementPC(sizeof(uint8_t));
	uint16_t temp = *reinterpret_cast<uint16_t*>(STATE->getMemoryPoint(STATE->getProgramCounter().org));
	STATE->IncrementPC(sizeof(uint16_t));
	STATE->setAccumulator(*reinterpret_cast<uint8_t*>(STATE->getMemoryPoint(temp)) );
	return GO_TO;
}

ComputerState Arrpee8::__LDARP8_16(StatePointer STATE)
{
	STATE->IncrementPC(sizeof(uint8_t));
	uint16_t temp = *reinterpret_cast<uint16_t*>(STATE->getMemoryPoint(STATE->getProgramCounter().org));
	STATE->IncrementPC(sizeof(uint16_t));
	STATE->setArgument(*reinterpret_cast<uint8_t*>(STATE->getMemoryPoint(temp)) );
	return GO_TO;
}

ComputerState Arrpee8::__LDACP16_16(StatePointer STATE)
{
	STATE->IncrementPC(sizeof(uint8_t));
	uint16_t temp = *reinterpret_cast<uint16_t*>(STATE->getMemoryPoint(STATE->getProgramCounter().org));
	STATE->IncrementPC(sizeof(uint16_t));
	STATE->setAccumulator(*reinterpret_cast<uint16_t*>(STATE->getMemoryPoint(temp)) );
	return GO_TO;
}

ComputerState Arrpee8::__LDARP16_16(StatePointer STATE)
{
	STATE->IncrementPC(sizeof(uint8_t));
	uint16_t temp = *reinterpret_cast<uint16_t*>(STATE->getMemoryPoint(STATE->getProgramCounter().org));
	STATE->IncrementPC(sizeof(uint16_t));
	STATE->setArgument(*reinterpret_cast<uint16_t*>(STATE->getMemoryPoint(temp)) );
	return GO_TO;
}

ComputerState Arrpee8::__LDSPP16_16(StatePointer STATE)
{
	STATE->IncrementPC(sizeof(uint8_t));
	uint16_t temp = *reinterpret_cast<uint16_t*>(STATE->getMemoryPoint(STATE->getProgramCounter().org));
	STATE->IncrementPC(sizeof(uint16_t));
	STATE->setStackPointer(*reinterpret_cast<uint16_t*>(STATE->getMemoryPoint(temp)) );
	return GO_TO;
}

ComputerState Arrpee8::__LDSMP16_16(StatePointer STATE)
{
	STATE->IncrementPC(sizeof(uint8_t));
	uint16_t temp = *reinterpret_cast<uint16_t*>(STATE->getMemoryPoint(STATE->getProgramCounter().org));
	STATE->IncrementPC(sizeof(uint16_t));
	STATE->setStackMaxSize(*reinterpret_cast<uint16_t*>(STATE->getMemoryPoint(temp)) );
	return GO_TO;
}

ComputerState Arrpee8::__LDSCP16_16(StatePointer STATE)
{
	STATE->IncrementPC(sizeof(uint8_t));
	uint16_t temp = *reinterpret_cast<uint16_t*>(STATE->getMemoryPoint(STATE->getProgramCounter().org));
	STATE->IncrementPC(sizeof(uint16_t));
	STATE->setStackCurSize(*reinterpret_cast<uint16_t*>(STATE->getMemoryPoint(temp)) );
	return GO_TO;
}

ComputerState Arrpee8::__STAC8_16(StatePointer STATE)
{
	STATE->IncrementPC(sizeof(uint8_t));
	uint16_t temp = *reinterpret_cast<uint16_t*>(STATE->getMemoryPoint(STATE->getProgramCounter().org));
	STATE->IncrementPC(sizeof(uint16_t));
	*reinterpret_cast<uint8_t*>(STATE->getMemoryPoint(temp)) = STATE->getAccumulator().buf[0];
	return GO_TO;
}

ComputerState Arrpee8::__STAR8_16(StatePointer STATE)
{
	STATE->IncrementPC(sizeof(uint8_t));
	uint16_t temp = *reinterpret_cast<uint16_t*>(STATE->getMemoryPoint(STATE->getProgramCounter().org));
	STATE->IncrementPC(sizeof(uint16_t));
	*reinterpret_cast<uint8_t*>(STATE->getMemoryPoint(temp)) = STATE->getArgument().buf[0];
	return GO_TO;
}

ComputerState Arrpee8::__STAC16_16(StatePointer STATE)
{
	STATE->IncrementPC(sizeof(uint8_t));
	uint16_t temp = *reinterpret_cast<uint16_t*>(STATE->getMemoryPoint(STATE->getProgramCounter().org));
	STATE->IncrementPC(sizeof(uint16_t));
	*reinterpret_cast<uint16_t*>(STATE->getMemoryPoint(temp)) = STATE->getAccumulator().org;
	return GO_TO;
}

ComputerState Arrpee8::__STAR16_16(StatePointer STATE)
{
	STATE->IncrementPC(sizeof(uint8_t));
	uint16_t temp = *reinterpret_cast<uint16_t*>(STATE->getMemoryPoint(STATE->getProgramCounter().org));
	STATE->IncrementPC(sizeof(uint16_t));
	*reinterpret_cast<uint16_t*>(STATE->getMemoryPoint(temp)) = STATE->getArgument().org;
	return GO_TO;
}

ComputerState Arrpee8::__STSP16_16(StatePointer STATE)
{
	STATE->IncrementPC(sizeof(uint8_t));
	uint16_t temp = *reinterpret_cast<uint16_t*>(STATE->getMemoryPoint(STATE->getProgramCounter().org));
	STATE->IncrementPC(sizeof(uint16_t));
	*reinterpret_cast<uint16_t*>(STATE->getMemoryPoint(temp)) = STATE->getStackPointer().org;
	return GO_TO;
}

ComputerState Arrpee8::__STSM16_16(StatePointer STATE)
{
	STATE->IncrementPC(sizeof(uint8_t));
	uint16_t temp = *reinterpret_cast<uint16_t*>(STATE->getMemoryPoint(STATE->getProgramCounter().org));
	STATE->IncrementPC(sizeof(uint16_t));
	*reinterpret_cast<uint16_t*>(STATE->getMemoryPoint(temp)) = STATE->getStackMaxSize().org;
	return GO_TO;
}

ComputerState Arrpee8::__STSC16_16(StatePointer STATE)
{
	STATE->IncrementPC(sizeof(uint8_t));
	uint16_t temp = *reinterpret_cast<uint16_t*>(STATE->getMemoryPoint(STATE->getProgramCounter().org));
	STATE->IncrementPC(sizeof(uint16_t));
	*reinterpret_cast<uint16_t*>(STATE->getMemoryPoint(temp)) = STATE->getStackCurSize().org;
	return GO_TO;
}

ComputerState Arrpee8::__MEMCPY16(StatePointer STATE)
{
	STATE->IncrementPC(sizeof(uint8_t));
	uint16_t source = *reinterpret_cast<uint16_t*>(STATE->getMemoryPoint(STATE->getProgramCounter().org));
	STATE->IncrementPC(sizeof(uint16_t));
	uint16_t destination = *reinterpret_cast<uint16_t*>(STATE->getMemoryPoint(STATE->getProgramCounter().org));
	STATE->IncrementPC(sizeof(uint16_t));
	uint16_t ammount = *reinterpret_cast<uint16_t*>(STATE->getMemoryPoint(STATE->getProgramCounter().org));
	STATE->IncrementPC(sizeof(uint16_t));
	memcpy(STATE->getMemoryPoint(destination),STATE->getMemoryPoint(source),ammount);
	return GO_TO;
}

ComputerState Arrpee8::__IFEQ(StatePointer STATE)
{
	STATE->setAccumulator( STATE->getAccumulator().org == STATE->getArgument().org );
	return GO_ON;
}

ComputerState Arrpee8::__IFGR(StatePointer STATE)
{
	STATE->setAccumulator( STATE->getAccumulator().org > STATE->getArgument().org );
	return GO_ON;
}

ComputerState Arrpee8::__IFGE(StatePointer STATE)
{
	STATE->setAccumulator( STATE->getAccumulator().org >= STATE->getArgument().org );
	return GO_ON;
}

ComputerState Arrpee8::__ILGR(StatePointer STATE)
{
	STATE->setAccumulator( STATE->getAccumulator().org < STATE->getArgument().org );
	return GO_ON;
}

ComputerState Arrpee8::__ILGE(StatePointer STATE)
{
	STATE->setAccumulator( STATE->getAccumulator().org <= STATE->getArgument().org );
	return GO_ON;
}

ComputerState Arrpee8::__IFB(StatePointer STATE)
{
	STATE->setAccumulator( (STATE->getAccumulator().org & (1 << STATE->getArgument().org)) != 0 );
	return GO_ON;
}

ComputerState Arrpee8::__STB(StatePointer STATE)
{
	STATE->setAccumulator( STATE->getAccumulator().org | (1 << STATE->getArgument().org) );
	return GO_ON;
}

ComputerState Arrpee8::__GOTO_16(StatePointer STATE)
{
	STATE->IncrementPC(sizeof(uint8_t));
	STATE->setProgramCounter(*reinterpret_cast<uint16_t*>(STATE->getMemoryPoint(STATE->getProgramCounter().org)));
	return GO_TO;
}

ComputerState Arrpee8::__IFJM_16(StatePointer STATE)
{
	STATE->IncrementPC(sizeof(uint8_t));
	if(STATE->getAccumulator().org)
	{
		uint16_t newPlace = *reinterpret_cast<uint16_t*>(STATE->getMemoryPoint(STATE->getProgramCounter().org));
		uint16_t stackPlace = STATE->getStackPointer().org + (STATE->getStackCurSize().org * sizeof(uint16_t));
		STATE->IncrementPC(sizeof(uint16_t));
		STATE->setStackCurSize(STATE->getStackCurSize().org + 1);
		*reinterpret_cast<uint16_t*>(STATE->getMemoryPoint(stackPlace)) = STATE->getProgramCounter().org;
		STATE->setProgramCounter(newPlace);
	}
	else STATE->IncrementPC(sizeof(uint16_t));
	return GO_TO;
}

ComputerState Arrpee8::__SUBR_16(StatePointer STATE)
{
	STATE->IncrementPC(sizeof(uint8_t));
	uint16_t newPlace = *reinterpret_cast<uint16_t*>(STATE->getMemoryPoint(STATE->getProgramCounter().org));
	uint16_t stackPlace = STATE->getStackPointer().org + (STATE->getStackCurSize().org * sizeof(uint16_t));
	STATE->IncrementPC(sizeof(uint16_t));
	STATE->setStackCurSize(STATE->getStackCurSize().org + 1);
	*reinterpret_cast<uint16_t*>(STATE->getMemoryPoint(stackPlace)) = STATE->getProgramCounter().org;
	STATE->setProgramCounter(newPlace);
	return GO_TO;
}

ComputerState Arrpee8::__RETURN(StatePointer STATE)
{
	STATE->IncrementPC(sizeof(uint8_t));
	uint16_t newPlace = STATE->getStackPointer().org + ((STATE->getStackCurSize().org - 1) * sizeof(uint16_t));
	uint16_t newPointer = *reinterpret_cast<uint16_t*>(STATE->getMemoryPoint(newPlace));
	STATE->setStackCurSize(STATE->getStackCurSize().org - 1);
	STATE->setProgramCounter(newPointer);
	return GO_TO;
}
