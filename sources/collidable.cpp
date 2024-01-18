#include <collidable.hpp>
#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/norm.hpp>
#include <utils.hpp>

#define STRING_BUF_SIZE 256

static unsigned int idCount = 0;

std::string collidableTypeStrings[] = {
    std::string("Sphere"),
    std::string("Cuboid"),
};

std::vector<Collidable> Collidable::loadConfig(const std::filesystem::path& path) {
    // all numeric values below are doubles
    // s x y z r = sphere with center at (x, y, z) with radius r
    // r x y z xl yl zl = cuboid with smallest corner at (x, y, z) with side lengths in x, y, z directions being xl, yl, yz, respectively
    std::ifstream f(path);
    if (!f.is_open()) {
        std::cout << "Cannot open file: " << path << '\n';
        exit(1);
    }
    std::vector<Collidable> collidables;
    std::string type;
    glm::dvec3 pos;
    glm::dvec3 velocity;
    double r, xl, yl, zl;
    while (!f.eof()) {
        Collidable collidable;
        f >> type >> pos.x >> pos.y >> pos.z >> velocity.x >> velocity.y >> velocity.z;
        if (type == "s") {
            f >> r;
            collidable = Collidable::constructSphere(pos, r);
        } else if (type == "c") {
            f >> xl >> yl >> zl;
            collidable = Collidable::constructCuboid(pos, xl, yl, zl);
        } else {
            std::cerr << "Invalid shape type: " << type << "\n";
            exit(1);
        }
        collidables.emplace_back(collidable);
    }
    return collidables;
}

Collidable::Collidable(
    const CollidableType type,
    const glm::dvec3& position,
    const glm::dvec3& velocity,
    const double mass,
    const double cor,
    const double xl,
    const double yl,
    const double zl
): id(idCount++), type(type), position(glm::dvec4(position.x, position.y, position.z, 0)), xl(xl), yl(yl), zl(zl) {
    this->cor = clamp(cor, 0.0, 1.0);
    this->mass = clamp(mass, 0.0, 1e10);
    switch (type) {
        case CollidableType::sphere: {
            aabb.min = glm::dvec4(0);
            aabb.max = glm::dvec4(xl);
            break;
        }
        case CollidableType::cuboid: {
            aabb.min = glm::dvec4(0);
            aabb.max = glm::dvec4(xl, yl, zl, 0);
            break;
        }
        default: {
            std::cerr << "Unknown type\n";
            exit(1);
        }
    }
}

Collidable Collidable::constructSphere(const glm::dvec3& center, const double radius) {
    return Collidable(CollidableType::sphere, center, radius);
}
Collidable Collidable::constructCuboid(const glm::dvec3& position, const double xl, const double yl, const double zl) {
    return Collidable(CollidableType::cuboid, position, xl, yl, zl);
}