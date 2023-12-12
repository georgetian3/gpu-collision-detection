#ifndef COLLIDABLE_HPP
#define COLLIDABLE_HPP

#include <filesystem>
#include <fstream>
#include <vector>
#include <glm/glm.hpp>


struct Collision {
    bool collided;
    unsigned int id1;
    unsigned int id2;
    glm::dvec3 point;
};


class Sphere;
class RectangularCuboid;
class Cube;
class RegularTetrahedron;

class Collidable {

protected:

    static unsigned int idCount;
    unsigned int id;
    void setId();
    glm::dvec3 velocity;
    glm::dvec3 position;

    glm::dvec3 minAABB;
    glm::dvec3 maxAABB;

public:

    Collidable();
    unsigned int getId() const;
    glm::dvec3 getMinAABB() const;
    glm::dvec3 getMaxAABB() const;
    virtual Collision collides(const Sphere& collidable) = 0;
    virtual Collision collides(const Cube& cube) = 0;
    virtual Collision collides(const RectangularCuboid& cuboid) = 0;
    static std::vector<Collidable> readConfig(const std::filesystem::path& path);

};

class Sphere: public Collidable {

public:
    Sphere(const glm::dvec3 center, const double radius);

};


class RectangularCuboid: public Collidable {

    double xl;
    double yl;
    double zl;

public:
    RectangularCuboid(const glm::dvec3 position, const double xl, const double yl, const double zl);

};


class Cube: public Collidable {

    double length;

public:
    Cube(const glm::dvec3 position, const double length);
};

#endif