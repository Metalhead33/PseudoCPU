#pragma once
#include "include/arch/Arrpee16plus.hpp"
class Arrpee32 : public AbstractArchitecture
{
private:
	Arrpee32();
	static sAbstractArchitecture singleton;
public:
	static void RegisterArrpee32(pAbstractArchitecture arch);
	static sAbstractArchitecture getSingleton();
	enum INST_SET_RP32 : uint8_t
	{
		// 32-bit memory address
		P32GOTO = Arrpee16plus::PAD, // 32-bit pointer GOTO
		P32SUBR, // 32-bit pointer subroutine
		P32JSUBR, // 32-bit pointer jailed subroutine
		LCG32, // Load 32-bit constant into general register (operand)
		LCA32, // Load 32-bit constant into address register (operand)
		LR32G, // Loads 32-bit integer to general register from position pointed to by regjster
		LR32A, // Loads 32-bit integer to address register from position pointed to by regjster
		LP32G8, // Load 8-bit integer into general register from 32-bit pointer operand
		LP32G16, // Load 16-bit integer into general register from 32-bit pointer operand
		LP32G32, // Load 32-bit integer into general register from 32-bit pointer operand
		LP32A32, // Load 32-bit integer into address register from 32-bit pointer operand
		SP32G8, // Stores 8-bit integer from general register into 8-bit pointer operand
		SP32G16, // Stores 16-bit integer from general register into 32-bit pointer operand
		SP32G32, // Stores 32-bit integer from general register into 32-bit pointer operand
		SP32A32, // Storess 32-bit integer from address register into 32-bit pointer operand
		SR32G, // Stores 32-bit integer from general register into position pointed to by regjster
		SR32A, // Stores 32-bit integer from address register into position pointed to by regjster
		FADD, // Floating point addition
		FSUB, // Floating poid subtraction
		FMUL, // Floating point multiplication
		FDIV, // Floating point division
		PAD
	};
};
