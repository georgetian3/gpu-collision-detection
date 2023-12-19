#include <scene.hpp>
#include <iostream>
#include <stopwatch.hpp>
#include <gpu_collision_detector.hpp>
#include <utils.hpp>
#include <glm/gtx/string_cast.hpp>

int main(int argc, char* argv[]) {
    if (argc > 1) {
        std::cout << "Command line arguments ignored\n";
    }

    std::cout << "sizeof(Host Collidable): " << sizeof(Collidable) << '\n';

    auto collidables = Collidable::loadConfig("resources/collidables.txt");
    GpuCollisionDetector gpuCD;
    gpuCD.setCollidables(collidables);
    gpuCD.detectCollisions();


    std::cout << "Done!";
}