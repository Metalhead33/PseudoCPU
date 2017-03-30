#include "include/Peripherial.hpp"

Peripherial::Peripherial(sDirectMemoryAccess dirmemacc)
	: DMA(dirmemacc)
{
	;
}
sDirectMemoryAccess Peripherial::GetDMA()
{
	return DMA;
}
void Peripherial::SetDMA(sDirectMemoryAccess newDMA)
{
	DMA = newDMA;
}
