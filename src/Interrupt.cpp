#include "Interrupt.hpp"
extern "C" {
#include "pthread.h"
}
namespace Psecom {
namespace Peripheria {


void Interrupt::InterruptTheState()
{
	handler->InterruptState(memstart,mempos,maskable);
}

void* Interrupt::ThreadInterrupt(void* p)
{
	static_cast<Interrupt*>(p)->InterruptTheState();
	return NULL;
}

void Interrupt::InterruptWrapper()
{
	if(own_thread) {
		pthread_t id;
		pthread_create(&id, NULL, ThreadInterrupt, this);
		pthread_join(id, NULL);
	}
	else InterruptTheState();
}

Interrupt::Interrupt(pAbstractInterruptHandler handle,bool maskability, bool threaded, size_t starter, size_t position)
{
	handler = handle;
	maskable = maskability;
	own_thread = threaded;
	memstart = starter;
	mempos = position;
}

}
}
