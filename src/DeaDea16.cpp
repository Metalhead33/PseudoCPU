#include "include/DeaDea16.hpp"

DeaDea16::DeaDea16(uint16_t memsize)
	: AbstractProcessor<uint8_t,uint16_t>(memsize)
{
	RegisterFunctions();
}
DeaDea16::DeaDea16(uint8_t* extmem, uint16_t memsize)
	: AbstractProcessor<uint8_t,uint16_t>(extmem,memsize)
{
	RegisterFunctions();
}
DeaDea16::DeaDea16(SharedMemory shared_mem, uint16_t memsize)
	: AbstractProcessor<uint8_t,uint16_t>(shared_mem,memsize)
{
	RegisterFunctions();
}
DeaDea16::DeaDea16(AbstractFread* fileread)
	: AbstractProcessor<uint8_t,uint16_t>(fileread)
{
	RegisterFunctions();
}

void DeaDea16::RegisterFunctions()
{
	// Basic control functions
	RegisterInstruction(&InEXIT, _EXIT);
	RegisterInstruction(&InPANIC, _PANIC);

	// 8-bit memory access
	RegisterInstruction(&LoadAAC8, _LoadAAC8);
	RegisterInstruction(&LoadAAR8, _LoadAAR8);
	RegisterInstruction(&LoadPAC8, _LoadPAC8);
	RegisterInstruction(&LoadPAR8, _LoadPAR8);
	RegisterInstruction(&StoreAC8, _StoreAC8);
	RegisterInstruction(&StoreAR8, _StoreAR8);

	// 16-bit memory access
	RegisterInstruction(&Switch, _Switch);
	RegisterInstruction(&LoadAAC16, _LoadAAC16);
	RegisterInstruction(&LoadAAR16, _LoadAAR16);
	RegisterInstruction(&LoadPAC16, _LoadPAC16);
	RegisterInstruction(&LoadPAR16, _LoadPAR16);
	RegisterInstruction(&StoreAC16, _StoreAC16);
	RegisterInstruction(&StoreAR16, _StoreAR16);

	//Arithmetical and logical instructions
	RegisterInstruction(&ADD, _ADD);
	RegisterInstruction(&SUB, _SUB);
	RegisterInstruction(&MUL, _MUL);
	RegisterInstruction(&DIV, _DIV);
	RegisterInstruction(&MOD, _MOD);
	RegisterInstruction(&LAND, _LAND);
	RegisterInstruction(&BAND, _BAND);
	RegisterInstruction(&LOR, _LOR);
	RegisterInstruction(&BOR, _BOR);
	RegisterInstruction(&BXOR, _BXOR);
	RegisterInstruction(&LNOT, _LNOT);
	RegisterInstruction(&BNOT, _BNOT);
	RegisterInstruction(&BLSH, _BLSH);
	RegisterInstruction(&BRSH, _BRSH);

	//Control flow
	RegisterInstruction(&GOTO, _GOTO);
	RegisterInstruction(&IF, _IF);
	RegisterInstruction(&IFN, _IFN);
}

Pstate DeaDea16::Switch(RegisterStorage str)
{
	str->SwitchRegisters();
	return KEEP_GOING;
} // Switches up the Accumulator Register and Argument Register

// 16-bit memory access functions

Pstate DeaDea16::LoadAAC16(RegisterStorage str)
{
	uint16_t* operand = str->CastAccessMemAtPC<uint16_t>();
	IF_DEBUG(
				std::cout << "Operand Address: " << (size_t)operand << std::endl;
				std::cout << "LoadAAC16 Operand: " << (int)*operand << std::endl;
	)
	str->IncrementPC(sizeof(uint16_t));
	str->SetACR(*operand);
	return KEEP_GOING;
} // Loads into the Accumulator Register - Absolute

Pstate DeaDea16::LoadAAR16(RegisterStorage str)
{
	uint16_t* operand = str->CastAccessMemAtPC<uint16_t>();
	IF_DEBUG(
				std::cout << "Operand Address: " << (size_t)operand << std::endl;
				std::cout << "LoadAAR16 Operand: " << (int)*operand << std::endl;
	)
	str->IncrementPC(sizeof(uint16_t));
	str->SetARR(*operand);
	return KEEP_GOING;
} // Loads into the Argument Register - Absolute

Pstate DeaDea16::LoadPAC16(RegisterStorage str)
{
	uint16_t* operand = str->CastAccessMemAtPC<uint16_t>();
	IF_DEBUG(
				std::cout << "Operand Address: " << (size_t)operand << std::endl;
				std::cout << "LoadPAC16 Operand: " << (int)*operand << std::endl;
	)
	str->IncrementPC(sizeof(uint16_t));
	operand = str->CastAccessMemory<uint16_t>(*operand);
	str->SetACR(*operand);
	return KEEP_GOING;
} // Loads into the Accumulator Register - Pointer

Pstate DeaDea16::LoadPAR16(RegisterStorage str)
{
	uint16_t* operand = str->CastAccessMemAtPC<uint16_t>();
	IF_DEBUG(
				std::cout << "Operand Address: " << (size_t)operand << std::endl;
				std::cout << "LoadPAR16 Operand: " << (int)*operand << std::endl;
	)
	str->IncrementPC(sizeof(uint16_t));
	operand = str->CastAccessMemory<uint16_t>(*operand);
	str->SetARR(*operand);
	return KEEP_GOING;
} // Loads into the Argument Register - Pointer

Pstate DeaDea16::StoreAC16(RegisterStorage str)
{
	uint16_t* operand = str->CastAccessMemAtPC<uint16_t>();
	IF_DEBUG(
				std::cout << "Operand Address: " << (size_t)operand << std::endl;
				std::cout << "StoreAC16 Operand: " << (int)*operand << std::endl;
	)
	str->IncrementPC(sizeof(uint16_t));
	operand = str->CastAccessMemory<uint16_t>(*operand);
	*operand = str->GetACR();
	return KEEP_GOING;
} // Stores into the memory from the Accumulator Register

Pstate DeaDea16::StoreAR16(RegisterStorage str)
{
	uint16_t* operand = str->CastAccessMemAtPC<uint16_t>();
	IF_DEBUG(
				std::cout << "Operand Address: " << (size_t)operand << std::endl;
				std::cout << "StoreAR16 Operand: " << (int)*operand << std::endl;
	)
	str->IncrementPC(sizeof(uint16_t));
	operand = str->CastAccessMemory<uint16_t>(*operand);
	*operand = str->GetARR();
	return KEEP_GOING;
} // Stores into the memory from the Argument Register

// 8-bit memory access functions

Pstate DeaDea16::LoadAAC8(RegisterStorage str)
{
	uint8_t* operand = str->CastAccessMemAtPC<uint8_t>();
	IF_DEBUG(
				std::cout << "Operand Address: " << (size_t)operand << std::endl;
				std::cout << "LoadAAC8 Operand: " << (int)*operand << std::endl;
	)
	str->IncrementPC(sizeof(uint8_t));
	str->SetACR(*operand);
	return KEEP_GOING;
} // Loads into the Accumulator Register - Absolute

Pstate DeaDea16::LoadAAR8(RegisterStorage str)
{
	uint8_t* operand = str->CastAccessMemAtPC<uint8_t>();
	IF_DEBUG(
				std::cout << "Operand Address: " << (size_t)operand << std::endl;
				std::cout << "LoadAAR8 Operand: " << (int)*operand << std::endl;
	)
	str->IncrementPC(sizeof(uint8_t));
	str->SetARR(*operand);
	return KEEP_GOING;
} // Loads into the Argument Register - Absolute

Pstate DeaDea16::LoadPAC8(RegisterStorage str)
{
	uint16_t* operand = str->CastAccessMemAtPC<uint16_t>();
	IF_DEBUG(
				std::cout << "Operand Address: " << (size_t)operand << std::endl;
				std::cout << "LoadPAC8 Operand: " << (int)*operand << std::endl;
	)
	str->IncrementPC(sizeof(uint16_t));
	uint8_t* temp = str->CastAccessMemory<uint8_t>(*operand);
	str->SetACR(*temp);
	return KEEP_GOING;
} // Loads into the Accumulator Register - Pointer

Pstate DeaDea16::LoadPAR8(RegisterStorage str)
{
	uint16_t* operand = str->CastAccessMemAtPC<uint16_t>();
	IF_DEBUG(
				std::cout << "Operand Address: " << (size_t)operand << std::endl;
				std::cout << "LoadPAR8 Operand: " << (int)*operand << std::endl;
	)
	str->IncrementPC(sizeof(uint16_t));
	uint8_t* temp = str->CastAccessMemory<uint8_t>(*operand);
	str->SetARR(*temp);
	return KEEP_GOING;
} // Loads into the Argument Register - Pointer

Pstate DeaDea16::StoreAC8(RegisterStorage str)
{
	uint16_t* operand = str->CastAccessMemAtPC<uint16_t>();
	IF_DEBUG(
				std::cout << "Operand Address: " << (size_t)operand << std::endl;
				std::cout << "StoreAC8 Operand: " << (int)(*operand) << std::endl;
	)
	str->IncrementPC(sizeof(uint16_t));
	uint8_t* temp = str->CastAccessMemory<uint8_t>(*operand);
	*temp = (uint8_t)str->GetACR();
	return KEEP_GOING;
} // Stores into the memory from the Accumulator Register

Pstate DeaDea16::StoreAR8(RegisterStorage str)
{
	uint16_t* operand = str->CastAccessMemAtPC<uint16_t>();
	IF_DEBUG(
				std::cout << "Operand Address: " << (size_t)operand << std::endl;
				std::cout << "StoreAR8 Operand: " << (int)*operand << std::endl;
	)
	str->IncrementPC(sizeof(uint16_t));
	uint8_t* temp = str->CastAccessMemory<uint8_t>(*operand);
	*temp = (uint8_t)str->GetARR();
	return KEEP_GOING;
} // Stores into the memory from the Argument Register

Pstate DeaDea16:: ADD(RegisterStorage str)
{
	str->SetACR(str->GetACR() + str->GetARR());
	return KEEP_GOING;
} // Adds the content of registers. (0 operands)
Pstate DeaDea16:: SUB(RegisterStorage str)
{
	str->SetACR(str->GetACR() - str->GetARR());
	return KEEP_GOING;
} // Subtracts the content of registers. (0 operands)
Pstate DeaDea16:: MUL(RegisterStorage str)
{
	str->SetACR(str->GetACR() * str->GetARR());
	return KEEP_GOING;
} // Multiplies the content of registers. (0 operands)
Pstate DeaDea16:: DIV(RegisterStorage str)
{
	str->SetACR(str->GetACR() / str->GetARR());
	return KEEP_GOING;
} // Divides the content of registers. (0 operands)
Pstate DeaDea16:: MOD(RegisterStorage str)
{
	str->SetACR(str->GetACR() % str->GetARR());
	return KEEP_GOING;
} // Moduloes the content of registers. (0 operands)
Pstate DeaDea16:: LAND(RegisterStorage str)
{
	str->SetACR(str->GetACR() && str->GetARR());
	return KEEP_GOING;
} // Logical AND (0 operands)
Pstate DeaDea16:: BAND(RegisterStorage str)
{
	str->SetACR(str->GetACR() & str->GetARR());
	return KEEP_GOING;
} // Bitwise AND (0 operands)
Pstate DeaDea16:: LOR(RegisterStorage str)
{
	str->SetACR(str->GetACR() || str->GetARR());
	return KEEP_GOING;
} // Logical Inclusive OR (0 operands)
Pstate DeaDea16:: BOR(RegisterStorage str)
{
	str->SetACR(str->GetACR() | str->GetARR());
	return KEEP_GOING;
} // Bitwise Inclusive OR (0 operands)
Pstate DeaDea16:: BXOR(RegisterStorage str)
{
	str->SetACR(str->GetACR() ^ str->GetARR());
	return KEEP_GOING;
} // Bitwise Exclusive OR (0 operands)
Pstate DeaDea16:: LNOT(RegisterStorage str)
{
	str->SetACR(!str->GetACR());
	return KEEP_GOING;
} // Logical NOT (0 operands)
Pstate DeaDea16:: BNOT(RegisterStorage str)
{
	str->SetACR(~str->GetACR());
	return KEEP_GOING;
} // Bitwise NOT (0 operands)
Pstate DeaDea16:: BLSH(RegisterStorage str)
{
	str->SetACR(str->GetACR() << str->GetARR());
	return KEEP_GOING;
} // Bitwise left shift of the accumulator by the argument (0 operands)
Pstate DeaDea16:: BRSH(RegisterStorage str)
{
	str->SetACR(str->GetACR() >> str->GetARR());
	return KEEP_GOING;
} // Bitwise right shift of the accumulator by the argument (0 operands)


Pstate DeaDea16:: GOTO(RegisterStorage str) // Go to location pointed by the operand (1 operand, 16-bit)
{
	uint16_t* operand = str->CastAccessMemAtPC<uint16_t>();
	IF_DEBUG(
				std::cout << "Operand Address: " << (size_t)operand << std::endl;
				std::cout << "GOTO Operand: " << (int)*operand << std::endl;
	)
	str->SetPC(*operand);
	//str->IncrementPC(sizeof(uint16_t));
	return KEEP_GOING;
}
Pstate DeaDea16:: IF(RegisterStorage str)
{
	uint16_t* operand = str->CastAccessMemAtPC<uint16_t>();
	if(str->GetACR()) str->SetPC(*operand);
	else str->IncrementPC(sizeof(uint16_t));
	return KEEP_GOING;
} // Go to the location of the operand, if the ACCR is over 0 (1 operand, 16-bit)
Pstate DeaDea16:: IFN(RegisterStorage str)
{
	uint16_t* operand = str->CastAccessMemAtPC<uint16_t>();
	if(str->GetACR()) str->SetPC(*operand);
	else str->IncrementPC(sizeof(uint16_t));
	return KEEP_GOING;
} // Go to the location of the operand, if the ACCR is 0 (1 operand, 16-bit)
