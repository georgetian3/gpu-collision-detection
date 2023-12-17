#include <scene.hpp>
#include <iostream>
#include <stopwatch.hpp>
#include <gpu_collision_detector.hpp>

int main(int argc, char* argv[]) {
    if (argc > 1) {
        std::cout << "Command line arguments ignored\n";
    }
    
    // for (int i = 0; i < collidables.size(); i++) {
    //     std::cout << collidables[i]->toString() << '\n';
    // }
    // NaiveCollisionDetector naiveCD;
    // naiveCD.collidables = collidables;
    // naiveCD.detectCollisions();
    // Scene scene(
    //     (std::filesystem::current_path() / std::filesystem::path(argv[0]).parent_path()).lexically_normal(),
    //     1600, 900
    // );
    auto collidables = Collidable::readConfig("resources/collidables.txt");
    GpuCollisionDetector gpuCD;
    gpuCD.setCollidables(collidables);
    gpuCD.test();
    std::cout << "Done!";
}