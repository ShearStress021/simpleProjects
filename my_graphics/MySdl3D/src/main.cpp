#include <SDL3/SDL.h>
#include <iostream>

int main(int argc, char* argv[])
{
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
		return 1;

	}

	SDL_Window* window = SDL_CreateWindow(
			"SDL Sample",
			800, 600,
			SDL_WINDOW_RESIZABLE

			);

	if (!window)
	{
		std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;

	}

	SDL_Event e;
	bool running = true;

	while (running)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_EVENT_QUIT)
				running = false;

		}

	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;

}


