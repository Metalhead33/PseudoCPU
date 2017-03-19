#include <iostream>
#include <cstdio>
#include "include/Deadea8.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	//cout << "Hello World!" << endl;
	Fcom::Deadea8 computer(0);
	std::string save_path = "/home/metalhead33/memtest";
	uint8_t* memspace = (uint8_t*)computer.GetRegister()->memory_space;
	for(int i = 0;i < 255;++i) memspace[i] = 0;
	memspace[0] = Fcom::Deadea8::_LOADA;
	memspace[1] = 122;
	memspace[2] = Fcom::Deadea8::_STORP;
	memspace[3] = 8;
	memspace[4] = Fcom::Deadea8::_EXIT;
	memspace[5] = 0;
	computer.GetRegister()->AdjustPointer();
	if(computer.Run() != -1) {
	FILE* faile = fopen(save_path.c_str(),"wb");
	fwrite(computer.GetRegister()->memory_space,sizeof(char),computer.GetRegister()->memsize,faile);
	fclose(faile);
	printf("\nSuccess!\n");
	}
	else printf("\nFailure!\n");
    return 0;
}
