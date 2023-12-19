#include <scene.hpp>
#include <iostream>
#include <stopwatch.hpp>
#include <gpu_collision_detector.hpp>

int main(int argc, char* argv[]) {
    if (argc > 1) {
        std::cout << "Command line arguments ignored\n";
    }

    std::cout << "sizeof(Host Collidable): " << sizeof(Collidable) << '\n';
    
    // for (int i = 0; i < collidables.size(); i++) {
    //     std::cout << collidables[i]->toString() << '\n';
    // }
    // NaiveCollisionDetector naiveCD;
    // naiveCD.collidables = collidables;
    // naiveCD.detectCollisions();
    auto collidables = Collidable::loadConfig("resources/collidables.txt");
    GpuCollisionDetector gpuCD;
    gpuCD.setCollidables(collidables);
    gpuCD.detectCollisions();

    // Scene scene(
    //     (std::filesystem::current_path() / std::filesystem::path(argv[0]).parent_path()).lexically_normal(),
    //     1600, 900
    // );
    // scene.setCollisionDetector(std::shared_ptr<CollisionDetector>(&gpuCD));
    // scene.render();
    
    std::cout << "Done!";
}