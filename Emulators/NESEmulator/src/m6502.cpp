#include "../include/m6502.h"
#include "../include/bus.h"

namespace nes 
{
	Nes6502::Nes6502()
	{

	}

	Nes6502::~Nes6502()
	{

	}

	uint8_t Nes6502::read(uint16_t a)
	{

		return bus->read(a, false);

	}

	void Nes6502::write(uint16_t a, uint8_t d)
	{
		bus->write(a, d);

	}


}




