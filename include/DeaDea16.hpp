#ifndef DEADEA16_HPP
#define DEADEA16_HPP
#include "AbstractProcessor.hpp"

class DeaDea16 : public AbstractProcessor<uint8_t,uint16_t>
{
public:
	//DeaDea16();
	DeaDea16(uint16_t memsize);
	DeaDea16(uint8_t* extmem, uint16_t memsize);
	DeaDea16(SharedMemory shared_mem, uint16_t memsize);
	DeaDea16(AbstractFread* fileread);

	void RegisterFunctions();
	enum InstructionList : uint8_t
	{
		_EXIT = 128,
		_PANIC = _EXIT+1,
		// 8-bit Memory Access Instructions
		_LoadAAC8 = _PANIC+1, // Loads into the Accumulator Register - Absolute
		_LoadAAR8 = _LoadAAC8+1, // Loads into the Argument Register - Absolute
		_LoadPAC8 = _LoadAAR8+1, // Loads into the Accumulator Register - Pointer
		_LoadPAR8 = _LoadPAC8+1, // Loads into the Argument Register - Pointer
		_StoreAC8 = _LoadPAR8+1, // Stores into the memory from the Accumulator Register
		_StoreAR8 = _StoreAC8+1, // Stores into the memory from the Argument Register

		// 16-bit Memory Access Instructions
		_Switch = _StoreAR8+1, // Switches up the Accumulator Register and Argument Register
		_LoadAAC16 = _Switch+1, // Loads into the Accumulator Register - Absolute
		_LoadAAR16 = _LoadAAC16+1, // Loads into the Argument Register - Absolute
		_LoadPAC16 = _LoadAAR16+1, // Loads into the Accumulator Register - Pointer
		_LoadPAR16 = _LoadPAC16+1, // Loads into the Argument Register - Pointer
		_StoreAC16 = _LoadPAR16+1, // Stores into the memory from the Accumulator Register
		_StoreAR16 = _StoreAC16+1, // Stores into the memory from the Argument Register

		// Arithmetical and logical instructions
		_ADD = _StoreAR16+1, // Adds the content of registers. (0 operands)
		_SUB = _ADD+1, // Subtracts the content of registers. (0 operands)
		_MUL = _SUB+1, // Multiplies the content of registers. (0 operands)
		_DIV = _MUL+1, // Divides the content of registers. (0 operands)
		_MOD = _DIV+1, // Moduloes the content of registers. (0 operands)
		_LAND = _MOD+1, // Logical AND (0 operands)
		_BAND = _LAND+1, // Bitwise AND (0 operands)
		_LOR = _BAND+1, // Logical Inclusive OR (0 operands)
		_BOR = _LOR+1, // Bitwise Inclusive OR (0 operands)
		_BXOR = _BOR+1, // Bitwise Exclusive OR (0 operands)
		_LNOT = _BXOR+1, // Logical NOT (0 operands)
		_BNOT = _LNOT+1, // Bitwise NOT (0 operands)
		_BLSH = _BNOT+1, // Bitwise left shift of the accumulator by the argument (0 operands)
		_BRSH = _BLSH+1, // Bitwise right shift of the accumulator by the argument (0 operands)

		//Control flow
		_GOTO = _BRSH+1,
		_IF = _GOTO+1,
		_IFN = _IF+1
	};

	// Base Instructions
	static Pstate InEXIT(RegisterStorage str) { return STOP; } // Self-evident. Stops the machine. (0 operands)
	static Pstate InPANIC(RegisterStorage str) { return PANIC; } // Self-evident. Force-exits the machine. (0 operands)

	// 8-bit Memory Access Instructions
	static Pstate LoadAAC8(RegisterStorage str); // Loads into the Accumulator Register - Absolute (1 operand, 8-bit)
	static Pstate LoadAAR8(RegisterStorage str); // Loads into the Argument Register - Absolute (1 operand, 8-bit)
	static Pstate LoadPAC8(RegisterStorage str); // Loads into the Accumulator Register - Pointer (1 operand, 16-bit)
	static Pstate LoadPAR8(RegisterStorage str); // Loads into the Argument Register - Pointer (1 operand, 16-bit)
	static Pstate StoreAC8(RegisterStorage str); // Stores into the memory from the Accumulator Register (1 operand, 16-bit)
	static Pstate StoreAR8(RegisterStorage str); // Stores into the memory from the Argument Register (1 operand, 16-bit)

	// 16-bit Memory Access Instructions
	static Pstate Switch(RegisterStorage str); // Switches up the Accumulator Register and Argument Register (0 operands)
	static Pstate LoadAAC16(RegisterStorage str); // Loads into the Accumulator Register - Absolute (1 operand, 16-bit)
	static Pstate LoadAAR16(RegisterStorage str); // Loads into the Argument Register - Absolute (1 operand, 16-bit)
	static Pstate LoadPAC16(RegisterStorage str); // Loads into the Accumulator Register - Pointer (1 operand, 16-bit)
	static Pstate LoadPAR16(RegisterStorage str); // Loads into the Argument Register - Pointer (1 operand, 16-bit)
	static Pstate StoreAC16(RegisterStorage str); // Stores into the memory from the Accumulator Register (1 operand, 16-bit)
	static Pstate StoreAR16(RegisterStorage str); // Stores into the memory from the Argument Register (1 operand, 16-bit)

	// Arithmetical and logical instructions
	static Pstate ADD(RegisterStorage str); // Adds the content of registers. (0 operands)
	static Pstate SUB(RegisterStorage str); // Subtracts the content of registers. (0 operands)
	static Pstate MUL(RegisterStorage str); // Multiplies the content of registers. (0 operands)
	static Pstate DIV(RegisterStorage str); // Divides the content of registers. (0 operands)
	static Pstate MOD(RegisterStorage str); // Moduloes the content of registers. (0 operands)
	static Pstate LAND(RegisterStorage str); // Logical AND (0 operands)
	static Pstate BAND(RegisterStorage str); // Bitwise AND (0 operands)
	static Pstate LOR(RegisterStorage str); // Logical Inclusive OR (0 operands)
	static Pstate BOR(RegisterStorage str); // Bitwise Inclusive OR (0 operands)
	static Pstate BXOR(RegisterStorage str); // Bitwise Exclusive OR (0 operands)
	static Pstate LNOT(RegisterStorage str); // Logical NOT (0 operands)
	static Pstate BNOT(RegisterStorage str); // Bitwise NOT (0 operands)
	static Pstate BLSH(RegisterStorage str); // Bitwise left shift of the accumulator by the argument (0 operands)
	static Pstate BRSH(RegisterStorage str); // Bitwise right shift of the accumulator by the argument (0 operands)

	// Control flow
	static Pstate GOTO(RegisterStorage str); // Go to location pointed by the operand (1 operand, 16-bit)
	static Pstate IF(RegisterStorage str); // Go to the location of the operand, if the ACCR is over 0 (1 operand, 16-bit)
	static Pstate IFN(RegisterStorage str); // Go to the location of the operand, if the ACCR is 0 (1 operand, 16-bit)
};

#endif // DEADEA16_HPP
