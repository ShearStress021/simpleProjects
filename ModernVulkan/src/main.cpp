#include <SDL3/SDL.h>
#include <cstdio>
int main(int argc, char* argv[]) {
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		std::fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
		return 1;

	}

	SDL_Window* window = SDL_CreateWindow(
			"Modern Vulkan + SDL3",
			800, 600,
			SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE

			);
	if (!window) {
		std::fprintf(stderr, "SDL_CreateWindow failed: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;

	}
	SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

	bool running = true;
	SDL_Event e;
	while (running) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_EVENT_QUIT) {
				running = false;

			}

		}
		SDL_Delay(16);

	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;

}


