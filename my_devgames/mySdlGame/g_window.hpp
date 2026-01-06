#pragma once


#include "SDL3/SDL.h"
#include <string>




class GameWindow{
    public:
        GameWindow(int w, int h, std::string name);
        bool shouldClose(){return false; }
    private:
        void initWindow();
        const int width{};
        const int height{};
        std::string windowName{};
        SDL_Window * window{};
};
