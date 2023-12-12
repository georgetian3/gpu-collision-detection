#include <collidable.hpp>
#include <iostream>
#include <glm/gtx/string_cast.hpp>

unsigned int Collidable::idCount = 0;

void Collidable::setId() {
    id = idCount++;
}

Collidable::Collidable() {
    setId();
}

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

std::vector<Collidable> Collidable::readConfig(const std::filesystem::path& path) {
    // # all numeric values below are doubles
    // # s x y z r = sphere with center at (x, y, z) with radius r
    // # c x y z l = cube with smallest corner at (x, y, z) with side length l
    // # r x y z xl yl zl = rectangular cuboid with smallest corner at (x, y, z) with side lengths in x, y, z directions being xl, yl, yz, respectively
    std::vector<Collidable> collidables;
    std::ifstream f(path);
    if (!f.is_open()) {
        std::cout << "Cannot open file: " << path << '\n';
        exit(1);
    }
    std::string type;
    glm::dvec3 pos;
    double r, l, xl, yl, zl;
    while (!f.eof()) {
        Collidable collidable;
        f >> type >> pos.x >> pos.y >> pos.z;
        if (type == "s") {
            f >> r;
            collidable = Sphere(pos, r);
        } else if (type == "c") {
            f >> l;
            collidable = Cube(pos, l);
        } else if (type == "r") {
            f >> xl >> yl >> zl;
            collidable = RectangularCuboid(pos, xl, yl, zl);
        } else {
            std::cout << "Invalid shape type\n";
        }
        collidables.emplace_back(collidable);
    }
    return collidables;
}

Sphere::Sphere(const glm::dvec3 center, const double radius): radius(radius) {
    position = center;
    minAABB = glm::dvec3(-radius / 2);
    maxAABB = glm::dvec3(+radius / 2);
}

std::string Sphere::toString() const {
    char buf[100];
    sprintf(buf, "Sphere (center: %s, radius: %d)", glm::to_string(position), radius);
    return std::string(buf);
}

RectangularCuboid::RectangularCuboid(const glm::dvec3 position, const double xl, const double yl, const double zl):
    xl(xl), yl(yl), zl(zl) {
    
    minAABB = glm::dvec3(0.0);
    maxAABB = glm::dvec3(xl, yl, zl);

}

Cube::Cube(const glm::dvec3 position, const double length): length(length) {
    this->position = position;
    minAABB = glm::dvec3(0.0);
    maxAABB = glm::dvec3(length);
}