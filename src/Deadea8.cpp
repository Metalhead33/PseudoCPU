#include "include/Deadea8.hpp"

namespace Fcom {
Deadea8::Deadea8(uint8_t banknum)
	: AbstractProcessor<uint8_t,uint8_t>(255,banknum)
{
	RegisterInstruction(&EXIT,_EXIT);

	//Memory access instructions
	RegisterInstruction(&LOADA,_LOADA);
	RegisterInstruction(&LOADP,_LOADP);
	RegisterInstruction(&LOADPP,_LOADPP);
	RegisterInstruction(&STORP,_STORP);
	RegisterInstruction(&STORPP,_STORPP);
	RegisterInstruction(&BANKA,_BANKA);
	RegisterInstruction(&BANKP,_BANKP);
	RegisterInstruction(&BANKPP,_BANKPP);
	RegisterInstruction(&GOTOA,_GOTOA);
	RegisterInstruction(&GOTOP,_GOTOP);
	RegisterInstruction(&GOTOPP,_GOTOPP);

	//Arithmetic instruction
	RegisterInstruction(&ADDA,_ADDA);
	RegisterInstruction(&ADDP,_ADDP);
	RegisterInstruction(&ADDPP,_ADDPP);
	RegisterInstruction(&SUBA,_SUBA);
	RegisterInstruction(&SUBP,_SUBP);
	RegisterInstruction(&SUBPP,_SUBPP);

	//Bitwise instructions
	RegisterInstruction(&ANDA,_ANDA );
	RegisterInstruction(&ANDP,_ANDP );
	RegisterInstruction(&ANDPP,_ANDPP );
	RegisterInstruction(&ORA,_ORA );
	RegisterInstruction(&ORP,_ORP );
	RegisterInstruction(&ORPP,_ORPP );
	RegisterInstruction(&XORA,_XORA );
	RegisterInstruction(&XORP,_XORP );
	RegisterInstruction(&XORPP,_XORPP );
	RegisterInstruction(&NOT,_NOT );
}

Deadea8::~Deadea8()
{
	;
}

Pstate Deadea8::LOADA(RegisterStorage reg,uint8_t ammount)
{
	reg->AccumulatorRegister = ammount;
	return KEEP_GOING;
}
Pstate Deadea8::LOADP(RegisterStorage reg,uint8_t memspace)
{
	reg->AccumulatorRegister = reg->GetValue(memspace);
	return KEEP_GOING;
}
Pstate Deadea8::LOADPP(RegisterStorage reg,uint8_t memspace)
{
	reg->AccumulatorRegister = reg->MemoryJumpValue(memspace);
	return KEEP_GOING;
}
Pstate Deadea8::ADDA(RegisterStorage reg,uint8_t ammount)
{
	reg->AccumulatorRegister += ammount;
	return KEEP_GOING;
}
Pstate Deadea8::ADDP(RegisterStorage reg,uint8_t memspace)
{
	reg->AccumulatorRegister += reg->GetValue(memspace);
	return KEEP_GOING;
}
Pstate Deadea8::ADDPP(RegisterStorage reg,uint8_t memspace)
{
	reg->AccumulatorRegister += reg->MemoryJumpValue(memspace);
	return KEEP_GOING;
}
Pstate Deadea8::STORP(RegisterStorage reg,uint8_t memspace)
{
	*((uint8_t*)reg->GetAddress(memspace)) = reg->AccumulatorRegister;
	return KEEP_GOING;
}
Pstate Deadea8::STORPP(RegisterStorage reg,uint8_t memspace)
{
	*((uint8_t*)reg->MemoryJump(memspace)) = reg->AccumulatorRegister;
	return KEEP_GOING;
}
Pstate Deadea8::EXIT(RegisterStorage reg,uint8_t memspace)
{
	return STOP;
}
Pstate Deadea8::BANKA(RegisterStorage reg,uint8_t memspace)
{
	reg->BankCounter = memspace;
	return KEEP_GOING;
}
Pstate Deadea8::BANKP(RegisterStorage reg,uint8_t memspace)
{
	reg->BankCounter = reg->GetValue(memspace);
	return KEEP_GOING;
}
Pstate Deadea8::BANKPP(RegisterStorage reg,uint8_t memspace)
{
	reg->BankCounter = reg->MemoryJumpValue(memspace);
	return KEEP_GOING;
}
Pstate Deadea8::GOTOA(RegisterStorage reg,uint8_t memspace)
{
	reg->ProgramCounter = memspace;
	reg->AdjustPointer();
	return KEEP_GOING;
}
Pstate Deadea8::GOTOP(RegisterStorage reg,uint8_t memspace)
{
	reg->ProgramCounter = reg->GetValue(memspace);
	reg->AdjustPointer();
	return KEEP_GOING;
}
Pstate Deadea8::GOTOPP(RegisterStorage reg,uint8_t memspace)
{
	reg->ProgramCounter = reg->MemoryJumpValue(memspace);
	reg->AdjustPointer();
	return KEEP_GOING;
}
Pstate Deadea8::SUBA(RegisterStorage reg,uint8_t ammount)
{
	reg->AccumulatorRegister -= ammount;
	return KEEP_GOING;
}
Pstate Deadea8::SUBP(RegisterStorage reg,uint8_t memspace)
{
	reg->AccumulatorRegister -= reg->GetValue(memspace);
	return KEEP_GOING;
}
Pstate Deadea8::SUBPP(RegisterStorage reg,uint8_t memspace)
{
	reg->AccumulatorRegister -= reg->MemoryJumpValue(memspace);
	return KEEP_GOING;
}
Pstate Deadea8::LBWA(RegisterStorage reg,uint8_t ammount)
{
	reg->AccumulatorRegister = reg->AccumulatorRegister << ammount;
	return KEEP_GOING;
}
Pstate Deadea8::LBWP(RegisterStorage reg,uint8_t ammount)
{
	reg->AccumulatorRegister = reg->AccumulatorRegister << reg->GetValue(ammount);
	return KEEP_GOING;
}
Pstate Deadea8::LBWPP(RegisterStorage reg,uint8_t ammount)
{
	reg->AccumulatorRegister = reg->AccumulatorRegister << reg->MemoryJumpValue(ammount);
	return KEEP_GOING;
}
Pstate Deadea8::RBWA(RegisterStorage reg,uint8_t ammount)
{
	reg->AccumulatorRegister = reg->AccumulatorRegister >> ammount;
	return KEEP_GOING;
}
Pstate Deadea8::RBWP(RegisterStorage reg,uint8_t ammount)
{
	reg->AccumulatorRegister = reg->AccumulatorRegister >> reg->GetValue(ammount);
	return KEEP_GOING;
}
Pstate Deadea8::RBWPP(RegisterStorage reg,uint8_t ammount)
{
	reg->AccumulatorRegister = reg->AccumulatorRegister >> reg->MemoryJumpValue(ammount);
	return KEEP_GOING;
}
Pstate Deadea8::ANDA(RegisterStorage reg,uint8_t ammount)
{
	reg->AccumulatorRegister = reg->AccumulatorRegister & ammount;
	return KEEP_GOING;
}
Pstate Deadea8::ANDP(RegisterStorage reg,uint8_t ammount)
{
	reg->AccumulatorRegister = reg->AccumulatorRegister & reg->GetValue(ammount);
	return KEEP_GOING;
}
Pstate Deadea8::ANDPP(RegisterStorage reg,uint8_t ammount)
{
	reg->AccumulatorRegister = reg->AccumulatorRegister & reg->MemoryJumpValue(ammount);
	return KEEP_GOING;
}
Pstate Deadea8::ORA(RegisterStorage reg,uint8_t ammount)
{
	reg->AccumulatorRegister = reg->AccumulatorRegister | ammount;
	return KEEP_GOING;
}
Pstate Deadea8::ORP(RegisterStorage reg,uint8_t ammount)
{
	reg->AccumulatorRegister = reg->AccumulatorRegister | reg->GetValue(ammount);
	return KEEP_GOING;
}
Pstate Deadea8::ORPP(RegisterStorage reg,uint8_t ammount)
{
	reg->AccumulatorRegister = reg->AccumulatorRegister | reg->MemoryJumpValue(ammount);
	return KEEP_GOING;
}
Pstate Deadea8::XORA(RegisterStorage reg,uint8_t ammount)
{
	reg->AccumulatorRegister = reg->AccumulatorRegister ^ ammount;
	return KEEP_GOING;
}
Pstate Deadea8::XORP(RegisterStorage reg,uint8_t ammount)
{
	reg->AccumulatorRegister = reg->AccumulatorRegister ^ reg->GetValue(ammount);
	return KEEP_GOING;
}
Pstate Deadea8::XORPP(RegisterStorage reg,uint8_t ammount)
{
	reg->AccumulatorRegister = reg->AccumulatorRegister ^ reg->MemoryJumpValue(ammount);
	return KEEP_GOING;
}
Pstate Deadea8::NOT(RegisterStorage reg,uint8_t ammount)
{
	reg->AccumulatorRegister = ~reg->AccumulatorRegister;
	return KEEP_GOING;
}
}
