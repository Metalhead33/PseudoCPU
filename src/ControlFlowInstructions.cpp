#include "include/ControlFlowInstructions.hpp"
namespace ControlFlow {
ProcessorState Nope(pAbstractProcessor proc)
{
	return PROCEED;
} // Does absolutely nothing
ProcessorState Ret(pAbstractProcessor proc)
{
	return RETURN;
} // Returns to the original position
ProcessorState Freeze(pAbstractProcessor proc)
{
	return IDLE;
} // Freezes the computer
ProcessorState Poweroff(pAbstractProcessor proc)
{
	return POWEROFF;
} // Turns off the computer
ProcessorState Panic(pAbstractProcessor proc)
{
	return PANIC;
} // Turns off the computer, because of error

ProcessorState GeneralMove(pAbstractProcessor proc)
{
	uint8_t regAddr;
	regAddr = *(proc->rawCastAccessMemoryAt<uint8_t>(proc->getAccessRegister(AbstractProcessor::PROGRAM_COUNTER)));
	proc->IncrementPC(sizeof(uint8_t));
	proc->movGeneralRegisters(regAddr);
	return PROCEED;
} // Moves from one general register to another. Operand is 1-byte, actually two nibbles.
ProcessorState AddressMove(pAbstractProcessor proc)
{
	uint8_t regAddr;
	regAddr = *(proc->rawCastAccessMemoryAt<uint8_t>(proc->getAccessRegister(AbstractProcessor::PROGRAM_COUNTER)));
	proc->IncrementPC(sizeof(uint8_t));
	proc->movAddressRegisters(regAddr);
	return PROCEED;
} // Moves from one address register to another. Operand is 1-byte, actually two nibbles.
ProcessorState GeneralShuffle(pAbstractProcessor proc)
{
	uint8_t regAddr;
	regAddr = *(proc->rawCastAccessMemoryAt<uint8_t>(proc->getAccessRegister(AbstractProcessor::PROGRAM_COUNTER)));
	proc->IncrementPC(sizeof(uint8_t));
	proc->swapGeneralRegisters(regAddr);
	return PROCEED;
} // Switches up the contents of two general registers. Operand is 1-byte, actually two nibbles.
ProcessorState AddressShuffle(pAbstractProcessor proc)
{
	uint8_t regAddr;
	regAddr = *(proc->rawCastAccessMemoryAt<uint8_t>(proc->getAccessRegister(AbstractProcessor::PROGRAM_COUNTER)));
	proc->IncrementPC(sizeof(uint8_t));
	proc->swapAddressRegisters(regAddr);
	return PROCEED;
} // Switches up the content of two address registers. Operand is 1-byte, actually two nibbles.

ProcessorState GotoRptr(pAbstractProcessor proc)
{
	uint8_t regAddr;
	regAddr = *(proc->rawCastAccessMemoryAt<uint8_t>(proc->getAccessRegister(AbstractProcessor::PROGRAM_COUNTER)));
	// proc->IncrementPC(sizeof(uint8_t)); // Unnecessary
	proc->setAccessRegister(AbstractProcessor::PROGRAM_COUNTER,proc->getAccessRegister(regAddr));
	return PROCEED;
} // Jumps to address pointer by address stored in register referenced by the operand, which is a 1-byte integer
ProcessorState SubrRptr(pAbstractProcessor proc)
{
	uint8_t regAddr;
	regAddr = *(proc->rawCastAccessMemoryAt<uint8_t>(proc->getAccessRegister(AbstractProcessor::PROGRAM_COUNTER)));
	proc->IncrementPC(sizeof(uint8_t));
	proc->startNormalSubroutine(proc->getAccessRegister(regAddr));
	return PROCEED;
} // Starts subroutine by jumping to address pointer by address stored in register referenced by the operand, which is a 1-byte integer
ProcessorState JSubrRptr(pAbstractProcessor proc)
{
	uint8_t regAddr;
	regAddr = *(proc->rawCastAccessMemoryAt<uint8_t>(proc->getAccessRegister(AbstractProcessor::PROGRAM_COUNTER)));
	proc->IncrementPC(sizeof(uint8_t));
	proc->startJailedSubroutine(proc->getAccessRegister(regAddr));
	return PROCEED;
} // Starts jailed subroutine by jumping to address pointer by address stored in register referenced by the operand, which is a 1-byte integer

ProcessorState ConGotoRptr(pAbstractProcessor proc)
{
	pword8n tmp;
	tmp.org.bytes[0] = *(proc->rawCastAccessMemoryAt<uint8_t>(proc->getAccessRegister(AbstractProcessor::PROGRAM_COUNTER)));
	proc->IncrementPC(sizeof(uint8_t));
	if(proc->getGeneralRegister(tmp.org.org.lower)) proc->setAccessRegister(AbstractProcessor::PROGRAM_COUNTER,proc->getAccessRegister(tmp.org.org.upper));
	return PROCEED;
} // Conditional jump to address. Operand is 1-byte int, actually two nibbles.
ProcessorState ConSubrRptr(pAbstractProcessor proc)
{
	pword8n tmp;
	tmp.org.bytes[0] = *(proc->rawCastAccessMemoryAt<uint8_t>(proc->getAccessRegister(AbstractProcessor::PROGRAM_COUNTER)));
	proc->IncrementPC(sizeof(uint8_t));
	if(proc->getGeneralRegister(tmp.org.org.lower)) proc->startNormalSubroutine(proc->getAccessRegister(tmp.org.org.upper));
	return PROCEED;
} // Conditional start of subroutine.
ProcessorState ConJSubrRptr(pAbstractProcessor proc)
{
	pword8n tmp;
	tmp.org.bytes[0] = *(proc->rawCastAccessMemoryAt<uint8_t>(proc->getAccessRegister(AbstractProcessor::PROGRAM_COUNTER)));
	proc->IncrementPC(sizeof(uint8_t));
	if(proc->getGeneralRegister(tmp.org.org.lower)) proc->startJailedSubroutine(proc->getAccessRegister(tmp.org.org.upper));
	return PROCEED;
} // Conditional start of jailed subroutine
}
