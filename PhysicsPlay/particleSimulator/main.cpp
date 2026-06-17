#include <iostream>
#include <raylib.h>
#include <vector>
#include <random>


constexpr float MAX_INITIAL_SPEED { 300.0f };
constexpr float MAX_RADIUS {7.0f};
constexpr float MIN_RADIUS {3.0f};
constexpr float DRAG {0.99f};
constexpr float GRAVITY {9.81f};

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
                particle.position = Vector2{random_range(0.0f, GetScreenWidth()), 
                    random_range(0.0f, GetScreenHeight())};
                particle.velocity = Vector2{random_range(-MAX_INITIAL_SPEED, MAX_INITIAL_SPEED), 
                    random_range(-MAX_INITIAL_SPEED, MAX_INITIAL_SPEED)};

                particle.radius = random_range(MIN_RADIUS, MAX_RADIUS);

                m_particles.push_back(particle);
            }
        }


        void draw(){

            for(const auto& particle: m_particles){
                DrawCircle(particle.position.x, particle.position.y, particle.radius, WHITE);
            }

        }

        void update(float deltatime){
            for(auto& particle : m_particles){

                particle.velocity.x *= DRAG;
                particle.velocity.y *= DRAG;

                particle.velocity.y += GRAVITY;

                particle.position.x += particle.velocity.x * deltatime;
                particle.position.y += particle.velocity.y * deltatime;

                bool hitRight { particle.position.x + particle.radius >= GetScreenWidth() };
                bool hitLeft{ particle.position.x - particle.radius <= 0 };
                bool hitDown{particle.position.y + particle.radius >= GetScreenHeight()};
                bool hitUp{ particle.position.y - particle.radius <= 0 };


                if(hitRight){
                    particle.position.x = GetScreenWidth() - particle.radius;
                    particle.position.x *= -1;
                }

                if(hitLeft){
                    particle.position.x =  particle.radius;
                    particle.position.x *= -1;
                }

                if(hitUp){
                    particle.position.y = particle.radius;
                    particle.position.y *= -1;
                }
                if(hitDown){
                    particle.position.y = GetScreenHeight() - particle.radius;
                    particle.position.y *= -1;
                }

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

    ParticleSimulation simulation{};
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        simulation.draw();
        simulation.update(GetFrameTime());
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
