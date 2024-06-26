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
    cuboid
};

struct AABB {
    glm::dvec4 min = glm::dvec4(0.0);
    glm::dvec4 max = glm::dvec4(0.0);
};

#pragma pack(1)
struct Collidable {

    glm::dvec4 position = glm::dvec4(0.0);
    glm::dvec4 velocity = glm::dvec4(0.0);
    AABB aabb;

    uint64_t mortonCode = 0;
    union {
        double length = 0;
        double radius;
        double xl;
    };
    double yl = 0;
    double zl = 0;
    double mass = 1.0;
    double cor = 1.0;

    unsigned int id = -1;
    CollidableType type;

    int immovable = false;

    Collidable() {}

    Collidable(
        const CollidableType type,
        const glm::dvec3& position,
        const glm::dvec3& velocity,
        const double mass,
        const double cor,
        const double xl,
        const double yl = 0.0,
        const double zl = 0.0
    );

    static std::vector<Collidable> loadConfig(const std::filesystem::path& path);

};
#pragma pack()

#endif