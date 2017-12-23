#ifndef ARRPEE8_HPP
#define ARRPEE8_HPP
#include "include/abstract/InstructionSet.hpp"

class Arrpee8 : public InstructionSet<uint8_t,uint16_t,uint16_t>
{
private:
	static sInstructionSet singleton;
	Arrpee8();
public:
	enum OPCODES : uint8_t
	{
		// Very basic control - none of these have an argument
		NOP = 128, // 128 - No instruction, used for padding mostly
		POFF, // 129 - Power off

		// Arithmetic and logic - none have arguments, all operate on the registers
		ADD, // 130 - Add
		NEG, // 131 - Negate
		MUL, // 132 - Multiply
		DIV, // 133 - Divide
		MOD, // 134 - Modulo
		BSL, // 135 - Leftward bitwise shift
		BSR, // 136 - Rightward bitwise shift
		LAND, // 137 - Logical AND
		BAND, // 138 - Bitwise AND
		LIOR, // 139 - Logical Inclusive OR
		BIOR, // 140 - Bitwise Inclusive OR
		LXOR, // 141 - Logical Exclusive OR
		BXOR, // 142 - Bitwise Exclusive OR
		LNOT, // 143 - Logic NOT
		BNOT, // 144 - Bitwise NOT

		// Loading and storing data
		SHFA, // 145 - Shuffle the content of the Accumulator Register and Argument Register

		// Loading directly - all take one argument, which is the size of the loaded data
		LDACD8, // 146 - loads the argument (an 8-bit integer) into the Accumulator Register
		LDARD8, // 147 - loads the argument (an 8-bit integer) into the Argument Register
		LDACD16, // 148 - loads the argument (a 16-bit integer) into the Accumulator Register
		LDARD16, // 149 - loads the argument (a 16-bit integer) into the Argument Register
		LDSPD16, // 150 - loads the argument (a 16-bit integer) as the Stack Pointer
		LDSMD16, // 151 - loads the argument (a 16-bit integer) as the Maximum Size of Stack
		LDSCD16, // 152 - loads the argument (a 16-bit integer) as the current stack size. Not recommended.

		// Loading from memory - all take a single 16-bit integer as an argument, which is actually a pointer
		LDACP8_16, // 153 - loads a 8-bit integer into the Accumulator Register from a 16-bit pointer
		LDARP8_16, // 154 - loads an 8-bit integer into the Argument Register from a 16-bit pointer
		LDACP16_16, // 155 - loads a 16-bit integer into the Accumulator Register from a 16-bit pointer
		LDARP16_16, // 156 - loads a 16-bit integer into the Argument Register from a 16-bit pointer
		LDSPP16_16, // 157 - loads a 16-bit integer as the Stack Pointer from a 16-bit pointer
		LDSMP16_16, // 158 - loads a 16-bit integer as the Maximum Size of Stack from a 16-bit pointer
		LDSCP16_16, // 159 - loads a 16-bit integer as the current stack size from a 16-bit pointer

		// Storing into memory - all take a 16-bit integer as an argument, which is actually a pointer
		STAC8_16, // 160 - saves a 8-bit integer from the Accumulator Register into the pointed location
		STAR8_16, // 161 - saves an 8-bit integer from the Argument Register into the pointed location
		STAC16_16, // 162 - saves a 16-bit integer from the Accumulator Register into the pointed location
		STAR16_16, // 163 - saves a 16-bit integer from the Argument Register into the pointed location
		STSP16_16, // 164 - saves a 16-bit integer from the Stack Pointer into the pointed location
		STSM16_16, // 165 - saves a 16-bit integer from the Maximum Size of Stack into the pointed location
		STSC16_16, // 166 - saves a 16-bit integer as the current stack size into the pointed location

		// Other memory stuff
		MEMCPY16, // 167 - yep, exactly what the name says. Memcpy. Takes three 16-bit integers as arguments.

		// If-stuff
		IFEQ, // 168 - If Accumulator Register and Argument register are equals.
		IFGR, // 169 - If Accumulator Register is Greater Than Argument Register
		IFGE, // 170 - If Accumulator Register is Greater Or Equal Than Argument Register
		ILGR, // 171 - If Accumulator Register is Lesser Than Argument Register
		ILGE, // 172 - If Accumulator Register is Lesser Or Equal Than Argument Register
		IFB, // 173 - If bit of the accumulator register is 1...
		STB, // 174 - Set bit of the accumulator register to 1.

		// Controlf-low
		GOTO_16, // 175 - Jumps to somewhere (given in 16-bit argument)
		IFJM_16, // 176 - Jumps if Accumulator Register is non-zero, the argument is where to jump. Adds previous location to the stack.
		SUBR_16, // 177 - Jumps to a location unconditionally, and adds previous location to the stack.
		RETURN, // 178 - Returns to the last stack.
		PAD // 179 - padding used for size, not a real instruction
	};
	// Very basic control - none of these have an argument
	static ComputerState __NOP(StatePointer STATE);
	static ComputerState __POFF(StatePointer STATE);

	// Arithmetic and logic - none have arguments, all operate on the registers
	static ComputerState __ADD(StatePointer STATE);
	static ComputerState __NEG(StatePointer STATE);
	static ComputerState __MUL(StatePointer STATE);
	static ComputerState __DIV(StatePointer STATE);
	static ComputerState __MOD(StatePointer STATE);
	static ComputerState __BSL(StatePointer STATE);
	static ComputerState __BSR(StatePointer STATE);
	static ComputerState __LAND(StatePointer STATE);
	static ComputerState __BAND(StatePointer STATE);
	static ComputerState __LIOR(StatePointer STATE);
	static ComputerState __BIOR(StatePointer STATE);
	static ComputerState __LXOR(StatePointer STATE);
	static ComputerState __BXOR(StatePointer STATE);
	static ComputerState __LNOT(StatePointer STATE);
	static ComputerState __BNOT(StatePointer STATE);

	// Loading and storing data
	static ComputerState __SHFA(StatePointer STATE);

	// Loading directly - all take one argument, which is the size of the loaded data
	static ComputerState __LDACD8(StatePointer STATE);
	static ComputerState __LDARD8(StatePointer STATE);
	static ComputerState __LDACD16(StatePointer STATE);
	static ComputerState __LDARD16(StatePointer STATE);
	static ComputerState __LDSPD16(StatePointer STATE);
	static ComputerState __LDSMD16(StatePointer STATE);
	static ComputerState __LDSCD16(StatePointer STATE);

	// Loading from memory - all take a single 16-bit integer as an argument, which is actually a pointer
	static ComputerState __LDACP8_16(StatePointer STATE);
	static ComputerState __LDARP8_16(StatePointer STATE);
	static ComputerState __LDACP16_16(StatePointer STATE);
	static ComputerState __LDARP16_16(StatePointer STATE);
	static ComputerState __LDSPP16_16(StatePointer STATE);
	static ComputerState __LDSMP16_16(StatePointer STATE);
	static ComputerState __LDSCP16_16(StatePointer STATE);

	// Storing into memory - all take a 16-bit integer as an argument, which is actually a pointer
	static ComputerState __STAC8_16(StatePointer STATE);
	static ComputerState __STAR8_16(StatePointer STATE);
	static ComputerState __STAC16_16(StatePointer STATE);
	static ComputerState __STAR16_16(StatePointer STATE);
	static ComputerState __STSP16_16(StatePointer STATE);
	static ComputerState __STSM16_16(StatePointer STATE);
	static ComputerState __STSC16_16(StatePointer STATE);

	// Other memory stuff
	static ComputerState __MEMCPY16(StatePointer STATE);

	// If-stuff
	static ComputerState __IFEQ(StatePointer STATE);
	static ComputerState __IFGR(StatePointer STATE);
	static ComputerState __IFGE(StatePointer STATE);
	static ComputerState __ILGR(StatePointer STATE);
	static ComputerState __ILGE(StatePointer STATE);
	static ComputerState __IFB(StatePointer STATE);
	static ComputerState __STB(StatePointer STATE);

	// Controlf-low
	static ComputerState __GOTO_16(StatePointer STATE);
	static ComputerState __IFJM_16(StatePointer STATE);
	static ComputerState __SUBR_16(StatePointer STATE);
	static ComputerState __RETURN(StatePointer STATE);

	// Get the singleton
	static sInstructionSet getSingleton();
};

#endif // ARRPEE8_HPP
