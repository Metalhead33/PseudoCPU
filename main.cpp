#include <iostream>
#include <cstdio>
#include "include/DeaDea16.hpp"
#include "include/StdStream.hpp"

using namespace std;

const uint8_t assembly_code[] = {
	DeaDea16::_LoadAAC8, // 0
	16, // 1
	DeaDea16::_LoadAAR8, // 2
	24, // 3
	DeaDea16::_ADD, // 4
	DeaDea16::_LoadAAR8, // 5
	40, // 6
	DeaDea16::_BXOR, // 7
	DeaDea16::_IF, //8
	13, // 9
	0, // 10
	DeaDea16::_LoadAAC8, // 11
	32, // 12
	DeaDea16::_LoadAAR8, // 13
	20, // 14
	DeaDea16::_SUB, // 15
	DeaDea16::_StoreAC8, // 16
	24, // 17
	0, // 18
	DeaDea16::_EXIT, // 19
	0, // 20
	0, // 21
	0, // 22
	0, // 23
	0 // 24
};

int main(int argc, char *argv[])
{
	DeaDea16 deasys(assembly_code,sizeof(assembly_code));
	if(deasys.Run() != -1) {
	std::cout << "Success!!" << std::endl;
	StdStream filestream("/home/metalhead33/memtest.raw",false);
	deasys.MemoryDump(&filestream);
	filestream.close();
	}
	else std::cout << "Failure!" << std::endl;
    return 0;
}
