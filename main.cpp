#include <cstdio>
#include "StdStream.hpp"
#include <cstring>
#include <cstdio>

int main(void)
{
	timespec waitingTime;
	waitingTime.tv_nsec = 500;
	sAbstractFwrite writer = StdStream::createWriter("/tmp/ass");
	return 0;
}
