#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_scancode.h>
#include <SDL3_image/SDL_image.h>
#include <cstdlib>
#include <glm/detail/qualifier.hpp>
#include <vector>
#include "gameobject.h"
#include "string"
#include <glm/glm.hpp>
#include <array>



struct SDLState {
    SDL_Window *window{};
    SDL_Renderer *renderer{};
    int width, height, logW, logH;
    const bool *keys{};

    SDLState(): keys(SDL_GetKeyboardState(nullptr))
    {

    }
};

const size_t LAYER_IDX_LEVEL{0};
const size_t LAYER_IDX_CHARACTERS{1};
const int MAP_ROWS{5};
const int MAP_COLS{50};
const int TILE_SIZE{32};

struct GameState {
    std::array<std::vector<GameObject>, 2> layers{};
    int playerIndex{};


    GameState() {
        playerIndex = 0;
        
    }

};

struct Resources {
    const int ANIM_PLAYER_IDLE{0};
    const int ANIM_PLAYER_RUN{1};
    std::vector<Animation> playerAnims{};
    SDL_Texture * textIdle{}, *textRun{}, *textGrass{}, *textGround{}, * textPanel{};

    std::vector<SDL_Texture *> textures{};

    SDL_Texture *loadTexture(SDL_Renderer *renderer,const std::string &filePath){
        SDL_Texture *tex = IMG_LoadTexture(renderer, filePath.c_str());
        SDL_SetTextureScaleMode(tex, SDL_SCALEMODE_NEAREST);
        textures.push_back(tex);
        return tex;

    };




    void load(SDLState &state){
        playerAnims.resize(5);
        playerAnims[ANIM_PLAYER_IDLE] = Animation(8, 1.6f);
        playerAnims[ANIM_PLAYER_RUN] =  Animation(4, 0.5f);

        textIdle = loadTexture(state.renderer, "data/idle.png");
        textRun = loadTexture(state.renderer, "data/run.png");
        textGrass = loadTexture(state.renderer, "data/tiles/grass.png");
        textGround = loadTexture(state.renderer, "data/tiles/ground.png");
        textPanel = loadTexture(state.renderer, "data/tiles/panel.png");

    }

    void unload(){
        for (SDL_Texture * tex : textures){
            SDL_DestroyTexture(tex);
        }
    }
    

};
void cleanUp(SDLState & state);

bool initialize(SDLState & state);

void drawObject(const SDLState &state, GameState &gs, GameObject &obj, float deltaTime);

void update(const SDLState & state, GameState &gs, Resources &res, GameObject &obj, 
        float deltaTime);


void createTile(const SDLState &state, GameState &gs, const Resources &res);

int main(int argc, char* argv[]) 
{
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


    GameState gs;
    createTile(state,gs,res);


    uint64_t prevTime{SDL_GetTicks()};

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

        //update all objects
        for (auto &layer : gs.layers){
            for (GameObject &obj : layer){

                update(state,gs,res,obj,deltaTime);
                if (obj.currentAnimation != 1){
                    obj.animations[obj.currentAnimation].step(deltaTime);
                }
            }
        }


        // handle movement

        SDL_SetRenderDrawColor(state.renderer, 25,25,25,255);

        SDL_RenderClear(state.renderer);

        for (auto &layer : gs.layers){
            for (GameObject &obj : layer){
                drawObject(state,gs,obj,deltaTime);
            }
        }




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

void drawObject(const SDLState &state, GameState &gs, GameObject &obj, float deltaTime){

        const float spriteSize{32};

        float srcX = obj.currentAnimation != -1 ? obj.animations[obj.currentAnimation]
            .currentFrame() * spriteSize : 0.f;
        SDL_FRect src {
            .x = srcX,
            .y = 0,
            .w = spriteSize, 
            .h = spriteSize 
        };

        SDL_FRect dest {
            .x = obj.position.x,
            .y = obj.position.y,
            .w = spriteSize, 
            .h = spriteSize 
        };

        SDL_FlipMode flipmode = obj.direction == -1 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
        SDL_RenderTextureRotated(state.renderer, obj.texture, &src, &dest,0,
                nullptr,flipmode);
}

void update(const SDLState & state, GameState &gs, Resources &res, GameObject &obj, 
        float deltaTime)
{
    if(obj.type == ObjectType::player)
    {
        float currentDirection{0};

        if(state.keys[SDL_SCANCODE_A])
        {
            currentDirection += -1;
        }

        if (state.keys[SDL_SCANCODE_D])
        {
            currentDirection += 1;
        }

        if (currentDirection)
        {
            obj.direction = currentDirection;
        }

        switch (obj.data.player.state)
        {
           case PlayerState::idle:
            {
                if(currentDirection)
                {
                    
                    obj.data.player.state = PlayerState::running;
                    obj.texture = res.textRun;
                    obj.currentAnimation = res.ANIM_PLAYER_RUN;
                }
                else 
                {
                    if(obj.velocity.x)
                    {
                        const float factor = obj.velocity.x > 0 ? -1.5f : 1.5f;
                        float amount = factor * obj.acceleration.x * deltaTime;
                        if(std::abs(obj.velocity.x) < std::abs(amount))
                        {
                            obj.velocity.x = 0;
                        }
                        else 
                        {
                            obj.velocity.x += amount;
                        }
                    }
                }
                break;
            }
           case PlayerState::running:
           {
               if(!currentDirection)
               {
                   obj.data.player.state = PlayerState::idle;
                   obj.texture = res.textIdle;
                   obj.currentAnimation = res.ANIM_PLAYER_IDLE;
               }
               break;
           }



        }


    obj.velocity += currentDirection * obj.acceleration * deltaTime;

    if (std::abs(obj.velocity.x) > obj.maxSpeedx)
    {
        obj.velocity.x = currentDirection * deltaTime;
    }


    obj.position += obj.velocity * deltaTime;

    }
}


void createTile(const SDLState &state, GameState &gs, const Resources &res)
{
    short map[MAP_ROWS][MAP_COLS] = {
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    };

    


    for (int r = 0; r < MAP_ROWS; r ++)
    {
        for (int c = 0; c < MAP_COLS; c++)
        {
            switch(map[r][c])
            {
                case 4:
                    {
                        GameObject player;
                        player.position = glm::vec2(
                                c * TILE_SIZE,
                                state.logH - (MAP_ROWS -r) * TILE_SIZE
                                );
                        player.type = ObjectType::player;
                        player.data.player = PlayerData();
                        player.texture = res.textIdle;
                        player.animations = res.playerAnims;
                        player.currentAnimation = res.ANIM_PLAYER_IDLE;
                        player.acceleration = glm::vec2(300, 0);
                        player.maxSpeedx= 100;
                        gs.layers[LAYER_IDX_CHARACTERS].push_back(player);

                        break;
                    }
            }
        }
    }


}
