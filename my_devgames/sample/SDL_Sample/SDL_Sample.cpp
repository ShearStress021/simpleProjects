#include "SDL_Sample.h"

using namespace std;

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cerr << "SDL_Init failed: " << SDL_GetError() << endl;
		return 1;
	}

	SDL_Window* window = SDL_CreateWindow(
		"SDL Sample",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		800, 600,
		SDL_WINDOW_SHOWN
	);

	if (!window)
	{
		cerr << "SDL_CreateWindow failed: " << SDL_GetError() << endl;
		SDL_Quit();
		return 1;
	}

	SDL_Event e;
	bool running = true;

	while (running)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				running = false;
		}
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}