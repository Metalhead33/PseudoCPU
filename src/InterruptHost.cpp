#include "include/InterruptHost.hpp"

Interrupt InterruptHost::PopInterrupt()
{
	Interrupt temp = IRQ->top();
	IRQ->pop();
	return temp;
}
bool InterruptHost::InterruptListIsEmpty()
{
	return IRQ->empty();
}
InterruptHost::InterruptHost()
	: IRQ(new InterruptStack)
{
	;
}
InterruptHost::~InterruptHost()
{
	;
}
size_t InterruptHost::IRQJump()
{
	if(IRQ->empty()) return original_post;
	else
	{
		Interrupt temp = PopInterrupt();
		return temp.start + temp.cur_pos;
	}
}
void InterruptHost::UpdateCurIRQ(size_t PC)
{
	if(!IRQ->empty())
	{
		IRQ->top().cur_pos = PC - IRQ->top().start;
	}
}
void InterruptHost::AddInterruptRequest(size_t startpos,bool maskability)
{
	while(!IRQ->top().maskable); // No adding of interrupts until the last masked interrupt has been resolved.
	IRQ->push(Interrupt(startpos,maskability));
}
