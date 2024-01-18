#ifndef COLLIDABLE_HPP
#define COLLIDABLE_HPP

#include <filesystem>
#include <fstream>
#include <memory>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

enum class CollidableType {
    sphere,
    cube,
    cuboid
};

struct AABB {
    glm::dvec3 min = glm::dvec3(0.0);
    glm::dvec3 max = glm::dvec3(0.0);
};

struct Collidable {

    unsigned int id = -1;
    CollidableType type;

    bool immovable = false;

    glm::dvec3 position = glm::dvec3(0.0);
    uint64_t mortonCode = 0;

    AABB aabb;

    union {
        double length = 0;
        double radius;
        double xl;
    };
    double yl = 0;
    double zl = 0;

    glm::dvec3 velocity = glm::dvec3(0.0);

    Collidable() {}

    Collidable(
        const CollidableType type,
        const glm::dvec3& position,
        const double xl,
        const double yl = 0.0,
        const double zl = 0.0
    );

    static Collidable constructCube(const glm::dvec3& position, const double length);
    static Collidable constructSphere(const glm::dvec3& center, const double radius);
    static Collidable constructRectangularCuboid(const glm::dvec3& center, const double xl, const double yl, const double zl);

    static std::vector<Collidable> loadConfig(const std::filesystem::path& path);
    std::string toString() const;

};

#endif