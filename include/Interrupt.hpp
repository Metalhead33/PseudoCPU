#ifndef INTERRUPT_HPP
#define INTERRUPT_HPP
#include "abstract/AbstractInterruptHandler.hpp"
namespace Psecom {
namespace Peripheria {

class Interrupt
{
private:
	pAbstractInterruptHandler handler;
	bool maskable;
	bool own_thread;
	size_t memstart,mempos;
public:
	void InterruptTheState();
	static void* ThreadInterrupt(void* p);
	void InterruptWrapper();
	Interrupt(pAbstractInterruptHandler handle,bool maskability, bool threaded, size_t starter, size_t position);
};

}
}
#endif // INTERRUPT_HPP
