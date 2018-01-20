#pragma once
#include "include/arch/Arrpee8.hpp"
class Arrpee8plus : public AbstractArchitecture
{
private:
	Arrpee8plus();
	static sAbstractArchitecture singleton;
public:
	static void RegisterArrpe8plus(pAbstractArchitecture arch);
	static sAbstractArchitecture getSingleton();
	enum INST_SET_RP8P : uint8_t
	{
		// 16-bit memory address
		P16GOTO = Arrpee8::PAD, // 16-bit pointer GOTO
		P16SUBR, // 16-bit pointer subroutine
		P16JSUBR, // 16-bit pointer jailed subroutine
		LCA16, // Load 16-bit constant into address register (operand)
		LR16A, // Loads 16-bit integer to address register from position pointed to by regjster
		LP16G8, // Load 8-bit integer into general register from 16-bit pointer operand
		LP16A16, // Load 16-bit integer into address register from 16-bit pointer operand
		SP16G8, // Stores 8-bit integer from general register into 16-bit pointer operand
		SP16A16, // Storess 16-bit integer from address register into 16-bit pointer operand
		SR16A, // Stores 16-bit integer from address register into position pointed to by regjster
		PAD
	};
};

class Arrpee8plus_Machine : public Processor<uint8_t, uint16_t, uint8_t>
{
public:
	typedef Processor<uint8_t, uint16_t, uint8_t> PROCTYPE;
	Arrpee8plus_Machine(sAbstractMemoryDevice newMemory, timespec& newWaitingTime)
		: PROCTYPE(newMemory,Arrpee8plus::getSingleton(),newWaitingTime,8,8 - AbstractProcessor::PAD)
	{
		;
	}
};
