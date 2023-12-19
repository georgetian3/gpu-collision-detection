#ifndef COLLIDABLE_HPP
#define COLLIDABLE_HPP

#include <filesystem>
#include <fstream>
#include <memory>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>

struct Collision {
    const unsigned int id1;
    const unsigned int id2;
    const glm::dvec3 point;
    Collision(const unsigned int id1, const unsigned int id2, const glm::dvec3 point): id1(id1), id2(id2), point(point) {}
    static bool isCollision(const Collision& collision) {
        return collision.id1 != 0 || collision.id2 != 0;
    }
};

const Collision NO_COLLISION = Collision(0, 0, glm::dvec3(0.0));

enum class CollidableType {
    sphere,
    cube,
    rectangularCuboid
};

struct AABB {
    glm::dvec3 min = glm::dvec3(0.0);
    glm::dvec3 max = glm::dvec3(0.0);
};

struct Collidable {

    const CollidableType type = CollidableType::sphere;
    const unsigned int id = -1;

    glm::dvec3 position = glm::dvec3(0.0);
    uint64_t mortonCode = 0;

    AABB relativeAABB;
    AABB absoluteAABB;

    union {
        const double length = 0;
        const double radius;
        const double xl;
    };

    const double yl = 0;
    const double zl = 0;

    Collidable(
        const CollidableType type,
        const glm::dvec3& position,
        const double xl,
        const double yl = 0.0,
        const double zl = 0.0
    );


    Collidable() {}

    static Collidable constructCube(const glm::dvec3& position, const double length) {
        return Collidable(CollidableType::cube, position, length);
    }
    static Collidable constructSphere(const glm::dvec3& center, const double radius) {
        return Collidable(CollidableType::sphere, center, radius);
    }

    static std::vector<Collidable> loadConfig(const std::filesystem::path& path);
    std::string toString() const;
    static Collision collide(const Collidable& a, const Collidable& b);

};

#endif