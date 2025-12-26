#pragma once


#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"
#include <SDL3/SDL_video.h>
#include <string>




class GameWindow{
    public:
        GameWindow(int w, int h, std::string name);
        bool shouldClose(){return }
    private:
        void initWindow();
        const int width{};
        const int height{};
        std::string windowName{};
        SDL_Window * window{};
};
