#pragma once
#include <cstdint>
#include <array>
#include "m6502.h"




namespace nes
{
	class NesBus {

		public:
			NesBus();
			~NesBus();
		public:
			Nes6502 cpu;
			std::array<uint8_t, 64 * 1024> ram{};


		public:
			void write(uint16_t addr, uint8_t data);
			uint8_t read(uint16_t addr, bool bReadOnly = false) ;



	};



}
