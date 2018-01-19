#pragma once
#include "include/arch/Arrpee16.hpp"
class Arrpee16plus : public AbstractArchitecture
{
private:
	Arrpee16plus();
	static sAbstractArchitecture singleton;
public:
	static void RegisterArrpee16plus(pAbstractArchitecture arch);
	static sAbstractArchitecture getSingleton();
	enum INST_SET_RP16P : uint8_t
	{
		// 24-bit memory address
		P24GOTO = Arrpee16::PAD, // 24-bit pointer GOTO
		P24SUBR, // 24-bit pointer subroutine
		P24JSUBR, // 24-bit pointer jailed subroutine
		LCA24, // Load 24-bit constant into address register (operand)
		LR24A, // Loads 24-bit integer to address register from position pointed to by regjster
		LP24G8, // Load 8-bit integer into general register from 24-bit pointer operand
		LP24G16, // Load 16-bit integer into general register from 24-bit pointer operand
		LP24A24, // Load 24-bit integer into address register from 24-bit pointer operand
		SP8G24, // Stores 8-bit integer from general register into 24-bit pointer operand
		SP16G24, // Stores 8-bit integer from general register into 24-bit pointer operand
		SP24A24, // Storess 24-bit integer from address register into 24-bit pointer operand
		SR24A, // Stores 24-bit integer from address register into position pointed to by regjster
		PAD
	};
};
