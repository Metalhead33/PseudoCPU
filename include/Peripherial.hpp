#ifndef PERIPHERIAL_HPP
#define PERIPHERIAL_HPP
#include "DirectMemoryAccess.hpp"
DEFINE_CLASS(Peripherial)

class Peripherial
{
private:
	sDirectMemoryAccess DMA;
public:
	Peripherial(sDirectMemoryAccess dirmemacc);
	sDirectMemoryAccess GetDMA();
	void SetDMA(sDirectMemoryAccess newDMA);
};

#endif // PERIPHERIAL_HPP
