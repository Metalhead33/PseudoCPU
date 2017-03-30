#ifndef INTERRUPTHOST_HPP
#define INTERRUPTHOST_HPP
#include "Interrupt.hpp"

class InterruptHost
{
private:
	InterruptQueue IRQ;
	size_t original_post;
public:
	Interrupt PopInterrupt();
	bool InterruptListIsEmpty();
	InterruptHost();
	virtual ~InterruptHost();
	virtual void AdjustPCForIRQ() = 0;

	size_t IRQJump();
	void UpdateCurIRQ(size_t PC);
	void AddInterruptRequest(size_t startpos,bool maskability);

	size_t GetOriginalPost() const { return original_post; }
	void SetOriginalPost(size_t setto) { original_post = setto; }
};

#endif // INTERRUPTHOST_HPP
