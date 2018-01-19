#include "ArithmeticalInstructions.hpp"

namespace Arithmetic {

// Floating point maths
ProcessorState FloatAdd(pAbstractProcessor proc)
{
	pword8n tmp;
	tmp.org.bytes[0] = *(proc->rawCastAccessMemoryAt<uint8_t>(proc->getAccessRegister(AbstractProcessor::PROGRAM_COUNTER)));
	proc->IncrementPC(sizeof(uint8_t));
	PaddedByteField<float> argA;
	PaddedByteField<float> argB;
	argA.padding = proc->getGeneralRegister(tmp.org.org.lower);
	argB.padding = proc->getGeneralRegister(tmp.org.org.upper);
	argA.org.org += argB.org.org;
	proc->setGeneralRegister(tmp.org.org.lower,argA.padding);
	return PROCEED;
} // Addition - 1 byte argument, it's 2 nibbles.
ProcessorState FloatSubtract(pAbstractProcessor proc)
{
	pword8n tmp;
	tmp.org.bytes[0] = *(proc->rawCastAccessMemoryAt<uint8_t>(proc->getAccessRegister(AbstractProcessor::PROGRAM_COUNTER)));
	proc->IncrementPC(sizeof(uint8_t));
	PaddedByteField<float> argA;
	PaddedByteField<float> argB;
	argA.padding = proc->getGeneralRegister(tmp.org.org.lower);
	argB.padding = proc->getGeneralRegister(tmp.org.org.upper);
	argA.org.org -= argB.org.org;
	proc->setGeneralRegister(tmp.org.org.lower,argA.padding);
	return PROCEED;
} // Subtraction - 1 byte argument, it's 2 nibbles.
ProcessorState FloatMultiplicate(pAbstractProcessor proc)
{
	pword8n tmp;
	tmp.org.bytes[0] = *(proc->rawCastAccessMemoryAt<uint8_t>(proc->getAccessRegister(AbstractProcessor::PROGRAM_COUNTER)));
	proc->IncrementPC(sizeof(uint8_t));
	PaddedByteField<float> argA;
	PaddedByteField<float> argB;
	argA.padding = proc->getGeneralRegister(tmp.org.org.lower);
	argB.padding = proc->getGeneralRegister(tmp.org.org.upper);
	argA.org.org *= argB.org.org;
	proc->setGeneralRegister(tmp.org.org.lower,argA.padding);
	return PROCEED;
} // Multiplication - 1 byte argument, it's 2 nibbles.
ProcessorState FloatDivide(pAbstractProcessor proc)
{
	pword8n tmp;
	tmp.org.bytes[0] = *(proc->rawCastAccessMemoryAt<uint8_t>(proc->getAccessRegister(AbstractProcessor::PROGRAM_COUNTER)));
	proc->IncrementPC(sizeof(uint8_t));
	PaddedByteField<float> argA;
	PaddedByteField<float> argB;
	argA.padding = proc->getGeneralRegister(tmp.org.org.lower);
	argB.padding = proc->getGeneralRegister(tmp.org.org.upper);
	argA.org.org /= argB.org.org;
	proc->setGeneralRegister(tmp.org.org.lower,argA.padding);
	return PROCEED;
} // Division - 1 byte argument, it's 2 nibbles.

// Normal maths-ish
ProcessorState Add(pAbstractProcessor proc) {
	pword8n tmp;
	tmp.org.bytes[0] = *(proc->rawCastAccessMemoryAt<uint8_t>(proc->getAccessRegister(AbstractProcessor::PROGRAM_COUNTER)));
	proc->IncrementPC(sizeof(uint8_t));
	proc->setGeneralRegister(tmp.org.org.lower,proc->getGeneralRegister(tmp.org.org.lower) + proc->getGeneralRegister(tmp.org.org.upper));
	return PROCEED;
} // Addition - 1 byte argument, it's 2 nibbles.
ProcessorState Subtract(pAbstractProcessor proc) {
	pword8n tmp;
	tmp.org.bytes[0] = *(proc->rawCastAccessMemoryAt<uint8_t>(proc->getAccessRegister(AbstractProcessor::PROGRAM_COUNTER)));
	proc->IncrementPC(sizeof(uint8_t));
	proc->setGeneralRegister(tmp.org.org.lower,proc->getGeneralRegister(tmp.org.org.lower) - proc->getGeneralRegister(tmp.org.org.upper));
	return PROCEED;
} // Subtraction - 1 byte argument, it's 2 nibbles.
ProcessorState Multiplicate(pAbstractProcessor proc) {
	pword8n tmp;
	tmp.org.bytes[0] = *(proc->rawCastAccessMemoryAt<uint8_t>(proc->getAccessRegister(AbstractProcessor::PROGRAM_COUNTER)));
	proc->IncrementPC(sizeof(uint8_t));
	proc->setGeneralRegister(tmp.org.org.lower,proc->getGeneralRegister(tmp.org.org.lower) * proc->getGeneralRegister(tmp.org.org.upper));
	return PROCEED;
} // Multiplication - 1 byte argument, it's 2 nibbles.
ProcessorState Divide(pAbstractProcessor proc) {
	pword8n tmp;
	tmp.org.bytes[0] = *(proc->rawCastAccessMemoryAt<uint8_t>(proc->getAccessRegister(AbstractProcessor::PROGRAM_COUNTER)));
	proc->IncrementPC(sizeof(uint8_t));
	proc->setGeneralRegister(tmp.org.org.lower,proc->getGeneralRegister(tmp.org.org.lower) / proc->getGeneralRegister(tmp.org.org.upper));
	return PROCEED;
} // Division - 1 byte argument, it's 2 nibbles.
ProcessorState Modulo(pAbstractProcessor proc) {
	pword8n tmp;
	tmp.org.bytes[0] = *(proc->rawCastAccessMemoryAt<uint8_t>(proc->getAccessRegister(AbstractProcessor::PROGRAM_COUNTER)));
	proc->IncrementPC(sizeof(uint8_t));
	proc->setGeneralRegister(tmp.org.org.lower,proc->getGeneralRegister(tmp.org.org.lower) % proc->getGeneralRegister(tmp.org.org.upper));
	return PROCEED;
} // Modulo - 1 byte argument, it's 2 nibbles.
// Logical
ProcessorState LogicalNot(pAbstractProcessor proc) {
	pword8n tmp;
	tmp.org.bytes[0] = *(proc->rawCastAccessMemoryAt<uint8_t>(proc->getAccessRegister(AbstractProcessor::PROGRAM_COUNTER)));
	proc->IncrementPC(sizeof(uint8_t));
	proc->setGeneralRegister(tmp.org.org.lower,!proc->getGeneralRegister(tmp.org.org.lower) );
	return PROCEED;
} // Logical NOT - 1 byte argument, it's 2 nibbles.
ProcessorState LogicalAnd(pAbstractProcessor proc) {
	pword8n tmp;
	tmp.org.bytes[0] = *(proc->rawCastAccessMemoryAt<uint8_t>(proc->getAccessRegister(AbstractProcessor::PROGRAM_COUNTER)));
	proc->IncrementPC(sizeof(uint8_t));
	proc->setGeneralRegister(tmp.org.org.lower,proc->getGeneralRegister(tmp.org.org.lower) && proc->getGeneralRegister(tmp.org.org.upper));
	return PROCEED;
} // Logical AND - 1 byte argument, it's 2 nibbles.
ProcessorState LogicalInclusiveOr(pAbstractProcessor proc) {
	pword8n tmp;
	tmp.org.bytes[0] = *(proc->rawCastAccessMemoryAt<uint8_t>(proc->getAccessRegister(AbstractProcessor::PROGRAM_COUNTER)));
	proc->IncrementPC(sizeof(uint8_t));
	proc->setGeneralRegister(tmp.org.org.lower,proc->getGeneralRegister(tmp.org.org.lower) || proc->getGeneralRegister(tmp.org.org.upper));
	return PROCEED;
} // Logical OR - 1 byte argument, it's 2 nibbles.
ProcessorState LogicalExclusiveOr(pAbstractProcessor proc) {
	pword8n tmp;
	tmp.org.bytes[0] = *(proc->rawCastAccessMemoryAt<uint8_t>(proc->getAccessRegister(AbstractProcessor::PROGRAM_COUNTER)));
	proc->IncrementPC(sizeof(uint8_t));
	proc->setGeneralRegister(tmp.org.org.lower,!proc->getGeneralRegister(tmp.org.org.lower) != !proc->getGeneralRegister(tmp.org.org.upper));
	return PROCEED;
} // Logical XOR - 1 byte argument, it's 2 nibbles.
// Bitwise
ProcessorState BitwiseNot(pAbstractProcessor proc) {
	pword8n tmp;
	tmp.org.bytes[0] = *(proc->rawCastAccessMemoryAt<uint8_t>(proc->getAccessRegister(AbstractProcessor::PROGRAM_COUNTER)));
	proc->IncrementPC(sizeof(uint8_t));
	proc->setGeneralRegister(tmp.org.org.lower,~proc->getGeneralRegister(tmp.org.org.lower) );
	return PROCEED;
} // Bitwise NOT - 1 byte argument, it's 2 nibbles.
ProcessorState BitwiseAnd(pAbstractProcessor proc) {
	pword8n tmp;
	tmp.org.bytes[0] = *(proc->rawCastAccessMemoryAt<uint8_t>(proc->getAccessRegister(AbstractProcessor::PROGRAM_COUNTER)));
	proc->IncrementPC(sizeof(uint8_t));
	proc->setGeneralRegister(tmp.org.org.lower,proc->getGeneralRegister(tmp.org.org.lower) & proc->getGeneralRegister(tmp.org.org.upper));
	return PROCEED;
} // Bitwise AND - 1 byte argument, it's 2 nibbles.
ProcessorState BitwiseInclusiveOr(pAbstractProcessor proc) {
	pword8n tmp;
	tmp.org.bytes[0] = *(proc->rawCastAccessMemoryAt<uint8_t>(proc->getAccessRegister(AbstractProcessor::PROGRAM_COUNTER)));
	proc->IncrementPC(sizeof(uint8_t));
	proc->setGeneralRegister(tmp.org.org.lower,proc->getGeneralRegister(tmp.org.org.lower) | proc->getGeneralRegister(tmp.org.org.upper));
	return PROCEED;
} // Bitwise OR - 1 byte argument, it's 2 nibbles.
ProcessorState BitwisexclusiveOr(pAbstractProcessor proc) {
	pword8n tmp;
	tmp.org.bytes[0] = *(proc->rawCastAccessMemoryAt<uint8_t>(proc->getAccessRegister(AbstractProcessor::PROGRAM_COUNTER)));
	proc->IncrementPC(sizeof(uint8_t));
	proc->setGeneralRegister(tmp.org.org.lower,proc->getGeneralRegister(tmp.org.org.lower) ^ proc->getGeneralRegister(tmp.org.org.upper));
	return PROCEED;
} // Bitwise XOR - 1 byte argument, it's 2 nibbles.
ProcessorState BitwiseLeftShift(pAbstractProcessor proc) {
	pword8n tmp;
	tmp.org.bytes[0] = *(proc->rawCastAccessMemoryAt<uint8_t>(proc->getAccessRegister(AbstractProcessor::PROGRAM_COUNTER)));
	proc->IncrementPC(sizeof(uint8_t));
	proc->setGeneralRegister(tmp.org.org.lower,proc->getGeneralRegister(tmp.org.org.lower) << proc->getGeneralRegister(tmp.org.org.upper));
	return PROCEED;
} // Bitwise Left Shift - 1 byte argument, it's 2 nibbles.
ProcessorState BitwiseRightShift(pAbstractProcessor proc) {
	pword8n tmp;
	tmp.org.bytes[0] = *(proc->rawCastAccessMemoryAt<uint8_t>(proc->getAccessRegister(AbstractProcessor::PROGRAM_COUNTER)));
	proc->IncrementPC(sizeof(uint8_t));
	proc->setGeneralRegister(tmp.org.org.lower,proc->getGeneralRegister(tmp.org.org.lower) >> proc->getGeneralRegister(tmp.org.org.upper));
	return PROCEED;
} // Bitwise Right Shift - 1 byte argument, it's 2 nibbles.
}
