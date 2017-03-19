#ifndef DEADEA8_HPP
#define DEADEA8_HPP
#include "include/AbstractProcessor.hpp"
namespace Fcom {

class Deadea8 : public AbstractProcessor<uint8_t,uint8_t>
{
public:
	Deadea8(uint8_t banknum);
	virtual ~Deadea8();
	static Pstate EXIT(RegisterStorage reg,uint8_t memspace);

	//Memory access instructions
	static Pstate LOADA(RegisterStorage reg,uint8_t ammount); // Loads operand into the accumulator register
	static Pstate LOADP(RegisterStorage reg,uint8_t memspace);
	static Pstate LOADPP(RegisterStorage reg,uint8_t memspace);
	static Pstate STORP(RegisterStorage reg,uint8_t memspace);
	static Pstate STORPP(RegisterStorage reg,uint8_t memspace);
	static Pstate BANKA(RegisterStorage reg,uint8_t memspace);
	static Pstate BANKP(RegisterStorage reg,uint8_t memspace);
	static Pstate BANKPP(RegisterStorage reg,uint8_t memspace);
	static Pstate GOTOA(RegisterStorage reg,uint8_t memspace);
	static Pstate GOTOP(RegisterStorage reg,uint8_t memspace);
	static Pstate GOTOPP(RegisterStorage reg,uint8_t memspace);


	//Arithmetic instructions
	static Pstate ADDA(RegisterStorage reg,uint8_t ammount);
	static Pstate ADDP(RegisterStorage reg,uint8_t memspace);
	static Pstate ADDPP(RegisterStorage reg,uint8_t memspace);
	static Pstate SUBA(RegisterStorage reg,uint8_t ammount);
	static Pstate SUBP(RegisterStorage reg,uint8_t memspace);
	static Pstate SUBPP(RegisterStorage reg,uint8_t memspace);

	//Bitwise operations
	static Pstate LBWA(RegisterStorage reg,uint8_t ammount); // Bitwise shift leftwards
	static Pstate LBWP(RegisterStorage reg,uint8_t ammount);
	static Pstate LBWPP(RegisterStorage reg,uint8_t ammount);
	static Pstate RBWA(RegisterStorage reg,uint8_t ammount); // Bitwise shift rightwards
	static Pstate RBWP(RegisterStorage reg,uint8_t ammount);
	static Pstate RBWPP(RegisterStorage reg,uint8_t ammount);
	static Pstate ANDA(RegisterStorage reg,uint8_t ammount); // Bitwise AND
	static Pstate ANDP(RegisterStorage reg,uint8_t ammount);
	static Pstate ANDPP(RegisterStorage reg,uint8_t ammount);
	static Pstate ORA(RegisterStorage reg,uint8_t ammount); // Bitwise OR
	static Pstate ORP(RegisterStorage reg,uint8_t ammount);
	static Pstate ORPP(RegisterStorage reg,uint8_t ammount);
	static Pstate XORA(RegisterStorage reg,uint8_t ammount); // Bitwise XOR
	static Pstate XORP(RegisterStorage reg,uint8_t ammount);
	static Pstate XORPP(RegisterStorage reg,uint8_t ammount);
	static Pstate NOT(RegisterStorage reg,uint8_t ammount); // Bitwise NOT - complement


	enum InstructionList : uint8_t {
		_EXIT = 128, // 0x80
		_LOADA = 129,
		_LOADP = 130,
		_LOADPP = 131,
		_STORP = 132,
		_STORPP = 133,
		_BANKA = 134,
		_BANKP = 135,
		_BANKPP = 136,
		_GOTOA = 137,
		_GOTOP = 138,
		_GOTOPP = 139,
		_ADDA = 140,
		_ADDP = 141,
		_ADDPP = 142,
		_SUBA = 143,
		_SUBP = 144,
		_SUBPP = 145,
		_LBWA = 146,
		_LBWP = 147,
		_LBWPP = 148,
		_RBWA = 149,
		_RBWP = 150,
		_RBWPP = 151,
		_ANDA = 152,
		_ANDP = 153,
		_ANDPP = 154,
		_ORA = 155,
		_ORP = 156,
		_ORPP = 157,
		_XORA = 158,
		_XORP = 159,
		_XORPP = 160,
		_NOT = 161
	};

private:
};
}
#endif // DEADEA8_HPP
