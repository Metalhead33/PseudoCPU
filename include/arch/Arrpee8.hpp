#ifndef ARRPEE8_HPP
#define ARRPEE8_HPP
#include "include/abstract/InstructionSet.hpp"

class Arrpee8 : public InstructionSet<uint8_t,uint16_t,uint16_t>
{
private:
	Arrpee8();
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
		BSL, // 134 - Leftward bitwise shift
		BSR, // 135 - Rightward bitwise shift
		LAND, // 136 - Logical AND
		BAND, // 137 - Bitwise AND
		LIOR, // 138 - Logical Inclusive OR
		BIOR, // 139 - Bitwise Inclusive OR
		LXOR, // 140 - Logical Exclusive OR
		BXOR, // 141 - Bitwise Exclusive OR

		// Loading and storing data
		SHFA, // 142 - Shuffle the content of the Accumulator Register and Argument Register

		// Loading directly
		LDACD8, // 143 - loads the argument (an 8-bit integer) into the Accumulator Register
		LDARD8, // 144 - loads the argument (an 8-bit integer) into the Argument Register
		LDACD16, // 145 - loads the argument (a 16-bit integer) into the Accumulator Register
		LDARD16, // 146 - loads the argument (a 16-bit integer) into the Argument Register
		LDSPD16, // 147 - loads the argument (a 16-bit integer) as the Stack Pointer
		LDSMD16, // 148 - loads the argument (a 16-bit integer) as the Maximum Size of Stack
		LDSCD16, // 148 - loads the argument (a 16-bit integer) as the current stack size. Not recommended.

		// Loading from memory
		LDACP8_16, // 149 - loads a 8-bit integer into the Accumulator Register from a 16-bit pointer
		LDARP8_16, // 150 - loads an 8-bit integer into the Argument Register from a 16-bit pointer
		LDACP16_16, // 151 - loads a 16-bit integer into the Accumulator Register from a 16-bit pointer
		LDARP16_16, // 152 - loads a 16-bit integer into the Argument Register from a 16-bit pointer
		LDSPP16_16, // 153 - loads a 16-bit integer as the Stack Pointer from a 16-bit pointer
		LDSMP16_16, // 154 - loads a 16-bit integer as the Maximum Size of Stack from a 16-bit pointer
		LDSCP16_16, // 155 - loads a 16-bit integer as the current stack size from a 16-bit pointer

		// Storing into memory
		STAC8_16, // 149 - saves a 8-bit integer from the Accumulator Register into the pointed location
		STAR8_16, // 150 - saves an 8-bit integer from the Argument Register into the pointed location
		STAC16_16, // 151 - saves a 16-bit integer from the Accumulator Register into the pointed location
		STAR16_16, // 152 - saves a 16-bit integer from the Argument Register into the pointed location
		STSP16_16, // 153 - saves a 16-bit integer from the Stack Pointer into the pointed location
		STSM16_16, // 154 - saves a 16-bit integer from the Maximum Size of Stack into the pointed location
		STSC16_16, // 155 - saves a 16-bit integer as the current stack size into the pointed location
	};
public:
};

#endif // ARRPEE8_HPP
