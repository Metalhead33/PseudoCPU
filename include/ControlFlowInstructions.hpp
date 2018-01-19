#pragma once
#include "abstract/AbstractProcessor.hpp"
#include <cstring>
namespace ControlFlow {
// These instructions have no operands at all
ProcessorState Nope(pAbstractProcessor proc); // Does absolutely nothing
ProcessorState Ret(pAbstractProcessor proc); // Returns to the original position
ProcessorState Freeze(pAbstractProcessor proc); // Freezes the computer
ProcessorState Poweroff(pAbstractProcessor proc); // Turns off the computer
ProcessorState Panic(pAbstractProcessor proc); // Turns off the computer, because of error

ProcessorState GeneralMove(pAbstractProcessor proc); // Moves from one general register to another. Operand is 1-byte, actually two nibbles.
ProcessorState AddressMove(pAbstractProcessor proc); // Moves from one address register to another. Operand is 1-byte, actually two nibbles.
ProcessorState GeneralShuffle(pAbstractProcessor proc); // Switches up the contents of two general registers. Operand is 1-byte, actually two nibbles.
ProcessorState AddressShuffle(pAbstractProcessor proc); // Switches up the content of two address registers. Operand is 1-byte, actually two nibbles.

ProcessorState GotoRptr(pAbstractProcessor proc); // Jumps to address pointer by address stored in register referenced by the operand, which is a 1-byte integer
ProcessorState SubrRptr(pAbstractProcessor proc); // Starts subroutine by jumping to address pointer by address stored in register referenced by the operand, which is a 1-byte integer
ProcessorState JSubrRptr(pAbstractProcessor proc); // Starts jailed subroutine by jumping to address pointer by address stored in register referenced by the operand, which is a 1-byte integer

ProcessorState ConGotoRptr(pAbstractProcessor proc); // Conditional jump to address. Operand is 1-byte int, actually two nibbles.
ProcessorState ConSubrRptr(pAbstractProcessor proc); // Conditional start of subroutine.
ProcessorState ConJSubrRptr(pAbstractProcessor proc); // Conditional start of jailed subroutine

template <typename AddressSize> ProcessorState GotoCptr(pAbstractProcessor proc)
{
	PaddedByteField<AddressSize> ptr;
	ptr.org.org = *(proc->rawCastAccessMemoryAt<AddressSize>(proc->getAccessRegister(AbstractProcessor::PROGRAM_COUNTER)));
	proc->IncrementPC(sizeof(AddressSize));
	proc->setAccessRegister(AbstractProcessor::PROGRAM_COUNTER,ptr.padding);
	return PROCEED;
} // Jumps to the address given in the operand
template <typename AddressSize> ProcessorState SubrCptr(pAbstractProcessor proc)
{
	PaddedByteField<AddressSize> ptr;
	ptr.padding = 0;
	ptr.org.org = *(proc->rawCastAccessMemoryAt<AddressSize>(proc->getAccessRegister(AbstractProcessor::PROGRAM_COUNTER)));
	proc->IncrementPC(sizeof(AddressSize));
	proc->startNormalSubroutine(ptr.padding);
	return PROCEED;
} // Starts a subroutine by jumping to the address given in the operand
template <typename AddressSize> ProcessorState JSubrCptr(pAbstractProcessor proc)
{
	PaddedByteField<AddressSize> ptr;
	ptr.padding = 0;
	ptr.org.org = *(proc->rawCastAccessMemoryAt<AddressSize>(proc->getAccessRegister(AbstractProcessor::PROGRAM_COUNTER)));
	proc->IncrementPC(sizeof(AddressSize));
	proc->startJailedSubroutine(ptr.padding);
	return PROCEED;
} // Starts a jailed subroutine by jumping to the address given in the operand

constexpr auto Goto8 = &GotoCptr<uint8_t>;
constexpr auto Goto16 = &GotoCptr<uint16_t>;
constexpr auto Goto24 = &GotoCptr<bitfield24>;
constexpr auto Goto32 = &GotoCptr<uint32_t>;

constexpr auto Subr8 = &SubrCptr<uint8_t>;
constexpr auto Subr16 = &SubrCptr<uint16_t>;
constexpr auto Subr24 = &SubrCptr<bitfield24>;
constexpr auto Subr32 = &SubrCptr<uint32_t>;

constexpr auto JSubr8 = &JSubrCptr<uint8_t>;
constexpr auto JSubr16 = &JSubrCptr<uint16_t>;
constexpr auto JSubr24 = &JSubrCptr<bitfield24>;
constexpr auto JSubr32 = &JSubrCptr<uint32_t>;

// These are memory access instructions
template <typename DataSize> ProcessorState LoadConstIntoGeneral(pAbstractProcessor proc)
{
	pword8 regAddr;
	PaddedByteField<DataSize> data;
	regAddr.padding = 0;
	data.padding = 0;
	regAddr.org.org = *(proc->rawCastAccessMemoryAt<uint8_t>(proc->getAccessRegister(AbstractProcessor::PROGRAM_COUNTER)));
	proc->IncrementPC(sizeof(uint8_t));
	proc->setGeneralRegister(regAddr.org.org,0); // We first zero the register, to avoid pollution
	data.org.org = *(proc->rawCastAccessMemoryAt<DataSize>(proc->getAccessRegister(AbstractProcessor::PROGRAM_COUNTER)));
	proc->IncrementPC(sizeof(DataSize));
	proc->setGeneralRegister(regAddr.org.org,data.padding);
	return PROCEED;
} // Loads constant into the general register. Two operands: 1-byte int (register index), and the size of the new content.


template <typename DataSize> ProcessorState LoadConstIntoAddress(pAbstractProcessor proc)
{
	pword8 regAddr;
	PaddedByteField<DataSize> data;
	regAddr.padding = 0;
	data.padding = 0;
	regAddr.org.org = *(proc->rawCastAccessMemoryAt<uint8_t>(proc->getAccessRegister(AbstractProcessor::PROGRAM_COUNTER)));
	proc->IncrementPC(sizeof(uint8_t));
	proc->setAccessRegister(regAddr.org.org,0); // We first zero the register, to avoid pollution
	data.org.org = *(proc->rawCastAccessMemoryAt<DataSize>(proc->getAccessRegister(AbstractProcessor::PROGRAM_COUNTER)));
	proc->IncrementPC(sizeof(DataSize));
	proc->setAccessRegister(regAddr.org.org,data.padding);
	return PROCEED;
} // Loads constant into the address register. Two operands: 1-byte int (register index), and the size of the new content.

template <typename DataSize> ProcessorState LoadAddressPointerIntoGeneral(pAbstractProcessor proc)
{
	pword8n regAddr;
	PaddedByteField<DataSize> data;
	regAddr.padding = 0;
	data.padding = 0;
	regAddr.org.bytes[0] = *(proc->rawCastAccessMemoryAt<uint8_t>(proc->getAccessRegister(AbstractProcessor::PROGRAM_COUNTER)));
	proc->IncrementPC(sizeof(uint8_t));
	proc->setGeneralRegister(regAddr.org.org.lower,0); // We first zero the register, to avoid pollution
	data.org.org = *(proc->castAccessMemoryAt<DataSize>(proc->getAccessRegister(proc->getAccessRegister(regAddr.org.org.upper))));
	proc->setGeneralRegister(regAddr.org.org.lower,data.padding);
	return PROCEED;
} // Loads thing into the general register pointed to by the address register. The argument is a 1-byte integer, actually two nibbles

template <typename DataSize> ProcessorState LoadAddressPointerIntoAddress(pAbstractProcessor proc)
{
	pword8n regAddr;
	PaddedByteField<DataSize> data;
	regAddr.padding = 0;
	data.padding = 0;
	regAddr.org.bytes[0] = *(proc->rawCastAccessMemoryAt<uint8_t>(proc->getAccessRegister(AbstractProcessor::PROGRAM_COUNTER)));
	proc->IncrementPC(sizeof(uint8_t));
	proc->setAccessRegister(regAddr.org.org.lower,0); // We first zero the register, to avoid pollution
	data.org.org = *(proc->castAccessMemoryAt<DataSize>(proc->getAccessRegister(proc->getAccessRegister(regAddr.org.org.upper))));
	proc->setAccessRegister(regAddr.org.org.lower,data.padding);
	return PROCEED;
} // Loads thing into the address register pointed to by the address register. The argument is a 1-byte integer, actually two nibbles


template <typename DataSize, typename AddressSize> ProcessorState LoadPointerIntoGeneral(pAbstractProcessor proc)
{
	pword8 regAddr;
	PaddedByteField<AddressSize> ptr;
	PaddedByteField<DataSize> data;
	regAddr.padding = 0;
	ptr.padding = 0;
	data.padding = 0;
	regAddr.org.bytes[0] = *(proc->rawCastAccessMemoryAt<uint8_t>(proc->getAccessRegister(AbstractProcessor::PROGRAM_COUNTER)));
	proc->IncrementPC(sizeof(uint8_t));
	ptr.org.org = *(proc->rawCastAccessMemoryAt<AddressSize>(proc->getAccessRegister(AbstractProcessor::PROGRAM_COUNTER)));
	proc->IncrementPC(sizeof(AddressSize));
	proc->setGeneralRegister(regAddr.org.org,0); // We first zero the register, to avoid pollution
	data.org.org = *(proc->castAccessMemoryAt<DataSize>(ptr.padding));
	proc->setGeneralRegister(regAddr.org.org,data.padding);
	return PROCEED;
} // Loads data pointed to by the second operand into the general register indexed by the first operand (1-byte integer).

template <typename DataSize, typename AddressSize> ProcessorState LoadPointerIntoAddress(pAbstractProcessor proc)
{
	pword8 regAddr;
	PaddedByteField<AddressSize> ptr;
	PaddedByteField<DataSize> data;
	regAddr.padding = 0;
	ptr.padding = 0;
	data.padding = 0;
	regAddr.org.bytes[0] = *(proc->rawCastAccessMemoryAt<uint8_t>(proc->getAccessRegister(AbstractProcessor::PROGRAM_COUNTER)));
	proc->IncrementPC(sizeof(uint8_t));
	ptr.org.org = *(proc->rawCastAccessMemoryAt<AddressSize>(proc->getAccessRegister(AbstractProcessor::PROGRAM_COUNTER)));
	proc->IncrementPC(sizeof(AddressSize));
	proc->setAccessRegister(regAddr.org.org,0); // We first zero the register, to avoid pollution
	data.org.org = *(proc->castAccessMemoryAt<DataSize>(ptr.padding));
	proc->setAccessRegister(regAddr.org.org,data.padding);
	return PROCEED;
} // Loads data pointed to by the second operand into the address register indexed by the first operand (1-byte integer).

template <typename DataSize> ProcessorState SaveGRegisterIntoRegAddress(pAbstractProcessor proc)
{
	pword8n regAddr;
	size_t data;
	regAddr.padding = 0;
	data = 0;
	regAddr.org.bytes[0] = *(proc->rawCastAccessMemoryAt<uint8_t>(proc->getAccessRegister(AbstractProcessor::PROGRAM_COUNTER)));
	data = proc->getGeneralRegister(regAddr.org.org.lower);
	proc->IncrementPC(sizeof(uint8_t));
	memcpy(proc->accessMemoryAt(proc->getAccessRegister(regAddr.org.org.upper)),&data,sizeof(DataSize));
	return PROCEED;
} // ARguments are two nibbles stuffed into one 8-bit integer. Copies from indexed general register to address pointer by the indexed address register
template <typename DataSize, typename AddressSize> ProcessorState SaveGRegisterIntoPtrAddress(pAbstractProcessor proc)
{
	uint8_t regAddr;
	size_t data;
	PaddedByteField<AddressSize> ptr;
	ptr.padding = 0;
	data = 0;
	regAddr = *(proc->rawCastAccessMemoryAt<uint8_t>(proc->getAccessRegister(AbstractProcessor::PROGRAM_COUNTER)));
	proc->IncrementPC(sizeof(uint8_t));
	data = proc->getGeneralRegister(regAddr);
	ptr.org.org = *(proc->rawCastAccessMemoryAt<AddressSize>(proc->getAccessRegister(AbstractProcessor::PROGRAM_COUNTER)));
	proc->IncrementPC(sizeof(AddressSize));
	memcpy(proc->accessMemoryAt(ptr.padding),&data,sizeof(DataSize));
	return PROCEED;
} // Arguments are 8-bit register index and an address to where we store.

template <typename DataSize> ProcessorState SaveARegisterIntoRegAddress(pAbstractProcessor proc)
{
	pword8n regAddr;
	size_t data;
	regAddr.padding = 0;
	data = 0;
	regAddr.org.bytes[0] = *(proc->rawCastAccessMemoryAt<uint8_t>(proc->getAccessRegister(AbstractProcessor::PROGRAM_COUNTER)));
	data = proc->getAccessRegister(regAddr.org.org.lower);
	proc->IncrementPC(sizeof(uint8_t));
	memcpy(proc->accessMemoryAt(proc->getAccessRegister(regAddr.org.org.upper)),&data,sizeof(DataSize));
	return PROCEED;
} // ARguments are two nibbles stuffed into one 8-bit integer. Copies from indexed address register to address pointer by the indexed address register
template <typename DataSize, typename AddressSize> ProcessorState SaveARegisterIntoPtrAddress(pAbstractProcessor proc)
{
	uint8_t regAddr;
	size_t data;
	PaddedByteField<AddressSize> ptr;
	ptr.padding = 0;
	data = 0;
	regAddr = *(proc->rawCastAccessMemoryAt<uint8_t>(proc->getAccessRegister(AbstractProcessor::PROGRAM_COUNTER)));
	proc->IncrementPC(sizeof(uint8_t));
	data = proc->getAccessRegister(regAddr);
	ptr.org.org = *(proc->rawCastAccessMemoryAt<AddressSize>(proc->getAccessRegister(AbstractProcessor::PROGRAM_COUNTER)));
	proc->IncrementPC(sizeof(AddressSize));
	memcpy(proc->accessMemoryAt(ptr.padding),&data,sizeof(DataSize));
	return PROCEED;
} // Arguments are 8-bit register index and an address to where we store.

constexpr auto GLoadConstWord8 = &LoadConstIntoGeneral<uint8_t>;
constexpr auto GLoadConstWord16 = &LoadConstIntoGeneral<uint16_t>;
constexpr auto GLoadConstWord32 = &LoadConstIntoGeneral<uint32_t>;

constexpr auto ALoadConstWord8 = &LoadConstIntoAddress<uint8_t>;
constexpr auto ALoadConstWord16 = &LoadConstIntoAddress<uint16_t>;
constexpr auto ALoadConstWord24 = &LoadConstIntoAddress<bitfield24>;
constexpr auto ALoadConstWord32 = &LoadConstIntoAddress<uint32_t>;

constexpr auto GLoadRpointerWord8 = &LoadAddressPointerIntoGeneral<uint8_t>;
constexpr auto GLoadRpointerWord16 = &LoadAddressPointerIntoGeneral<uint16_t>;
constexpr auto GLoadRpointerWord32 = &LoadAddressPointerIntoGeneral<uint32_t>;

constexpr auto ALoadRpointerWord8 = &LoadAddressPointerIntoAddress<uint8_t>;
constexpr auto ALoadRpointerWord16 = &LoadAddressPointerIntoAddress<uint16_t>;
constexpr auto ALoadRpointerWord24 = &LoadAddressPointerIntoAddress<bitfield24>;
constexpr auto ALoadRpointerWord32 = &LoadAddressPointerIntoAddress<uint32_t>;

constexpr auto GLoadPtr8by8 = &LoadPointerIntoGeneral<uint8_t,uint8_t>;
constexpr auto GLoadPtr8by16 = &LoadPointerIntoGeneral<uint8_t,uint16_t>;
constexpr auto GLoadPtr8by24 = &LoadPointerIntoGeneral<uint8_t,bitfield24>;
constexpr auto GLoadPtr8by32 = &LoadPointerIntoGeneral<uint8_t,uint32_t>;
constexpr auto GLoadPtr16by16 = &LoadPointerIntoGeneral<uint16_t,uint16_t>;
constexpr auto GLoadPtr16by24 = &LoadPointerIntoGeneral<uint16_t,bitfield24>;
constexpr auto GLoadPtr16by32 = &LoadPointerIntoGeneral<uint16_t,uint32_t>;
constexpr auto GLoadPtr32by32 = &LoadPointerIntoGeneral<uint32_t,uint32_t>;

constexpr auto ALoadPtr8by8 = &LoadPointerIntoAddress<uint8_t,uint8_t>;
constexpr auto ALoadPtr16by16 = &LoadPointerIntoAddress<uint16_t,uint16_t>;
constexpr auto ALoadPtr24by24 = &LoadPointerIntoAddress<bitfield24,bitfield24>;
constexpr auto ALoadPtr32by32 = &LoadPointerIntoAddress<uint32_t,uint32_t>;

constexpr auto RSaveGWord8 = &SaveGRegisterIntoRegAddress<uint8_t>;
constexpr auto RSaveGWord16 = &SaveGRegisterIntoRegAddress<uint16_t>;
constexpr auto RSaveGWord32 = &SaveGRegisterIntoRegAddress<uint32_t>;

constexpr auto RSaveAWord8 = &SaveARegisterIntoRegAddress<uint8_t>;
constexpr auto RSaveAWord16 = &SaveARegisterIntoRegAddress<uint16_t>;
constexpr auto RSaveAWord24 = &SaveARegisterIntoRegAddress<bitfield24>;
constexpr auto RSaveAWord32 = &SaveARegisterIntoRegAddress<uint32_t>;

constexpr auto PSaveWord8by8 = &SaveGRegisterIntoPtrAddress<uint8_t,uint8_t>;
constexpr auto PSaveWord8by16 = &SaveGRegisterIntoPtrAddress<uint8_t,uint16_t>;
constexpr auto PSaveWord8by24 = &SaveGRegisterIntoPtrAddress<uint8_t,bitfield24>;
constexpr auto PSaveWord8by32 = &SaveGRegisterIntoPtrAddress<uint8_t,uint32_t>;
constexpr auto PSaveWord16by16 = &SaveGRegisterIntoPtrAddress<uint16_t,uint16_t>;
constexpr auto PSaveWord16by24 = &SaveGRegisterIntoPtrAddress<uint16_t,bitfield24>;
constexpr auto PSaveWord16by32 = &SaveGRegisterIntoPtrAddress<uint16_t,uint32_t>;
constexpr auto PSaveWord32by32 = &SaveGRegisterIntoPtrAddress<uint32_t,uint32_t>;

constexpr auto ASavePtr8by8 = &SaveARegisterIntoPtrAddress<uint8_t,uint8_t>;
constexpr auto ASavePtr16by16 = &SaveARegisterIntoPtrAddress<uint16_t,uint16_t>;
constexpr auto ASavePtr24by24 = &SaveARegisterIntoPtrAddress<bitfield24,bitfield24>;
constexpr auto ASavePtr32by32 = &SaveARegisterIntoPtrAddress<uint32_t,uint32_t>;

}
