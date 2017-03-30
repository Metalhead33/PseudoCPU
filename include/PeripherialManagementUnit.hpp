#ifndef PERIPHERIALMANAGEMENTUNIT_HPP
#define PERIPHERIALMANAGEMENTUNIT_HPP
#include "Peripherial.hpp"
#include <list>

class PeripherialManagementUnit
{
public:
	PeripherialManagementUnit();
private:
	std::list<Peripherial*> peripherials;
};

#endif // PERIPHERIALMANAGEMENTUNIT_HPP
