#ifndef DEADEA16_HPP
#define DEADEA16_HPP
#include "abstract/AbstractProcessor.hpp"
#include <cstdint>

namespace Arch {
DEFINE_CLASS(DeaDea16)

class DeaDea16 : public Psecom::AbstractProcessorArchitecture<uint8_t,uint16_t>
{
private:
	DeaDea16();
	static sDeaDea16 __instance;
	//static pDeaDea16 __instance;
public:
	static sDeaDea16 instance();
	//static pDeaDea16 instance();
	typedef Psecom::AbstractProcessorArchitecture<uint8_t,uint16_t> AbstractCpuType;
	typedef std::shared_ptr<AbstractCpuType> SharedCpuType;
	typedef Psecom::AbstractProcessor<uint8_t,uint16_t> ProccessorType;
	static SharedCpuType CastToAbstract();

	enum InstructionSet : uint8_t
	{
		// Basic functions
		_NOPE = 0x80,
		_EXIT,
		_PANIC,
		_RET,
		_RES,

		// Memory and register
		_SWITCH,
		_LOADACA8,
		_LOADARA8,
		_LOADACP8,
		_LOADARP8,
		_LOADACA16,
		_LOADARA16,
		_LOADACP16,
		_LOADARP16,
		_STORAC8,
		_STORAR8,
		_STORAC16,
		_STORAR16
	};

	// HERE COME ALL THE FUNCTIONS
	// Basic functions
	static Psecom::Pstate inNOPE(RegisterStorage str); // Null instruction, does absolutely nothing. No operands.
	static Psecom::Pstate inEXIT(RegisterStorage str); // Exity. No operands.
	static Psecom::Pstate inPANIC(RegisterStorage str); // Exits violently. No operands.
	static Psecom::Pstate inRET(RegisterStorage str); // Returns to the previous state, keeping registers. No operands.
	static Psecom::Pstate inRES(RegisterStorage str); // Returns to the previous state, without. No operands.

	// Memory and register functions

	static Psecom::Pstate inSWITCH(RegisterStorage str); // Switches up the content of the two registers. No operands
	static Psecom::Pstate inLOADACA8(RegisterStorage str); // Loads 8-bit number into the accumulator register. A single 1-byte operand.
	static Psecom::Pstate inLOADARA8(RegisterStorage str); // Loads 8-bit number into the argument register. A single 1-byte operand.
	static Psecom::Pstate inLOADACP8(RegisterStorage str); // Loads 8-bit number into the accumulator register. A single 2-byte operand (pointer).
	static Psecom::Pstate inLOADARP8(RegisterStorage str); // Loads 8-bit number into the argument register. A single 2-byte operand (pointer).
	static Psecom::Pstate inLOADACA16(RegisterStorage str); // Loads 16-bit number into the accumulator register. A single 2-byte operand.
	static Psecom::Pstate inLOADARA16(RegisterStorage str); // Loads 16-bit number into the argument register. A single 2-byte operand.
	static Psecom::Pstate inLOADACP16(RegisterStorage str); // Loads 16-bit number into the accumulator register. A single 2-byte operand (pointer).
	static Psecom::Pstate inLOADARP16(RegisterStorage str); // Loads 16-bit number into the argument register. A single 2-byte operand (pointer).
	static Psecom::Pstate inSTORAC8(RegisterStorage str); // Copies 8-bit number from accumulator register to said memory block. A single 2-byte operand (pointer).
	static Psecom::Pstate inSTORAR8(RegisterStorage str); // Copies 8-bit number from argument register to said memory block. A single 2-byte operand (pointer).
	static Psecom::Pstate inSTORAC16(RegisterStorage str); // Copies 16-bit number from accumulator register to said memory block. A single 2-byte operand (pointer).
	static Psecom::Pstate inSTORAR16(RegisterStorage str); // Copies 16-bit number from argument register to said memory block. A single 2-byte operand (pointer).
};
}

#endif // DEADEA16_HPP
