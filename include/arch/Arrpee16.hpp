#pragma once
#include "include/arch/Arrpee8plus.hpp"
class Arrpee16 : public AbstractArchitecture
{
private:
	Arrpee16();
	static sAbstractArchitecture singleton;
public:
	static void RegisterArrpe16(pAbstractArchitecture arch);
	static sAbstractArchitecture getSingleton();
	enum INST_SET_RP16 : uint8_t
	{
		LCG16 = Arrpee8plus::PAD, // Load 16-bit constant into general register (operand)
		LR16G, // Loads 16-bit integer to general register from position pointed to by regjster
		LP16G16, // Load 16-bit integer into general register from 16-bit pointer operand
		SP16G16, // Stores 16-bit integer from general register into 16-bit pointer operand
		SR16G, // Stores 8-bit integer from general register into position pointed to by regjster
		PAD
	};
};
