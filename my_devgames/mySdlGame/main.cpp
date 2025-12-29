
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>
#include <vector>
#include "animation.h"
#include "string"
#include <glm/glm.hpp>

struct SDLState {
    SDL_Window *window;
    SDL_Renderer *renderer;

    int width, height, logW, logH;
};


struct Resources {
    const int ANIM_PLAYER_IDLE{0};
    std::vector<Animation> playerAnims;
    SDL_Texture * textIdle;

    std::vector<SDL_Texture *> textures;

    SDL_Texture *loadTexture(SDL_Renderer *renderer,const std::string &filePath){
        SDL_Texture *tex = IMG_LoadTexture(renderer, filePath.c_str());
        SDL_SetTextureScaleMode(tex, SDL_SCALEMODE_NEAREST);
        textures.push_back(tex);
        return tex;

    };




    void load(SDLState &state){
        playerAnims.resize(5);
        playerAnims[ANIM_PLAYER_IDLE] = Animation(8, 1.6f);

        textIdle = loadTexture(state.renderer, "data/idle.png");
    }

    void unload(){
        for (SDL_Texture * tex : textures){
            SDL_DestroyTexture(tex);
        }
    }
    

};
void cleanUp(SDLState & state);

bool initialize(SDLState & state);

int main(int argc, char* argv[]) {
    SDLState state;
    bool running = true;


    state.width = 1600;
    state.height = 900;
    state.logW = 640;
    state.logH = 320;


    if (!initialize(state)){
        return 1;
    }
    
    Resources res;
    res.load(state);


    const bool *keys = SDL_GetKeyboardState(nullptr);


    float playerX{150};
    
    const float floor =state.logH;

    uint64_t prevTime{SDL_GetTicks()};

    float flipH {false};



    while (running){


        uint64_t nowTime{SDL_GetTicks()};

        float deltaTime = (nowTime - prevTime) / 1000.f;
        SDL_Event event{0};
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT:
                    {
                        running = false;
                        break;
                    }
                case SDL_EVENT_WINDOW_RESIZED:
                    {
    
                        state.width = event.window.data1;
                        state.height = event.window.data2;
                        break;
                    }
            }
        }


        // handle movement
        //
        float moveAmount{0};

        if (keys[SDL_SCANCODE_A]){
            moveAmount += -75.f;
            flipH = true;
        }

        if (keys[SDL_SCANCODE_D]){
            moveAmount += 75.f;
            flipH = false;

        }

        playerX += moveAmount * deltaTime;


        SDL_SetRenderDrawColor(state.renderer, 25,25,25,255);

        SDL_RenderClear(state.renderer);


        const float spriteSize{32};
        SDL_FRect src {
            .x = 0,
            .y = 0,
            .w = spriteSize, 
            .h = spriteSize 
        };

        SDL_FRect dest {
            .x = playerX,
            .y = floor - spriteSize,
            .w = spriteSize, 
            .h = spriteSize 
        };
        SDL_RenderTextureRotated(state.renderer, 
                res.textIdle, &src, &dest,0,
                nullptr, (flipH) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);


        SDL_RenderPresent(state.renderer);

        prevTime = nowTime;
        // Do game logic, present a frame, etc.
    }
    res.unload();
    cleanUp(state);
    return 0;
}


bool initialize(SDLState & state){


    bool initSuccess{true};

    if(!SDL_Init(SDL_INIT_VIDEO)){
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", 
                "Error initilizing SDL3", nullptr);

        initSuccess = false;
    };              // Initialize SDL3

    // Create an application window with the following settings:
    state.window = SDL_CreateWindow(
        "SDL3 Demo window",                  // window title
        state.width,                               // width, in pixels
        state.height,                               // height, in pixels
        SDL_WINDOW_RESIZABLE// flags - see below
    );

    // Check that the window was successfully created
    if (!state.window)  {
        // In the case that the window could not be made...
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"Error",
                "Error creating  window", state.window);
        cleanUp(state);

        initSuccess = false;
    
    }

    state.renderer = SDL_CreateRenderer(state.window,nullptr);

    if(!state.renderer){
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", 
                "Error creating renderer", state.window);
        cleanUp(state);
        initSuccess = false;
    }
    
    SDL_SetRenderLogicalPresentation(state.renderer,state.logW, state.logH, 
            SDL_LOGICAL_PRESENTATION_LETTERBOX);

    return initSuccess;

}
void cleanUp(SDLState& state){
    SDL_DestroyRenderer(state.renderer);
    SDL_DestroyWindow(state.window);
    SDL_Quit();
}
