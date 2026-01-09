#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <cstdio>
#include <cstdlib>
#include <glm/ext/vector_float2.hpp>
#include <string>
#include <vector>
#include "gameobject.h"
#include "string"
#include <glm/glm.hpp>
#include <iostream>
#include <array>



struct SDLState {
    SDL_Window *window{};
    SDL_Renderer *renderer{};
    MIX_Mixer *mixer{};
    int width, height, logW, logH;
    const bool *keys{};
    bool fullScreen{};

    SDLState(): keys(SDL_GetKeyboardState(nullptr))
    {
        fullScreen = false;

    }
};

const size_t LAYER_IDX_LEVEL{0};
const size_t LAYER_IDX_CHARACTERS{1};
const int MAP_ROWS{5};
const int MAP_COLS{50};
const int TILE_SIZE{32};

struct GameState {
    std::array<std::vector<GameObject>, 2> layers{};
    std::vector<GameObject> backgroundTiles{};
    std::vector<GameObject> foregroundTiles{};
    std::vector<GameObject> bullets{};
    int playerIndex{};
    SDL_FRect mapViewport{};
    float bg2Scroll, bg3scroll, bg4scroll;
    bool debugMode{};


    GameState(const SDLState &state) {
        playerIndex = -1;

        mapViewport = SDL_FRect{
            .x =0, .y=0,
            .w=static_cast<float>(state.logW),
            .h =static_cast<float>(state.logH)
        };
        bg2Scroll = bg3scroll = bg4scroll = 0;
        debugMode = false;
        
    }
    

    GameObject &player(){return layers[LAYER_IDX_CHARACTERS][playerIndex];}


};

struct Resources {
    const int ANIM_PLAYER_IDLE{0};
    const int ANIM_PLAYER_RUN{1};
    const int ANIM_PLAYER_SLIDE{2};
    const int ANIM_PLAYER_SHOOT{3};
    const int ANIM_PLAYER_SLIDE_SHOOT{4};
    std::vector<Animation> playerAnims{};
    // bullets animations
    const int ANIM_BULLET_MOVING{0};
    const int ANIM_BULLET_HIT{1};
    std::vector<Animation> bulletAnims{};

    const int ANIM_ENEMY{0};
    const int ANIM_ENEMY_HIT{1};
    const int ANIM_ENEMY_DIE{2};
    std::vector<Animation> enemyAnims{};


    SDL_Texture * textPanel , *textIdle{}, *textRun{}, *textGrass{}, 
                *textGround{},*textBrick{}, *textSlide{}, *textBg1, *textBg2{}, 
                *textBg3{}, *textBg4{}, *textBullet{}, *textBulletHit{}, *textShoot{},
                *textRunShoot{}, *textSlideShoot{}, *textEnemy{}, *textEnemyHit{}, *textEnemyDie{};

    std::vector<SDL_Texture *> textures{};

    std::vector<MIX_Audio *> chucks{};
    MIX_Audio *chuckShoot{}, *chuckShootHit{}, *chuckEnemyHit{};

    MIX_Audio *musicMain{};

    SDL_Texture *loadTexture(SDL_Renderer *renderer,const std::string &filePath){
        SDL_Texture *tex = IMG_LoadTexture(renderer, filePath.c_str());
        SDL_SetTextureScaleMode(tex, SDL_SCALEMODE_NEAREST);
        textures.push_back(tex);
        return tex;

    };


    MIX_Audio* loadChunk(MIX_Mixer *mixer, const std::string& filename)
    {
        MIX_Audio * chunk = MIX_LoadAudio(mixer,filename.c_str(),false);
        chucks.push_back(chunk);
        return chunk;
        
    }




    void load(SDLState &state){
        playerAnims.resize(5);
        playerAnims[ANIM_PLAYER_IDLE] = Animation(8, 1.6f);
        playerAnims[ANIM_PLAYER_RUN] =  Animation(4, 0.5f);
        playerAnims[ANIM_PLAYER_SLIDE] = Animation(1, 1.0f);
        playerAnims[ANIM_PLAYER_SHOOT] = Animation(4, .5f);
        playerAnims[ANIM_PLAYER_SLIDE_SHOOT] = Animation(4, 0.5f);


        //bullet Animation
        //
        bulletAnims.resize(2);
        bulletAnims[ANIM_BULLET_MOVING] = Animation(1,1.15f);
        bulletAnims[ANIM_BULLET_HIT] = Animation(4,0.15f);

        enemyAnims.resize(3);
        enemyAnims[ANIM_ENEMY] = Animation(8, 1.0f);
        enemyAnims[ANIM_ENEMY_HIT] = Animation(8, 1.f);
        enemyAnims[ANIM_ENEMY_DIE] = Animation(18, 2.f);
        


        textIdle = loadTexture(state.renderer, "data/idle.png");
        textRun = loadTexture(state.renderer, "data/run.png");
        textSlide = loadTexture(state.renderer, "data/slide.png");
        textGrass = loadTexture(state.renderer, "data/tiles/grass.png");
        textGround = loadTexture(state.renderer, "data/tiles/ground.png");
        textPanel = loadTexture(state.renderer, "data/tiles/panel.png");
        textBrick = loadTexture(state.renderer, "data/tiles/brick.png");
        textShoot = loadTexture(state.renderer, "data/shoot.png");
        textSlideShoot = loadTexture(state.renderer, "data/slide_shoot.png");
        textRunShoot = loadTexture(state.renderer, "data/shoot_run.png");


        // Enemy
        textEnemy = loadTexture(state.renderer, "data/enemy.png");
        textEnemyHit = loadTexture(state.renderer, "data/enemy_hit.png");
        textEnemyDie = loadTexture(state.renderer, "data/enemy_die.png");
        


        //background
        textBg1 = loadTexture(state.renderer, "data/bg/bg_layer1.png");
        textBg2 = loadTexture(state.renderer, "data/bg/bg_layer2.png");
        textBg3 = loadTexture(state.renderer, "data/bg/bg_layer3.png");
        textBg4 = loadTexture(state.renderer, "data/bg/bg_layer4.png");

        //bullets
        //
        textBullet = loadTexture(state.renderer, "data/bullet.png");
        textBulletHit = loadTexture(state.renderer,"data/bullet_hit.png");

        // audio
        chuckShoot = loadChunk(state.mixer, "data/audio/shoot.wav");
        chuckShootHit = loadChunk(state.mixer, "data/audio/shoot_hit.wav");
        chuckEnemyHit = loadChunk(state.mixer, "data/audio/enemy_hit.wav");

        musicMain = MIX_LoadAudio(state.mixer, "data/audio/Juhani Junkala [Retro Game Music Pack] Level 1.mp3", false);


    }

    void unload(){
        for (SDL_Texture * tex : textures){
            SDL_DestroyTexture(tex);
        }

        for (MIX_Audio * chuck : chucks)
        {
            MIX_DestroyAudio(chuck);
        }

        MIX_DestroyAudio(musicMain);
    }
    

};
void cleanUp(SDLState & state);

bool initialize(SDLState & state);

void drawObject(const SDLState &state, GameState &gs, GameObject &obj,float width, float height, float deltaTime);

void update(const SDLState & state, GameState &gs, Resources &res, GameObject &obj, 
        float deltaTime);


void createTile(const SDLState &state, GameState &gs, const Resources &res);


void checkCollision(const SDLState &state, GameState &gs, Resources &res, GameObject &a 
        , GameObject &b, float deltaTime);



void handleKeyInput(const SDLState &state, GameState &gs, GameObject &obj, 
        SDL_Scancode key, bool keyDown);

void drawParalaxBackGround(SDL_Renderer *renderer, SDL_Texture *texture,
        float xVelocity, float &scrollPos, float scrollFactor, float deltaTime);

int main(int argc, char* argv[]) 
{
    SDLState state;
    bool running = true;


    state.width = 1600;
    state.height = 900;
    state.logW = 640;
    state.logH = 320;


    if (!initialize(state)){
        return 1; }
    
    Resources res;
    res.load(state);


    GameState gs(state);
    createTile(state,gs,res);


    uint64_t prevTime{SDL_GetTicks()};

    MIX_PlayAudio(state.mixer, res.musicMain);

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

                case SDL_EVENT_KEY_DOWN:
                    {
                        handleKeyInput(state,gs,gs.player(),event.key.scancode,true);
                        break;
                    }
                case SDL_EVENT_KEY_UP:
                    {
                        handleKeyInput(state,gs,gs.player(),event.key.scancode,false);
                        if (event.key.scancode == SDL_SCANCODE_F12)
                        {
                            gs.debugMode = !gs.debugMode;
                        }
                        else if (event.key.scancode == SDL_SCANCODE_F11)
                        {
                            state.fullScreen =! state.fullScreen;
                            SDL_SetWindowFullscreen(state.window,state.fullScreen);
                        }
                        break;
                    }
            }

        }

        //update all objects
        for (auto &layer : gs.layers){
            for (GameObject &obj : layer){

                update(state,gs,res,obj,deltaTime);
            }
        }

        for(GameObject &bullet : gs.bullets)
        {
           update(state,gs,res,bullet,deltaTime);

        }


        // handle movement

        gs.mapViewport.x = (gs.player().position.x + TILE_SIZE /2.f) -
            gs.mapViewport.w / 2.f;


        SDL_SetRenderDrawColor(state.renderer, 25,25,25,255);

        SDL_RenderClear(state.renderer);


        // draw backgrounds
        SDL_RenderTexture(state.renderer,res.textBg1,nullptr,nullptr) ;

        drawParalaxBackGround(state.renderer, res.textBg4, gs.player().velocity.x,
                gs.bg2Scroll,0.075f,deltaTime);
        drawParalaxBackGround(state.renderer, res.textBg3, gs.player().velocity.x,
                gs.bg2Scroll,0.15f,deltaTime);
        drawParalaxBackGround(state.renderer, res.textBg2, gs.player().velocity.x,
                gs.bg2Scroll,0.3f,deltaTime);


        for (GameObject &obj: gs.backgroundTiles)
        {
            SDL_FRect dst{
                .x = obj.position.x -gs.mapViewport.x,
                .y = obj.position.y,
                .w = static_cast<float>(obj.texture->w),
                .h = static_cast<float>(obj.texture->h)
                };

            SDL_RenderTexture(state.renderer, obj.texture, nullptr, &dst);

        }




        for (auto &layer : gs.layers){
            for (GameObject &obj : layer){
                drawObject(state,gs,obj,TILE_SIZE, TILE_SIZE,deltaTime);
            }
        }



        for (auto & bullet : gs.bullets)
        {
            if (bullet.data.bullet.state != BulletState::inactive)
            {
                drawObject(state, gs,bullet,bullet.collider.w, bullet.collider.h, deltaTime);
            }
        }
        for (GameObject &obj: gs.foregroundTiles)
        {
            SDL_FRect dst{
                .x = obj.position.x - gs.mapViewport.x,
                .y = obj.position.y,
                .w = static_cast<float>(obj.texture->w),
                .h = static_cast<float>(obj.texture->h)
                };

            SDL_RenderTexture(state.renderer, obj.texture, nullptr, &dst);

        }

        if (gs.debugMode)
        {
            SDL_SetRenderDrawColor(state.renderer, 255,255,255,255);
            std::string result = "S :";
            result.append(std::to_string(static_cast<int>(gs.player().data.player.state)));
            result.append(" B: ");
            result.append(std::to_string(gs.bullets.size()));
            result.append(" G: ");
            result.append(std::to_string(gs.player().grounded));
            SDL_RenderDebugText(state.renderer, 5,5, result.c_str());

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
                    //
    if (!MIX_Init()){
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", 
                "Error initilizing MIXER", nullptr);

        initSuccess = false;

    }

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
    SDL_SetRenderVSync(state.renderer,1);
    
    SDL_SetRenderLogicalPresentation(state.renderer,state.logW, state.logH, 
            SDL_LOGICAL_PRESENTATION_LETTERBOX);

    state.mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);
    if(!state.mixer)
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", 
                "Error Loading Audio", state.window);
        cleanUp(state);
        initSuccess = false;
        
    }

    return initSuccess;

}
void cleanUp(SDLState& state){
    SDL_DestroyRenderer(state.renderer);
    SDL_DestroyWindow(state.window);
    MIX_DestroyMixer(state.mixer);
    SDL_Quit();
}

void drawObject(const SDLState &state, GameState &gs, GameObject &obj, float width, float height, float deltaTime){


        float srcX = obj.currentAnimation != -1 ? obj.animations[obj.currentAnimation]
            .currentFrame()  * width: (obj.spriteFrame - 1) * width ;

        SDL_FRect src {
            .x = srcX,
            .y = 0,
            .w = width, 
            .h = height 
        };

        SDL_FRect dest {
            .x = obj.position.x -gs.mapViewport.x,
            .y = obj.position.y,
            .w = width, 
            .h = height 
        };

        SDL_FlipMode flipmode = obj.direction == -1 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
        if (!obj.shouldFlash){

            SDL_RenderTextureRotated(state.renderer, obj.texture, &src, &dest,0,
                    nullptr,flipmode);
        }
        else
        {
            SDL_SetTextureColorModFloat(obj.texture, 2.5f, 1.0f, 1.0f);

            SDL_RenderTextureRotated(state.renderer, obj.texture, &src, &dest,0,
                    nullptr,flipmode);
            SDL_SetTextureColorModFloat(obj.texture, 1.0f, 1.0f, 1.0f);


            if (obj.flashTimer.step(deltaTime))
            {
                obj.shouldFlash = false;
            }
        }

        

        if (gs.debugMode)
        {
            SDL_FRect rectA {
                .x = obj.position.x + obj.collider.x -gs.mapViewport.x,
                .y = obj.position.y + obj.collider.y,
                .w = obj.collider.w, 
                .h = obj.collider.h 
            };

            SDL_SetRenderDrawBlendMode(state.renderer, SDL_BLENDMODE_BLEND);
            SDL_SetRenderDrawColor(state.renderer, 255, 0,0,150);
            SDL_RenderFillRect(state.renderer, &rectA);
            SDL_SetRenderDrawBlendMode(state.renderer, SDL_BLENDMODE_NONE);


        }
}

void update(const SDLState & state, GameState &gs, Resources &res, GameObject &obj, 
        float deltaTime) 
{
    if (obj.currentAnimation != -1){
        obj.animations[obj.currentAnimation].step(deltaTime);
    }
    if (obj.dynamic && !obj.grounded)
    {
        obj.velocity += glm::vec2(0, 500) * deltaTime;
    }


    float currentDirection{0};

    if(obj.type == ObjectType::player)
    {

        if(state.keys[SDL_SCANCODE_A])
        {
            currentDirection += -1;
        }
        if (state.keys[SDL_SCANCODE_D])
        {
            currentDirection += 1;
        }


        Timer &weaponTimer = obj.data.player.weaponTimer;
        weaponTimer.step(deltaTime);

        const auto handleShooting = [&state, &gs, &res, &obj, &weaponTimer](
                SDL_Texture *tex, SDL_Texture *shootTex, int animIndex, 
                int shootAnimIndex)
        {

            if (state.keys[SDL_SCANCODE_J])
            {

                obj.texture = shootTex;
                obj.currentAnimation = shootAnimIndex;
                if (weaponTimer.isTimeout()){
                    weaponTimer.reset();
                    GameObject bullet;
                    bullet.data.bullet = BulletData();
                    bullet.type = ObjectType::bullet;
                    bullet.direction = gs.player().direction;
                    bullet.texture = res.textBullet;
                    bullet.currentAnimation = res.ANIM_BULLET_MOVING;
                    bullet.collider = SDL_FRect{
                        .x = 0, .y = 0,
                        .w = static_cast<float>(res.textBullet->w),
                        .h = static_cast<float>(res.textBullet->h),
                    };

                    const int yVariation{40};
                    const float yVelocity = SDL_rand(yVariation) - yVariation/2.f;
                    bullet.velocity = glm::vec2(
                            obj.velocity.x + 600.f * obj.direction,
                            yVelocity 
                            );
                    bullet.maxSpeedx = 1000.f;
                    bullet.animations = res.bulletAnims;
                    const float left{4};
                    const float right{24};
                    const float t = (obj.direction + 1) / 2.0f;
                    const float xOffset = left + right * t;
                    bullet.position = glm::vec2(
                            obj.position.x  + xOffset,
                            obj.position.y + TILE_SIZE/2.0f
                            );
                    bool foundInactive = false;

                    for (int i = 0; i < gs.bullets.size() && !foundInactive; i++)
                    {
                        if (gs.bullets[i].data.bullet.state == BulletState::inactive)
                        {
                            foundInactive = true;
                            gs.bullets[i] = bullet;
                        }
                    }
                    if (!foundInactive)
                    {
                        gs.bullets.push_back(bullet);

                    }
                    MIX_PlayAudio(state.mixer, res.chuckShoot);
                }
                
            }
            else {
                obj.texture = tex;
                obj.currentAnimation = animIndex;
            }

        };
        switch (obj.data.player.state)
        {
           case PlayerState::idle:
            {
                if(currentDirection)
                {
                    
                    obj.data.player.state = PlayerState::running;

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
                handleShooting(res.textIdle, res.textShoot,res.ANIM_PLAYER_IDLE, res.ANIM_PLAYER_SHOOT);
                obj.texture = res.textIdle;
                obj.currentAnimation = res.ANIM_PLAYER_IDLE;
                break;
            }
           case PlayerState::running:
           {
               if(!currentDirection)
               {
                   obj.data.player.state = PlayerState::idle;
               }   
               if (obj.velocity.x * obj.direction < 0 && obj.grounded)
               {
                   handleShooting(res.textSlide, res.textSlideShoot, res.ANIM_PLAYER_SLIDE_SHOOT, 
                           res.ANIM_PLAYER_SLIDE_SHOOT);
               }
               else
               {
                   handleShooting(res.textRun,res.textRunShoot, res.ANIM_PLAYER_RUN,
                           res.ANIM_PLAYER_RUN);
                    obj.texture = res.textRun;
                    obj.currentAnimation = res.ANIM_PLAYER_RUN;
               }
               break;
           }
           case PlayerState::jumping:
           {
               handleShooting(res.textRun, res.textRunShoot,res.ANIM_PLAYER_RUN, res.ANIM_PLAYER_RUN);
               break;
           }
        }

    }

    else if(obj.type == ObjectType::bullet)
    {

        switch(obj.data.bullet.state)
        {
            case BulletState::moving:
                {

                    if(obj.position.x - gs.mapViewport.x < 0 || obj.position.x - gs.mapViewport.x > state.logW || 
                            obj.position.y - gs.mapViewport.y < 0 || obj.position.y - gs.mapViewport.y > state.logH)

                    {
                        obj.data.bullet.state = BulletState::inactive;
                    }
                    
                    break;
                }

            case BulletState::colliding:
                {
                    if(obj.animations[obj.currentAnimation].isDone())
                    {
                        obj.data.bullet.state = BulletState::inactive;
                    }
                    break;
                }
        }
    }
    else if (obj.type == ObjectType::enemy)
    {
        EnemyData &d = obj.data.enemy;
        switch(d.state)
        {
            case EnemyState::shambling:
                {
                    glm::vec2 playerDir = gs.player().position - obj.position;
                    if (glm::length(playerDir) < 100)
                    {
                        currentDirection = playerDir.x < 0 ? -1 : 1;
                        obj.acceleration = glm::vec2(30, 0);
                    }
                    else 
                    {
                        obj.acceleration = glm::vec2(0);
                        obj.velocity.x = 0;
                    }
                    break;
                }
            case EnemyState::damage:
                {
                    if (obj.data.enemy.damagedTimer.step(deltaTime))
                    {
                        obj.data.enemy.state = EnemyState::shambling;
                        obj.texture = res.textEnemy;
                        obj.currentAnimation = res.ANIM_ENEMY;
                    }
                    break;
                }
            case EnemyState::dead:
                {
                    obj.velocity.x = 0;
                    if (obj.currentAnimation != -1 && obj.animations[obj.currentAnimation].isDone())
                    {
                        
                        obj.currentAnimation = -1;
                        obj.spriteFrame = 18;
                         
                    }
                    break;
                }
        }
    }
    if (currentDirection)
    {
        obj.direction = currentDirection;
    }
    obj.velocity += currentDirection * obj.acceleration * deltaTime;

    if (std::abs(obj.velocity.x) > obj.maxSpeedx)
    {
        obj.velocity.x = currentDirection * deltaTime;
    }
    obj.position += obj.velocity * deltaTime;

    bool foundGround = false;
    for (auto &layer: gs.layers)
    {
        for(GameObject &objB: layer)
        {
            if(&obj != &objB)
            {


                checkCollision(state,gs,res,obj,objB,deltaTime);
           


                if (objB.type == ObjectType::level)
                {
                // grounded sensor
                    SDL_FRect sensor {
                        .x = obj.position.x + obj.collider.x,
                        .y = obj.position.y + obj.collider.y + obj.collider.h,
                        .w = obj.collider.w,
                        .h = 1 
                    };
                    SDL_FRect rectB{
                        .x = objB.position.x + objB.collider.x,
                        .y = objB.position.y + objB.collider.y,
                        .w = objB.collider.w,
                        .h = objB.collider.h 
                    };

                    SDL_FRect rectC {
                        0
                    };
                    if(SDL_GetRectIntersectionFloat(&sensor, &rectB, &rectC))
                    {
                        foundGround = true;
                    }


                }

            
            }
            
        }

    }
    if(obj.grounded != foundGround)
    {
        obj.grounded = foundGround;

        if (foundGround && obj.type == ObjectType::player)
        {
            obj.data.player.state = PlayerState::running;
        }
    }
}


void collistionResponse(const SDLState &state, GameState &gs, Resources &res, 
        const SDL_FRect &rectA, const SDL_FRect &rectB, const SDL_FRect &rectC,
        GameObject &objA, GameObject &objB, float deltaTime)

{
    

    const auto genericResponse = [&]()
    {
        if(rectC.w < rectC.h)
        {
            if (objA.velocity.x > 0)
            {
                objA.position.x -= rectC.w;
            }
            else if(objA.velocity.x < 0)
            {
                objA.position.x += rectC.w;

            
            }

            objA.velocity.x = 0;

        }
        else 
        {

            if (objA.velocity.y > 0)
            {
                objA.position.y -= rectC.h;
            }
            else if(objA.velocity.y < 0)
            {
                objA.position.y += rectC.h;
            }

            objA.velocity.y = 0;

        }

    };
    if(objA.type == ObjectType::player)
    {
        switch(objB.type)
        {
            case ObjectType::level:
                {
                    genericResponse();
                    break;
                }
            case ObjectType::enemy:
                {
                    if (objB.data.enemy.state != EnemyState::dead)
                    {
                        objA.velocity = glm::vec2(100, 0) * -objA.direction;
                    }
                    break;
                }
            
        }

    }
    else if (objA.type == ObjectType::bullet)
    {
        bool passThrough{false};
        switch (objA.data.bullet.state) {
            case BulletState::moving:
                {
                    switch(objB.type){
                        case ObjectType::level:
                            {
                                MIX_PlayAudio(state.mixer, res.chuckShootHit);
                                break;
                            }
                        case ObjectType::enemy:
                            {
                                EnemyData &d = objB.data.enemy;
                                if (d.state != EnemyState::dead)
                                {
                                    objB.direction = -objA.direction;
                                    objB.shouldFlash = true;
                                    objB.flashTimer.reset();
                                    objB.texture = res.textEnemyHit;
                                    objB.currentAnimation = res.ANIM_ENEMY_HIT;
                                    d.state = EnemyState::damage;
                                    d.healthPoints -= 10;
                                    if (d.healthPoints <= 0)
                                    {
                                        d.state = EnemyState::dead;
                                        objB.texture = res.textEnemyDie;
                                        objB.currentAnimation = res.ANIM_ENEMY_DIE;
                                    }
                                    MIX_PlayAudio(state.mixer, res.chuckEnemyHit);

                                }
                                else {

                                    passThrough = true;
                                
                                }
                                break;


                            }
                    }
                    if (!passThrough)
                    {
                        genericResponse();
                        objA.velocity *= 0;
                        objA.data.bullet.state = BulletState::colliding;
                        objA.texture = res.textBulletHit;
                        objA.currentAnimation = res.ANIM_BULLET_HIT;

                    }
                    break;

                }
        }
    }
    else if (objA.type == ObjectType::enemy)
    {
        genericResponse();
    }
}
void checkCollision(const SDLState &state, GameState &gs, Resources &res, GameObject &a 
        , GameObject &b, float deltaTime)
{
    SDL_FRect rectA {
        .x = a.position.x + a.collider.x,
        .y = a.position.y + a.collider.y,
        .w = a.collider.w,
        .h = b.collider.h,

    };
    SDL_FRect rectB {
        .x = b.position.x + b.collider.x,
        .y = b.position.y + b.collider.y,
        .w = b.collider.w,
        .h = b.collider.h,

    };
    SDL_FRect rectC {0};

    
    if (SDL_GetRectIntersectionFloat(&rectA, &rectB, &rectC))
    {
        
        collistionResponse(state, gs, res, rectA, rectB, rectC, a, b,deltaTime);
    }

   


    
}


void createTile(const SDLState &state, GameState &gs, const Resources &res)
{
    short map[MAP_ROWS][MAP_COLS] = {
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,4,0,0,0,0,0,0,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,2,0,0,0,0,0,0,3,2,2,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,2,2,0,0,0,0,3,2,2,2,2,2,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    };
    short foreground[MAP_ROWS][MAP_COLS] = {
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
5,0,0,0,0,0,0,0,5,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    };
    short background[MAP_ROWS][MAP_COLS] = {
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    };


    const auto loadMap = [&state, &res, &gs](short layer[MAP_ROWS][MAP_COLS])
    {
        const  auto createObject = [&state](int r, int c, SDL_Texture *tex, ObjectType type) 
        {
            GameObject o;
            o.position = glm::vec2(c * TILE_SIZE, state.logH - (MAP_ROWS - r) * TILE_SIZE);
            o.type = type; 
            o.collider = {.x =0, .y=0,.w=TILE_SIZE,.h=TILE_SIZE};
            o.texture = tex;
            return  o;
        };
        for (int r = 0; r < MAP_ROWS; r ++)
        {
            for (int c = 0; c < MAP_COLS; c++)
            {
                switch(layer[r][c])
                {
                    case 1:
                        {

                            GameObject o = createObject(r,c,res.textGround, ObjectType::level);
                            gs.layers[LAYER_IDX_LEVEL].push_back(o);
                            break; } case 2:
                        {

                            GameObject o = createObject(r,c,res.textPanel, ObjectType::level);
                            gs.layers[LAYER_IDX_LEVEL].push_back(o);
                            break;
                        }

                    case 3:
                            {
                                GameObject o = createObject(r, c, res.textEnemy, ObjectType::enemy);
                                o.data.enemy = EnemyData();
                                o.currentAnimation = res.ANIM_ENEMY;
                                o.animations = res.enemyAnims;
                                o.maxSpeedx = 15;
                                o.dynamic = true;
                                o.collider = SDL_FRect{
                                    .x = 10, .y = 4, .w =12, .h =28
                                };
                                gs.layers[LAYER_IDX_CHARACTERS].push_back(o);
                                break;
                            }
                    case 4:
                        {
                            GameObject player = createObject(r, c,res.textIdle,  ObjectType::player);
                            player.data.player = PlayerData();
                            player.animations = res.playerAnims;
                            player.currentAnimation = res.ANIM_PLAYER_IDLE;
                            player.acceleration = glm::vec2(300, 0);
                            player.collider = {
                                .x = 11.f,
                                .y = 6,
                                .w = 10.f,
                                .h = 26.f
                            };
                            player.dynamic = true;
                            player.maxSpeedx= 100;
                        
                            gs.layers[LAYER_IDX_CHARACTERS].push_back(player);
                            gs.playerIndex = gs.layers[LAYER_IDX_CHARACTERS].size() - 1;
                            break;
                        }

                    case 5:
                        {
                            GameObject o = createObject(r, c,res.textGrass, ObjectType::level);
                            gs.foregroundTiles.push_back(o);
                            break;
                        }

                    case 6:
                        {
                            GameObject o = createObject(r, c , res.textBrick, ObjectType::level);
                            gs.backgroundTiles.push_back(o);
                            break;
                        }
                }
            }
        }


                
    };
    
    loadMap(background);
    loadMap(foreground);
    loadMap(map);
    assert(gs.playerIndex != -1);
}


void handleKeyInput(const SDLState &state, GameState &gs, GameObject &obj, 
        SDL_Scancode key, bool keyDown)
{
    const float JUMP_FORCE = -200.f;
    if(obj.type == ObjectType::player)
    {
        switch(obj.data.player.state)
        {
            case PlayerState::idle:
                {
                    if(key == SDL_SCANCODE_K && keyDown)
                    {
                        obj.data.player.state = PlayerState::jumping;
                        obj.velocity.y += JUMP_FORCE;

                    }
                    break;
                }
            case PlayerState::running:
                {
                    if(key == SDL_SCANCODE_K && keyDown)
                    {
                        obj.data.player.state = PlayerState::jumping;
                        obj.velocity.y += JUMP_FORCE;

                    }
                    break;
                }

            case PlayerState::jumping:
                {
                    break;
                }
        }
    }

    
}

void drawParalaxBackGround(SDL_Renderer *renderer, SDL_Texture *texture,
        float xVelocity, float &scrollPos, float scrollFactor, float deltaTime)
{
    scrollPos -= xVelocity * scrollFactor * deltaTime;

    if (scrollPos <= -texture->w)
    {
        scrollPos = 0;
    }
    SDL_FRect dest {
        .x = scrollPos, .y=30,
        .w = texture->w * 2.f,
        .h = static_cast<float>(texture->h)
    };

    SDL_RenderTextureTiled(renderer, texture, nullptr, 1, &dest);
}
