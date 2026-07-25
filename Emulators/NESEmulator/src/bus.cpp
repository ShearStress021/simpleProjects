#include "../include/bus.h"


namespace nes 
{
	NesBus::NesBus()
	{
		for(auto &i : ram) i =0x00;
		cpu.ConnectBus(this);
	}

	void NesBus::write(uint16_t addr, uint8_t data)
	{
		if(addr >= 0x0000 && addr <= 0xFFFF)
		{
			ram[addr] = data;
		}
	}

	uint8_t NesBus::read(uint16_t addr, bool bReadOnly)
	{
		if(addr >= 0x0000 && addr <= 0xFFFF)
			return ram[addr] ;
		return 0x00;
	}


	NesBus::~NesBus()
	{

	}


}


