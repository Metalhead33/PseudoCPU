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
		_StoreAR16 = _StoreAC16+1 // Stores into the memory from the Argument Register
	};

	// Base Instructions
	static Pstate InEXIT(RegisterStorage str) { return STOP; } // Self-evident. Stops the machine.
	static Pstate InPANIC(RegisterStorage str) { return PANIC; } // Self-evident. Force-exits the machine.

	// 8-bit Memory Access Instructions
	static Pstate LoadAAC8(RegisterStorage str); // Loads into the Accumulator Register - Absolute
	static Pstate LoadAAR8(RegisterStorage str); // Loads into the Argument Register - Absolute
	static Pstate LoadPAC8(RegisterStorage str); // Loads into the Accumulator Register - Pointer
	static Pstate LoadPAR8(RegisterStorage str); // Loads into the Argument Register - Pointer
	static Pstate StoreAC8(RegisterStorage str); // Stores into the memory from the Accumulator Register
	static Pstate StoreAR8(RegisterStorage str); // Stores into the memory from the Argument Register

	// 16-bit Memory Access Instructions
	static Pstate Switch(RegisterStorage str); // Switches up the Accumulator Register and Argument Register
	static Pstate LoadAAC16(RegisterStorage str); // Loads into the Accumulator Register - Absolute
	static Pstate LoadAAR16(RegisterStorage str); // Loads into the Argument Register - Absolute
	static Pstate LoadPAC16(RegisterStorage str); // Loads into the Accumulator Register - Pointer
	static Pstate LoadPAR16(RegisterStorage str); // Loads into the Argument Register - Pointer
	static Pstate StoreAC16(RegisterStorage str); // Stores into the memory from the Accumulator Register
	static Pstate StoreAR16(RegisterStorage str); // Stores into the memory from the Argument Register
};

#endif // DEADEA16_HPP
