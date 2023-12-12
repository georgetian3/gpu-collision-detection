#include <scene.hpp>
#include <iostream>
#include <stopwatch.hpp>
#include <collision_detector.hpp>

int main(int argc, char* argv[]) {
    if (argc > 1) {
        std::cout << "Command line arguments ignored\n";
    }

    NaiveCollisionDetector naiveCD;
    // Scene scene(
    //     (std::filesystem::current_path() / std::filesystem::path(argv[0]).parent_path()).lexically_normal(),
    //     1600, 900
    // );
}