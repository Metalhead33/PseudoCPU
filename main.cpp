#include <iostream>
#include <cstdio>
#include "include/DeaDea16.hpp"
#include "include/StdStream.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	DeaDea16 deasys(64);
	uint8_t* storage = deasys.CastAccessMemAtPC<uint8_t>();
	storage[0] = DeaDea16::_LoadAAC8;
	storage[1] = 30;
	storage[2] = DeaDea16::_LoadAAR8;
	storage[3] = 40;
	storage[4] = DeaDea16::_ADD;
	storage[5] = DeaDea16::_StoreAC8;
	uint16_t* storage2 = reinterpret_cast<uint16_t*>(&storage[6]);
	*storage2 = 10;
	//storage[3] = 9;
	//storage[4] = 0;
	storage[8] = DeaDea16::_GOTO;
	storage2 = reinterpret_cast<uint16_t*>(&storage[9]);
	*storage2 = 20;
	storage[20] = DeaDea16::_EXIT;
	if(deasys.Run() != -1) {
	std::cout << "Success!!" << std::endl;
	StdStream filestream("/home/metalhead33/memtest.raw",false);
	deasys.MemoryDump(&filestream);
	filestream.close();
	}
	else std::cout << "Failure!" << std::endl;
    return 0;
}
