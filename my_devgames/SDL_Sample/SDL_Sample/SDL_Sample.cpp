#include "SDL_Sample.h"

using namespace std;

int main(int argc, char* argv[])
{
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		cerr << "SDL_Init failed: " << SDL_GetError() << endl;
		return 1;
	}

	SDL_Window* window = SDL_CreateWindow(
		"SDL Sample",
		800, 600,
		SDL_WINDOW_RESIZABLE
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
			if (e.type == SDL_EVENT_QUIT)
				running = false;
		}
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}