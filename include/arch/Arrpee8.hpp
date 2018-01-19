#pragma once
#include "include/abstract/AbstractArchitecture.hpp"

class Arrpee8 : public AbstractArchitecture
{
private:
	Arrpee8();
	static sAbstractArchitecture singleton;
public:
	static void RegisterArrpe8(pAbstractArchitecture arch);
	static sAbstractArchitecture getSingleton();

	enum INST_SET_RP8 : uint8_t
	{
		// Really the basics
		NOPE = 0, // No instruction
		RET, // Return
		FRZ, // Freeze
		OFF, // Power off
		ERR, // Error / Panic
		// Arithmetics
		ADD, // Addition
		SUB, // Subtraction
		MUL, // Multiplication
		DIV, // Division
		MOD, // Modulo
		// Logic
		LNOT, // Logical NOT
		LAND, // Logical AND
		LIOR, // Logical OR
		LXOR, // Logical XOR
		// Bitwise
		BNOT, // Bitwise NOT
		BAND, // Bitwise AND
		BIOR, // Bitwise OR
		BXOR, // Bitwise XOR
		BLSH, // Bitwise Left Shift
		BRSH, // Bitwise Right Shift
		// Moving registers from one to another
		GMOV, // General register move
		GSHF, // General register shuffle
		AMOV, // Address register move
		ASHF, // Address register shuffle
		// GOTO
		RGOTO, // Register goto
		RSUBR, // Register subroutine
		RJSUBR, // Register jailed subroutine
		RCGOTO, // Conditional Register goto
		RCSUBR, // Conditional Register subroutine
		RCJSUBR, // Conditional Register jailed subroutine
		// 8-bit memory address
		P8GOTO, // 8-bit pointer GOTO
		P8SUBR, // 8-bit pointer subroutine
		P8JSUBR, // 8-bit pointer jailed subroutine
		LCG8, // Load 8-bit constant into general register (operand)
		LCA8, // Load 8-bit constant into address register (operand)
		LR8G, // Loads 8-bit integer to general register from position pointed to by regjster
		LR8A, // Loads 8-bit integer to address register from position pointed to by regjster
		LP8G8, // Load 8-bit integer into general register from 8-bit pointer operand
		LP8A8, // Load 8-bit integer into address register from 8-bit pointer operand
		SP8G8, // Stores 8-bit integer from general register into 8-bit pointer operand
		SP8A8, // Storess 8-bit integer from address register into 8-bit pointer operand
		SR8G, // Stores 8-bit integer from general register into position pointed to by regjster
		SR8A, // Stores 8-bit integer from address register into position pointed to by regjster

		PAD
	};

};
