#include <raylib.h>
#include <iostream>
#include <vector>
#include <random>

static constexpr size_t INITIAL_PARTICLE_AMOUNT{100};
const float MAX_INITIAL_SPEED{300.f};
const float MAX_RADIUS{7.f};
const float MIN_RADIUS{4.f};
const float DRAG{0.99f};
const float GRAVITY{9.81f};
const float BOUNCE{0.8f};

struct Particle {
    Vector2 position{};
    Vector2 velocity{};
    float radius{};
};

float random_range(float min, float max){

    static std::mt19937 generator{std::random_device()()};
    std::uniform_real_distribution<float> range{min, max};
    return range(generator);

}

class ParticleSimulation {
    public:
        ParticleSimulation(){

            for(size_t i{}; i < INITIAL_PARTICLE_AMOUNT; i++){
                Particle particle{};
                particle.position = Vector2{random_range(0, GetScreenWidth()), random_range(0, GetScreenHeight())};
                particle.velocity = Vector2{random_range(-MAX_INITIAL_SPEED, MAX_INITIAL_SPEED), random_range(-MAX_INITIAL_SPEED, MAX_INITIAL_SPEED)};
                particle.radius = random_range(MIN_RADIUS, MAX_RADIUS);
                mParticles.push_back(particle);
            }

        }

        void draw(){
            for(const auto& particle: mParticles){
                DrawCircle(particle.position.x,particle.position.y,particle.radius,WHITE);
            }

        }

        void update(float deltaTime){

            static Vector2 lastWindowPosition{GetWindowPosition()};

            for(auto& particle: mParticles){

                float dx {GetWindowPosition().x - lastWindowPosition.x};
                float dy {GetWindowPosition().y - lastWindowPosition.y};

                particle.velocity.x += dx * 2;
                particle.velocity.y += dy * 2;


                particle.velocity.x *= DRAG;
                particle.velocity.y *= DRAG;

                particle.velocity.y += GRAVITY;
                particle.position.x += particle.velocity.x * deltaTime;
                particle.position.y += particle.velocity.y * deltaTime;

                bool hitRight{particle.position.x + particle.radius > GetScreenWidth()};
                bool hitLeft{particle.position.x - particle.radius < 0};
                bool hitDown{particle.position.y + particle.radius > GetScreenHeight()};
                bool hitUp{particle.position.y - particle.radius < 0};

                if(hitRight){
                    particle.position.x = GetScreenWidth() - particle.radius;
                    particle.velocity.x *= -BOUNCE;
                }
                if(hitLeft){
                    particle.position.x = 0 + particle.radius;
                    particle.velocity.x *= -BOUNCE;
                }
                if(hitUp){
                    particle.position.y = 0 + particle.radius;
                    particle.velocity.y *= -BOUNCE;
                }
                if(hitDown){
                    particle.position.y = GetScreenHeight() - particle.radius;
                    particle.velocity.y *= -BOUNCE;
                }

            }

            lastWindowPosition = GetWindowPosition();
            for(size_t i{}; i< mParticles.size(); i++){
                for(size_t j{i + 1}; j < mParticles.size(); j++){
                    auto& a{mParticles[i]};
                    auto& b{mParticles[j]};


                    Vector2 delta {
                        b.position.x - a.position.x,
                        b.position.y - b.position.y
                    };

                    float distance {sqrtf(delta.x * delta.x + delta.y * delta.y)};

                    float min_distance{a.radius + b.radius};
                    if (distance >= min_distance) continue;


                    Vector2 normal { delta.x/distance , delta.y/distance };
                    float overlap {min_distance - distance};

                    a.position.x -= normal.x * overlap * 0.5;
                    a.position.y -= normal.x * overlap * 0.5;


                    b.position.x += normal.x * overlap * 0.5;
                    b.position.y += normal.x * overlap * 0.5;


                    Vector2 relativeVelocity {
                        b.velocity.x - a.velocity.x,
                        b.velocity.y - b.velocity.y
                    };

                    float dotRelativeVelocityNormal{
                        relativeVelocity.x * normal.x+
                        relativeVelocity.y * normal.y
                    } ;

                    if (dotRelativeVelocityNormal > 0) continue;

                    float restitution {0.9f};

                    float impulseScalar {
                        -(1.0f + restitution) * dotRelativeVelocityNormal / 2.f
                    };
                
                    Vector2 impulse {normal.x * impulseScalar, normal.y * impulseScalar};

                    a.velocity.x -= impulse.x;
                    a.velocity.y -= impulse.y;

                    b.velocity.x += impulse.x;
                    b.velocity.y += impulse.y;


                }
            }


        }

    private:
        std::vector<Particle> mParticles{};

};

int main(){

	InitWindow(920, 720, "raylib example - basic window");
    ParticleSimulation particleSim{};

	SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(BLACK);
            particleSim.draw();
            particleSim.update(GetFrameTime());
        EndDrawing();
    }

    CloseWindow();
	return 0;
}
