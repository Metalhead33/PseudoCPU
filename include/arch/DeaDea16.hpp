#ifndef DEADEA16_HPP
#define DEADEA16_HPP
#include "abstract/AbstractProcessor.hpp"
#include <cstdint>

namespace Arch {
DEFINE_CLASS(DeaDea16)

class DeaDea16 : public Psecom::AbstractProcessorArchitecture<uint8_t,uint16_t>
{
private:
	static sDeaDea16 __instance;
	//static pDeaDea16 __instance;
public:
	DeaDea16(); // Please don't ever use it. It is only kept there to ensure that the class can be inherited.
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
		_GOTO,

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
		_STORAR16,
		_MEMCPY,

		// Arithmetical and bitwise operations
		_ADD,
		_NEG,
		_MUL,
		_DIV,
		_MOD,
		_LBW,
		_RBW,
		_BXOR,
		_BIOR,
		_BAND,
		_BNOT,

		// Logical instructions
		_EQUAL,
		_NEQUAL,
		_LESSER,
		_GREATER,
		_ELESSER,
		_EGREATER,
		_LNOT,
		_LOR,
		_LAND,

		// Control flow
		_IF,
		_IFN,
		_FUNC,
		_MFUNC,

		// Misc
		_MEMS,
		_SPEED,
		_SPEEDG,
		_WAIT,
		_WAITI,
		_WAITS
	};

	// HERE COME ALL THE FUNCTIONS
	// Basic functions
	static Psecom::Pstate inNOPE(RegisterStorage str); // Null instruction, does absolutely nothing. No operands.
	static Psecom::Pstate inEXIT(RegisterStorage str); // Exity. No operands.
	static Psecom::Pstate inPANIC(RegisterStorage str); // Exits violently. No operands.
	static Psecom::Pstate inRET(RegisterStorage str); // Returns to the previous state, keeping registers. No operands.
	static Psecom::Pstate inRES(RegisterStorage str); // Returns to the previous state, without. No operands.
	static Psecom::Pstate inGOTO(RegisterStorage str); // Goto. Takes a single 2-byte operand (pointer).

	// Memory and register instructions

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
	static Psecom::Pstate inMEMCPY(RegisterStorage str); // Copies from one place to another. Takes 3 16-bit operands (all pointers): origin, destination, size

	// Arithmetical and bitwise instructions
	static Psecom::Pstate inADD(RegisterStorage str); // Addition. No operands.
	static Psecom::Pstate inNEG(RegisterStorage str); // Negation. No operands.
	static Psecom::Pstate inMUL(RegisterStorage str); // Multiplication. No operands.
	static Psecom::Pstate inDIV(RegisterStorage str); // Division. No operands.
	static Psecom::Pstate inMOD(RegisterStorage str); // Modulo. No operands.
	static Psecom::Pstate inLBW(RegisterStorage str); // Leftwards bitwise shift. No operands.
	static Psecom::Pstate inRBW(RegisterStorage str); // Rightwards bitwise shift. No operands.
	static Psecom::Pstate inBXOR(RegisterStorage str); // Bitwise XOR. No operands.
	static Psecom::Pstate inBIOR(RegisterStorage str); // Bitwise inclusive OR. No operands.
	static Psecom::Pstate inBAND(RegisterStorage str); // Bitwise AND. No operands.
	static Psecom::Pstate inBNOT(RegisterStorage str); // Bitwise NOT. No operands.
	//static Psecom::Pstate inCEBIT(RegisterStorage str); // Checks bit. No operands.
	//static Psecom::Pstate inCABIT(RegisterStorage str); // Changes bit. No operands.

	// Logical instructions (mostly comparing the Accumulator to the Argument: Accumulator < Argument, for example)
	static Psecom::Pstate inEQUAL(RegisterStorage str); // Equal. No operands.
	static Psecom::Pstate inNEQUAL(RegisterStorage str); // Not equal. No operands.
	static Psecom::Pstate inLESSER(RegisterStorage str); // Lesser. No operands.
	static Psecom::Pstate inGREATER(RegisterStorage str); // Greater. No operands.
	static Psecom::Pstate inELESSER(RegisterStorage str); // Lesser or equal. No operands.
	static Psecom::Pstate inEGREATER(RegisterStorage str); // Greater or equal. No operands.
	static Psecom::Pstate inLNOT(RegisterStorage str); // Logical NOT. No operands.
	static Psecom::Pstate inLOR(RegisterStorage str); // Logical OR. No operands.
	static Psecom::Pstate inLAND(RegisterStorage str); // Logical AND. No operands.

	// Control flow
	static Psecom::Pstate inIF(RegisterStorage str); // If. Checks accumulator. Jumps to operand (16-bit pointer) if true.
	static Psecom::Pstate inIFN(RegisterStorage str); // If not. Checks accumulator. Jumps to operand (16-bit pointer) if false.
	static Psecom::Pstate inFUNC(RegisterStorage str); // Starts a new state. Takes one 16-bit operand (pointer). Gives global access.
	static Psecom::Pstate inMFUNC(RegisterStorage str); // Starts a new state. Takes one 16-bit operand (pointer). Sets memstart to the place where access it, effectively allowing only local access.

	// Misc
	static Psecom::Pstate inMEMS(RegisterStorage str); // Takes memory size into the accumulator register. No operands.
	static Psecom::Pstate inSPEED(RegisterStorage str); // Changes the speed by altering the number of microseconds that we have to wait between each instruction to take place. No operand - it takes from the argument register.
	static Psecom::Pstate inSPEEDG(RegisterStorage str); // Takes the "speed" (amount of time that we have to wait between instructions) onto the accumulator register.
	static Psecom::Pstate inWAIT(RegisterStorage str); // Waits [argument register] microseconds.
	static Psecom::Pstate inWAITI(RegisterStorage str); // Waits [argument register] miliseconds.
	static Psecom::Pstate inWAITS(RegisterStorage str); // Waits [argument register] seconds.

};
}

#endif // DEADEA16_HPP
