#include <collidable.hpp>
#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/norm.hpp>

static unsigned int idCount = 0;

std::string collidableTypeStrings[] = {
    std::string("Sphere"),
    std::string("Cube"),
    std::string("Rectangular Cuboid"),
};


std::string Collidable::toString() const {
    return collidableTypeStrings[static_cast<int>(type)] + std::string(" ") + glm::to_string(position);
}

std::vector<Collidable> Collidable::loadConfig(const std::filesystem::path& path) {
    // # all numeric values below are doubles
    // # s x y z r = sphere with center at (x, y, z) with radius r
    // # c x y z l = cube with smallest corner at (x, y, z) with side length l
    // # r x y z xl yl zl = rectangular cuboid with smallest corner at (x, y, z) with side lengths in x, y, z directions being xl, yl, yz, respectively
    std::ifstream f(path);
    if (!f.is_open()) {
        std::cout << "Cannot open file: " << path << '\n';
        exit(1);
    }
    std::vector<Collidable> collidables;
    std::string type;
    glm::dvec3 pos;
    double r, l, xl, yl, zl;
    while (!f.eof()) {
        Collidable collidable;
        f >> type >> pos.x >> pos.y >> pos.z;
        if (type == "s") {
            f >> r;
            collidable = Collidable::constructSphere(pos, r);
        } else if (type == "c") {
            f >> l;
            collidable = Collidable::constructCube(pos, l);
        } else if (type == "r") {
            f >> xl >> yl >> zl;
            // collidable = new RectangularCuboid(pos, xl, yl, zl);
        } else {
            std::cout << "Invalid shape type\n";
        }
        collidables.emplace_back(collidable);
    }
    return collidables;
}

Collidable::Collidable(
    const unsigned int id,
    const CollidableType type,
    const glm::dvec3& position,
    const double xl,
    const double yl,
    const double zl
): id(id), type(type), position(position), xl(xl), yl(yl), zl(zl) {}

Collidable::Collidable(
    const CollidableType type,
    const glm::dvec3& position,
    const double xl,
    const double yl,
    const double zl
): id(idCount++), type(type), position(position), xl(xl), yl(yl), zl(zl) {}

Collidable::Collidable operator=(const Collidable& other) {
    return Collidable(other.id, other.type, other.position, other.xl, other.yl, other.zl);
}

static Collidable constructCube(const glm::dvec3& position, const double length) {
    return Collidable(CollidableType::cube, position, length);
}
static Collidable constructSphere(const glm::dvec3& center, const double radius) {
    return Collidable(CollidableType::sphere, center, radius);
}
