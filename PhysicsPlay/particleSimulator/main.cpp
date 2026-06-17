#include <iostream>
#include <raylib.h>
#include <vector>
#include <random>




struct Particle {
    Vector2 position{};
    Vector2 velocity{};
    float radius{};
};

float random_range(float min, float max){
    static std::mt19937 generator{std::random_device()()};
    std::uniform_real_distribution<float> range {min, max};
    return range(generator);
}

class ParticleSimulation{

    public:
        static constexpr size_t INITIAL_PARTICLES_AMOUNT{100};

        ParticleSimulation(){
            for(size_t i{}; i < INITIAL_PARTICLES_AMOUNT; i++){
                Particle particle{};
            }
        }

    private:
        std::vector<Particle> m_particles{};

};

int main(void)
{
    const int screenWidth = 1000;
    const int screenHeight = 1000;

    InitWindow(screenWidth, screenHeight, "Particle Simulator");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
