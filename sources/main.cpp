#include <scene.hpp>
#include <iostream>
#include <stopwatch.hpp>
#include <collision_detector.hpp>

int main(int argc, char* argv[]) {
    if (argc > 1) {
        std::cout << "Command line arguments ignored\n";
    }
    auto collidables = Collidable::readConfig("resources/collidables.txt");
    for (const auto& collidable: collidables) {
        std::cout << collidable.toString() << '\n';
    }
    NaiveCollisionDetector naiveCD;
    // Scene scene(
    //     (std::filesystem::current_path() / std::filesystem::path(argv[0]).parent_path()).lexically_normal(),
    //     1600, 900
    // );
    std::cout << "Done!";
}