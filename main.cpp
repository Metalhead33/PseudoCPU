#include <iostream>
#include <cstdio>
#include "include/AbstractMemcontainer.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	AbstractMemcontainer<uint8_t,uint8_t> abtest(128);
	std::cout << "Memory address: " << abtest.AccessMemory(0) << std::endl;
	std::cout << "Memory address at PC: " << abtest.AccessMemAtPC() << std::endl;
	std::cout << "Memory address at 127: " << abtest.AccessMemory(127) << std::endl;
    return 0;
}
