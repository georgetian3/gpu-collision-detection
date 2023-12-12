#include <collidable.hpp>

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

Collision Collidable::collides(const Collidable&) {
    return {false, 0, 0, glm::dvec3(0.0)};
}

std::vector<Collidable> Collidable::readConfig(const std::filesystem::path& path) {
    return std::vector<Collidable>();
}

Sphere::Sphere(const glm::dvec3 center, const double radius) {
    position = center;
    minAABB = glm::dvec3(-radius / 2);
    maxAABB = glm::dvec3(+radius / 2);
}

Collision Sphere::collides(const Sphere& sphere) {
    return {false, 0, 0, glm::dvec3(0.0)};
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