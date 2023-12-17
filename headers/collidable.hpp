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
    circle,
    cube,
    rectangularCuboid
};

class Collidable {

    CollidableType type;
    unsigned int id = -1;

    glm::dvec3 position = glm::dvec3(0.0);

    glm::dvec3 minAABB = glm::dvec3(0.0);
    glm::dvec3 maxAABB = glm::dvec3(0.0);

    union {
        double length = 0;
        double radius;
        double xl;
    };

    double yl = 0;
    double zl = 0;

public:

    static Collidable constructCube(const glm::dvec3& position, const double length) {
        return Collidable();
    }
    static std::vector<Collidable> loadConfig(const std::filesystem::path& path) {
        return std::vector<Collidable>();
    }

    unsigned int getId() const;
    glm::dvec3 getMinAABB() const;
    glm::dvec3 getMaxAABB() const;
    std::string toString() const;

    static Collision collide(const Collidable& a, const Collidable& b) {
        std::cout << "Collision collide(const Collidable& a, const Collidable& b)\n";
        return NO_COLLISION;
    }

};


#endif