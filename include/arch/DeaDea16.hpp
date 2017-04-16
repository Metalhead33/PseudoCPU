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
		_LAND
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



};
}

#endif // DEADEA16_HPP
