#pragma once
#include <SDL3/SDL.h>
#include <iostream>
#include <cstdint>


class MainWindow {
	
	public:
		bool init();
		void run();
		void Error(const char* msg) const;
		
	private:
		SDL_Window * window = nullptr;
		std::uint16_t width{1280};
		std::uint16_t height{720};

};
