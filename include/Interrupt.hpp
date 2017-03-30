#ifndef INTERRUPT_HPP
#define INTERRUPT_HPP
#include <stack>
#include "Global.hpp"

/*class Interrupt
{
public:
	Interrupt();
};*/

struct Interrupt
{
	size_t start;
	size_t cur_pos;
	bool maskable;
	Interrupt(size_t starter,bool masking) : start(starter),cur_pos(0),maskable(masking)
	{
	}
};

typedef std::stack<Interrupt> InterruptStack;
typedef std::shared_ptr<InterruptStack> InterruptQueue;


#endif // INTERRUPT_HPP
