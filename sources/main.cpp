#include <scene.hpp>
#include <iostream>
#include <gpu_collision_detector.hpp>
#include <utils.hpp>
#include <iostream>

int main(int argc, char* argv[]) {

    std::filesystem::path cwd = (std::filesystem::current_path() / std::filesystem::path(argv[0]).parent_path()).lexically_normal();

    if (argc > 1) {
        std::cout << "Command line arguments ignored\n";
    }

    auto collidables = Collidable::loadConfig(makeAbsolute(cwd, "resources/collidables.txt"));
    GpuCollisionDetector gpuCD;
    gpuCD.setCollidables(collidables);

    for (int i = 0; i < 2; i++) {
        gpuCD.updatePhysics(0.0005);
    }


    // Scene scene(
    //     (std::filesystem::current_path() / std::filesystem::path(argv[0]).parent_path()).lexically_normal(),
    //     1600, 900
    // );

    // scene.render();

    std::cout << "Done!";
}