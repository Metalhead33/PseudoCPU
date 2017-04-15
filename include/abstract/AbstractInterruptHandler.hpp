#ifndef ABSTRACTINTERRUPTHANDLER_HPP
#define ABSTRACTINTERRUPTHANDLER_HPP
#include "Global.hpp"
namespace Psecom {
namespace Peripheria {

DEFINE_CLASS(AbstractInterruptHandler)

class AbstractInterruptHandler
{
public:
	virtual void InterruptState(size_t memstart, size_t mempos, bool maskability) = 0;
	//static void* Interruptor(void* p);
};

}
}

#endif // ABSTRACTINTERRUPTHANDLER_HPP
