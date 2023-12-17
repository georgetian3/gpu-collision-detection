#include <collidable.hpp>
#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/norm.hpp>

unsigned int idCount = 0;


unsigned int Collidable::getId() const {
    return id;
}

glm::dvec3 Collidable::getMinAABB() const {
    return position + minAABB;
}

glm::dvec3 Collidable::getMaxAABB() const {
    return position + maxAABB;
}

std::string Collidable::toString() const {
    return std::string("Collidable");
}

std::vector<Collidable> Collidable::loadConfig(const std::filesystem::path& path) {
    // # all numeric values below are doubles
    // # s x y z r = sphere with center at (x, y, z) with radius r
    // # c x y z l = cube with smallest corner at (x, y, z) with side length l
    // # r x y z xl yl zl = rectangular cuboid with smallest corner at (x, y, z) with side lengths in x, y, z directions being xl, yl, yz, respectively
    std::vector<std::shared_ptr<Collidable>> collidables;
    std::ifstream f(path);
    if (!f.is_open()) {
        std::cout << "Cannot open file: " << path << '\n';
        exit(1);
    }
    std::string type;
    glm::dvec3 pos;
    double r, l, xl, yl, zl;
    while (!f.eof()) {
        Collidable* collidable;
        f >> type >> pos.x >> pos.y >> pos.z;
        if (type == "s") {
            f >> r;
            collidable = new Sphere(pos, r);
        } else if (type == "c") {
            f >> l;
            collidable = new Cube(pos, l);
        } else if (type == "r") {
            f >> xl >> yl >> zl;
            collidable = new RectangularCuboid(pos, xl, yl, zl);
        } else {
            std::cout << "Invalid shape type\n";
        }
        collidables.emplace_back(std::shared_ptr<Collidable>(collidable));
    }
    return collidables;
}