#include "arch/DeaDea16.hpp"
#include <stdexcept>
#include <iostream>       // std::cerr

namespace Arch {
sDeaDea16 DeaDea16::__instance = nullptr;
DeaDea16::DeaDea16()
{
	// Register the instructions
	RegisterInstruction(&inNOPE,_NOPE);
	RegisterInstruction(&inEXIT,_EXIT);
	RegisterInstruction(&inPANIC,_PANIC);
	RegisterInstruction(&inSWITCH,_SWITCH);
	RegisterInstruction(&inRES,_RES);
	RegisterInstruction(&inRET,_RET);
	RegisterInstruction(&inGOTO,_GOTO);
	RegisterInstruction(&inLOADACA8,_LOADACA8);
	RegisterInstruction(&inLOADARA8,_LOADARA8);
	RegisterInstruction(&inLOADACP8,_LOADACP8);
	RegisterInstruction(&inLOADARP8,_LOADARP8);
	RegisterInstruction(&inLOADACA16,_LOADACA16);
	RegisterInstruction(&inLOADARA16,_LOADARA16);
	RegisterInstruction(&inLOADACP16,_LOADACP16);
	RegisterInstruction(&inLOADARP16,_LOADARP16);
	RegisterInstruction(&inSTORAC8,_STORAC8);
	RegisterInstruction(&inSTORAR8,_STORAR8);
	RegisterInstruction(&inSTORAC16,_STORAC16);
	RegisterInstruction(&inSTORAR16,_STORAR16);
	// Arithmetical and bitwise instructions
	RegisterInstruction(&inADD,_ADD);
	RegisterInstruction(&inNEG,_NEG);
	RegisterInstruction(&inMUL,_MUL);
	RegisterInstruction(&inDIV,_DIV);
	RegisterInstruction(&inMOD,_MOD);
	RegisterInstruction(&inLBW,_LBW);
	RegisterInstruction(&inRBW,_RBW);
	RegisterInstruction(&inBXOR,_BXOR);
	RegisterInstruction(&inBIOR,_BIOR);
	RegisterInstruction(&inBAND,_BAND);
	RegisterInstruction(&inBNOT,_BNOT);
	// Logical instructions
	RegisterInstruction(&inEQUAL,_EQUAL);
	RegisterInstruction(&inNEQUAL,_NEQUAL);
	RegisterInstruction(&inLESSER,_LESSER);
	RegisterInstruction(&inGREATER,_GREATER);
	RegisterInstruction(&inELESSER,_ELESSER);
	RegisterInstruction(&inEGREATER,_EGREATER);
	RegisterInstruction(&inLNOT,_LNOT);
	RegisterInstruction(&inLOR,_LOR);
	RegisterInstruction(&inLAND,_LAND);
}
/*pDeaDea16 DeaDea16::instance()
{
	if(!__instance)
	{
		__instance = new DeaDea16();
	}
	return __instance;
}*/

sDeaDea16 DeaDea16::instance()
{
	if(!__instance.get())
	{
		__instance = sDeaDea16(new DeaDea16());
	}
	return __instance;
}

DeaDea16::SharedCpuType DeaDea16::CastToAbstract()
{
	return std::static_pointer_cast<AbstractCpuType>(instance());
}

Psecom::Pstate DeaDea16::inNOPE(RegisterStorage str)
{
	return Psecom::KEEP_GOING;
}

Psecom::Pstate DeaDea16::inEXIT(RegisterStorage str)
{
	return Psecom::STOP;
}

Psecom::Pstate DeaDea16::inPANIC(RegisterStorage str)
{
	return Psecom::PANIC;
}
Psecom::Pstate DeaDea16::inRET(RegisterStorage str)
{
	str->Return();
	return Psecom::KEEP_GOING;
}
Psecom::Pstate DeaDea16::inRES(RegisterStorage str)
{
	str->PopState();
	return Psecom::KEEP_GOING;
}

Psecom::Pstate DeaDea16::inGOTO(RegisterStorage str)
{
	try {
	uint16_t* tmp = static_cast<uint16_t*>(str->AccessMemoryAtPC());
	str->Goto(*tmp);
	return Psecom::KEEP_GOING;
	} catch(std::out_of_range exp)
	{
		std::cerr << "COMPUTER PANIC!\nShutting down.\nReason: Out of Range Error - " << exp.what() << '\n';
		return Psecom::PANIC;
	}
}

Psecom::Pstate DeaDea16::inSWITCH(RegisterStorage str)
{
	uint16_t tmp = str->GetAccumulatorRegister();
	str->SetAccumulatorRegister(str->GetArgumentRegister() );
	str->SetArgumentRegister(tmp);
	return Psecom::KEEP_GOING;
} // Loads 8-bit number into the accumulator register. A single 1-byte operand.

Psecom::Pstate DeaDea16::inLOADACA8(RegisterStorage str)
{
	try {
	uint8_t* tmp = static_cast<uint8_t*>(str->AccessMemoryAtPC());
	str->SetAccumulatorRegister((uint16_t)*tmp);
	str->IncrementProgramCounter(sizeof(uint8_t));
	return Psecom::KEEP_GOING;
	} catch(std::out_of_range exp)
	{
		std::cerr << "COMPUTER PANIC!\nShutting down.\nReason: Out of Range Error - " << exp.what() << '\n';
		return Psecom::PANIC;
	}
} // Loads 8-bit number into the accumulator register. A single 1-byte operand.
Psecom::Pstate DeaDea16::inLOADARA8(RegisterStorage str)
{
	try {
	uint8_t* tmp = static_cast<uint8_t*>(str->AccessMemoryAtPC());
	str->SetArgumentRegister((uint16_t)*tmp);
	str->IncrementProgramCounter(sizeof(uint8_t));
	return Psecom::KEEP_GOING;
	} catch(std::out_of_range exp)
	{
		std::cerr << "COMPUTER PANIC!\nShutting down.\nReason: Out of Range Error - " << exp.what() << '\n';
		return Psecom::PANIC;
	}
}
Psecom::Pstate DeaDea16::inLOADACP8(RegisterStorage str)
{
	try {
	uint16_t* tmp_ptr = static_cast<uint16_t*>(str->AccessMemoryAtPC());
	str->IncrementProgramCounter(sizeof(uint16_t));
	uint8_t* tmp = static_cast<uint8_t*>(str->AccessMemoryAt(*tmp_ptr));
	str->SetAccumulatorRegister((uint16_t)*tmp);
	return Psecom::KEEP_GOING;
	} catch(std::out_of_range exp)
	{
		std::cerr << "COMPUTER PANIC!\nShutting down.\nReason: Out of Range Error - " << exp.what() << '\n';
		return Psecom::PANIC;
	}
} // Loads 8-bit number into the accumulator register. A single 2-byte operand (pointer).
Psecom::Pstate DeaDea16::inLOADARP8(RegisterStorage str)
{
	try {
	uint16_t* tmp_ptr = static_cast<uint16_t*>(str->AccessMemoryAtPC());
	str->IncrementProgramCounter(sizeof(uint16_t));
	uint8_t* tmp = static_cast<uint8_t*>(str->AccessMemoryAt(*tmp_ptr));
	str->SetArgumentRegister((uint16_t)*tmp);
	return Psecom::KEEP_GOING;
	} catch(std::out_of_range exp)
	{
		std::cerr << "COMPUTER PANIC!\nShutting down.\nReason: Out of Range Error - " << exp.what() << '\n';
		return Psecom::PANIC;
	}
} // Loads 8-bit number into the argument register. A single 2-byte operand (pointer).
Psecom::Pstate DeaDea16::inLOADACA16(RegisterStorage str)
{
	try {
	uint16_t* tmp = static_cast<uint16_t*>(str->AccessMemoryAtPC());
	str->SetAccumulatorRegister(*tmp);
	str->IncrementProgramCounter(sizeof(uint16_t));
	return Psecom::KEEP_GOING;
	} catch(std::out_of_range exp)
	{
		std::cerr << "COMPUTER PANIC!\nShutting down.\nReason: Out of Range Error - " << exp.what() << '\n';
		return Psecom::PANIC;
	}
} // Loads 16-bit number into the accumulator register. A single 2-byte operand.
Psecom::Pstate DeaDea16::inLOADARA16(RegisterStorage str)
{
	try {
	uint16_t* tmp = static_cast<uint16_t*>(str->AccessMemoryAtPC());
	str->SetArgumentRegister(*tmp);
	str->IncrementProgramCounter(sizeof(uint16_t));
	return Psecom::KEEP_GOING;
	} catch(std::out_of_range exp)
	{
		std::cerr << "COMPUTER PANIC!\nShutting down.\nReason: Out of Range Error - " << exp.what() << '\n';
		return Psecom::PANIC;
	}
} // Loads 16-bit number into the argument register. A single 2-byte operand.
Psecom::Pstate DeaDea16::inLOADACP16(RegisterStorage str)
{
	try {
	uint16_t* tmp_ptr = static_cast<uint16_t*>(str->AccessMemoryAtPC());
	str->IncrementProgramCounter(sizeof(uint16_t));
	uint16_t* tmp = static_cast<uint16_t*>(str->AccessMemoryAt(*tmp_ptr));
	str->SetAccumulatorRegister(*tmp);
	return Psecom::KEEP_GOING;
	} catch(std::out_of_range exp)
	{
		std::cerr << "COMPUTER PANIC!\nShutting down.\nReason: Out of Range Error - " << exp.what() << '\n';
		return Psecom::PANIC;
	}
} // Loads 16-bit number into the accumulator register. A single 2-byte operand (pointer).
Psecom::Pstate DeaDea16::inLOADARP16(RegisterStorage str)
{
	try {
	uint16_t* tmp_ptr = static_cast<uint16_t*>(str->AccessMemoryAtPC());
	str->IncrementProgramCounter(sizeof(uint16_t));
	uint16_t* tmp = static_cast<uint16_t*>(str->AccessMemoryAt(*tmp_ptr));
	str->SetArgumentRegister(*tmp);
	return Psecom::KEEP_GOING;
	} catch(std::out_of_range exp)
	{
		std::cerr << "COMPUTER PANIC!\nShutting down.\nReason: Out of Range Error - " << exp.what() << '\n';
		return Psecom::PANIC;
	}
} // Loads 16-bit number into the argument register. A single 2-byte operand (pointer).
Psecom::Pstate DeaDea16::inSTORAC8(RegisterStorage str)
{
	try {
	uint16_t* tmp_ptr = static_cast<uint16_t*>(str->AccessMemoryAtPC());
	str->IncrementProgramCounter(sizeof(uint16_t));
	uint8_t* tmp = static_cast<uint8_t*>(str->AccessMemoryAt(*tmp_ptr));
	*tmp = (uint8_t)str->GetAccumulatorRegister();
	return Psecom::KEEP_GOING;
	} catch(std::out_of_range exp)
	{
		std::cerr << "COMPUTER PANIC!\nShutting down.\nReason: Out of Range Error - " << exp.what() << '\n';
		return Psecom::PANIC;
	}
} // Copies 8-bit number from accumulator register to said memory block. A single 2-byte operand (pointer).
Psecom::Pstate DeaDea16::inSTORAR8(RegisterStorage str)
{
	try {
	uint16_t* tmp_ptr = static_cast<uint16_t*>(str->AccessMemoryAtPC());
	str->IncrementProgramCounter(sizeof(uint16_t));
	uint8_t* tmp = static_cast<uint8_t*>(str->AccessMemoryAt(*tmp_ptr));
	*tmp = (uint8_t)str->GetArgumentRegister();
	return Psecom::KEEP_GOING;
	} catch(std::out_of_range exp)
	{
		std::cerr << "COMPUTER PANIC!\nShutting down.\nReason: Out of Range Error - " << exp.what() << '\n';
		return Psecom::PANIC;
	}
} // Copies 8-bit number from argument register to said memory block. A single 2-byte operand (pointer).
Psecom::Pstate DeaDea16::inSTORAC16(RegisterStorage str)
{
	try {
	uint16_t* tmp_ptr = static_cast<uint16_t*>(str->AccessMemoryAtPC());
	str->IncrementProgramCounter(sizeof(uint16_t));
	uint16_t* tmp = static_cast<uint16_t*>(str->AccessMemoryAt(*tmp_ptr));
	*tmp = str->GetAccumulatorRegister();
	return Psecom::KEEP_GOING;
	} catch(std::out_of_range exp)
	{
		std::cerr << "COMPUTER PANIC!\nShutting down.\nReason: Out of Range Error - " << exp.what() << '\n';
		return Psecom::PANIC;
	}
} // Copies 16-bit number from accumulator register to said memory block. A single 2-byte operand (pointer).
Psecom::Pstate DeaDea16::inSTORAR16(RegisterStorage str)
{
	try {
	uint16_t* tmp_ptr = static_cast<uint16_t*>(str->AccessMemoryAtPC());
	str->IncrementProgramCounter(sizeof(uint16_t));
	uint16_t* tmp = static_cast<uint16_t*>(str->AccessMemoryAt(*tmp_ptr));
	*tmp = str->GetArgumentRegister();
	return Psecom::KEEP_GOING;
	} catch(std::out_of_range exp)
	{
		std::cerr << "COMPUTER PANIC!\nShutting down.\nReason: Out of Range Error - " << exp.what() << '\n';
		return Psecom::PANIC;
	}
} // Copies 16-bit number from argument register to said memory block. A single 2-byte operand (pointer).

Psecom::Pstate DeaDea16::inMEMCPY(RegisterStorage str)
{
	try {
	uint16_t* origin = static_cast<uint16_t*>(str->AccessMemoryAtPC());
	str->IncrementProgramCounter(sizeof(uint16_t));
	uint16_t* destination = static_cast<uint16_t*>(str->AccessMemoryAtPC());
	str->IncrementProgramCounter(sizeof(uint16_t));
	uint16_t* size = static_cast<uint16_t*>(str->AccessMemoryAtPC());
	str->IncrementProgramCounter(sizeof(uint16_t));
	str->MemoryCopy(*destination,str->AccessMemoryAt(*origin),*size);
	return Psecom::KEEP_GOING;
	} catch(std::out_of_range exp)
	{
		std::cerr << "COMPUTER PANIC!\nShutting down.\nReason: Out of Range Error - " << exp.what() << '\n';
		return Psecom::PANIC;
	}
} // 3 16-bit operands (all pointers) - origin, destination, size

Psecom::Pstate DeaDea16::inADD(RegisterStorage str)
{
	str->SetAccumulatorRegister(str->GetAccumulatorRegister() + str->GetArgumentRegister() );
	return Psecom::KEEP_GOING;
} // Addition. No operands.
Psecom::Pstate DeaDea16::inNEG(RegisterStorage str)
{
	str->SetAccumulatorRegister(str->GetAccumulatorRegister() - str->GetArgumentRegister() );
	return Psecom::KEEP_GOING;
} // Negation. No operands.
Psecom::Pstate DeaDea16::inMUL(RegisterStorage str)
{
	str->SetAccumulatorRegister(str->GetAccumulatorRegister() * str->GetArgumentRegister() );
	return Psecom::KEEP_GOING;
} // Multiplication. No operands.
Psecom::Pstate DeaDea16::inDIV(RegisterStorage str)
{
	str->SetAccumulatorRegister(str->GetAccumulatorRegister() / str->GetArgumentRegister() );
	return Psecom::KEEP_GOING;
} // Division. No operands.
Psecom::Pstate DeaDea16::inMOD(RegisterStorage str)
{
	str->SetAccumulatorRegister(str->GetAccumulatorRegister() % str->GetArgumentRegister() );
	return Psecom::KEEP_GOING;
} // Modulo. No operands.
Psecom::Pstate DeaDea16::inLBW(RegisterStorage str)
{
	str->SetAccumulatorRegister(str->GetAccumulatorRegister() << str->GetArgumentRegister() );
	return Psecom::KEEP_GOING;
} // Leftwards bitwise shift. No operands.
Psecom::Pstate DeaDea16::inRBW(RegisterStorage str)
{
	str->SetAccumulatorRegister(str->GetAccumulatorRegister() >> str->GetArgumentRegister() );
	return Psecom::KEEP_GOING;
} // Rightwards bitwise shift. No operands.
Psecom::Pstate DeaDea16::inBXOR(RegisterStorage str)
{
	str->SetAccumulatorRegister(str->GetAccumulatorRegister() ^ str->GetArgumentRegister() );
	return Psecom::KEEP_GOING;
} // Bitwise XOR. No operands.
Psecom::Pstate DeaDea16::inBIOR(RegisterStorage str)
{
	str->SetAccumulatorRegister(str->GetAccumulatorRegister() | str->GetArgumentRegister() );
	return Psecom::KEEP_GOING;
} // Bitwise inclusive OR. No operands.
Psecom::Pstate DeaDea16::inBAND(RegisterStorage str)
{
	str->SetAccumulatorRegister(str->GetAccumulatorRegister() & str->GetArgumentRegister() );
	return Psecom::KEEP_GOING;
} // Bitwise AND. No operands.
Psecom::Pstate DeaDea16::inBNOT(RegisterStorage str)
{
	str->SetAccumulatorRegister( ~str->GetAccumulatorRegister() );
	return Psecom::KEEP_GOING;
} // Bitwise NOT. No operands.

Psecom::Pstate DeaDea16::inEQUAL(RegisterStorage str)
{
	str->SetAccumulatorRegister(str->GetAccumulatorRegister() == str->GetArgumentRegister() );
	return Psecom::KEEP_GOING;
} // Equal. No operands.
Psecom::Pstate DeaDea16::inNEQUAL(RegisterStorage str)
{
	str->SetAccumulatorRegister(str->GetAccumulatorRegister() != str->GetArgumentRegister() );
	return Psecom::KEEP_GOING;
} // Not equal. No operands.
Psecom::Pstate DeaDea16::inLESSER(RegisterStorage str)
{
	str->SetAccumulatorRegister(str->GetAccumulatorRegister() < str->GetArgumentRegister() );
	return Psecom::KEEP_GOING;
} // Lesser. No operands.
Psecom::Pstate DeaDea16::inGREATER(RegisterStorage str)
{
	str->SetAccumulatorRegister(str->GetAccumulatorRegister() > str->GetArgumentRegister() );
	return Psecom::KEEP_GOING;
} // Greater. No operands.
Psecom::Pstate DeaDea16::inELESSER(RegisterStorage str)
{
	str->SetAccumulatorRegister(str->GetAccumulatorRegister() <= str->GetArgumentRegister() );
	return Psecom::KEEP_GOING;
} // Lesser or equal. No operands.
Psecom::Pstate DeaDea16::inEGREATER(RegisterStorage str)
{
	str->SetAccumulatorRegister(str->GetAccumulatorRegister() >= str->GetArgumentRegister() );
	return Psecom::KEEP_GOING;
} // Greater or equal. No operands.
Psecom::Pstate DeaDea16::inLNOT(RegisterStorage str)
{
	str->SetAccumulatorRegister( !str->GetAccumulatorRegister() );
	return Psecom::KEEP_GOING;
} // Logical NOT. No operands.
Psecom::Pstate DeaDea16::inLOR(RegisterStorage str)
{
	str->SetAccumulatorRegister( str->GetAccumulatorRegister() || str->GetArgumentRegister() );
	return Psecom::KEEP_GOING;
} // Logical OR. No operands.
Psecom::Pstate DeaDea16::inLAND(RegisterStorage str)
{
	str->SetAccumulatorRegister( str->GetAccumulatorRegister() && str->GetArgumentRegister() );
	return Psecom::KEEP_GOING;
} // Logical AND. No operands.

}
