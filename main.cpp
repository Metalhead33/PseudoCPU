#include <iostream>
#include <cstdio>
#include "memory/SharedMemoryAccess.hpp"
#include "arch/DeaDea16.hpp"
#include "abstract/AbstractProcessor.hpp"
#include "StdStream.hpp"

using namespace std;

const uint8_t machine_code[] = {
	Arch::DeaDea16::_LOADACA8, // 0
	20, // 1
	Arch::DeaDea16::_STORAC8, // 2
	6, // 3
	0, // 4
	Arch::DeaDea16::_EXIT, // 5
	0, // 6
	0, // 7
	0, // 8
	0
};

int main(int argc, char *argv[])
{
	Io::sAbstractFwrite writer(new Io::StdStream("/home/metalhead33/memtest.raw",false));
	Psecom::Memory::sAbstractMemoryHandler mem(new Psecom::Memory::SharedMemoryAccess(machine_code,sizeof(machine_code)));
	Arch::DeaDea16::ProccessorType processor(Arch::DeaDea16::CastToAbstract(),mem,sf::microseconds(50));
	int i = processor.Run();
	std::dynamic_pointer_cast<Psecom::Memory::SharedMemoryAccess>(mem)->MemoryDump(writer);
	//Arch::DeaDea16::ProccessorType processor(Arch::DeaDea16::CastToAbstract(),static_pointer_cast<Psecom::Memory::AbstractMemoryHandler>(mem));
	return i;
}
