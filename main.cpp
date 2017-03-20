#include <iostream>
#include <cstdio>
//#include "include/AbstractMemcontainer.hpp"
#include "include/AbstractProcessor.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	AbstractProcessor<uint8_t,uint8_t> abtest(128);
	// Memory access test
	std::cout << "Memory address: " << abtest.AccessMemory(0) << std::endl;
	std::cout << "Memory address at PC: " << abtest.AccessMemAtPC() << std::endl;
	std::cout << "Memory address at 127: " << abtest.AccessMemory(127) << std::endl;

	// Memory writing and reading test
	uint8_t* datapointer = abtest.CastAccessMemory<uint8_t>(0);
	datapointer[0] = 0x81;
	datapointer[1] = 0x82;
	datapointer[2] = 0x83;
	datapointer[3] = 0x84;
	std::cout << "uint8_t[" << abtest.AccessMemory(0) << "] = " << std::dec << (int)datapointer[0] << std::endl;
	std::cout << "uint8_t[" << abtest.AccessMemory(1) << "] = " << std::dec << (int)datapointer[1] << std::endl;
	std::cout << "uint8_t[" << abtest.AccessMemory(2) << "] = " << std::dec << (int)datapointer[2] << std::endl;
	std::cout << "uint8_t[" << abtest.AccessMemory(3) << "] = " << std::dec << (int)datapointer[3] << std::endl;
	float* floatpointer = abtest.CastAccessMemory<float>(0);
	std::cout << "uint8_t[" << abtest.AccessMemory(0) << "] = " << floatpointer[0] << std::endl;
    return 0;
}
