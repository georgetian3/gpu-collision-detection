#include <scene.hpp>
#include <iostream>
#include <stopwatch.hpp>
#include <collision_detector.hpp>

int main(int argc, char* argv[]) {
    if (argc > 1) {
        std::cout << "Command line arguments ignored\n";
    }
    auto collidables = Collidable::readConfig("resources/collidables.txt");
    for (int i = 0; i < collidables.size(); i++) {
        std::cout << collidables[i]->toString() << '\n';
    }
    NaiveCollisionDetector naiveCD;
    naiveCD.collidables = collidables;
    naiveCD.detectCollisions();
    // Scene scene(
    //     (std::filesystem::current_path() / std::filesystem::path(argv[0]).parent_path()).lexically_normal(),
    //     1600, 900
    // );
    std::cout << "Done!";
}