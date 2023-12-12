#ifndef COLLIDABLE_HPP
#define COLLIDABLE_HPP

#include <filesystem>
#include <fstream>
#include <memory>
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

class Sphere;
class RectangularCuboid;
class Cube;

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
    static std::vector<std::shared_ptr<Collidable>> readConfig(const std::filesystem::path& path);
    virtual std::string toString() const = 0;
    static Collision collide(const Sphere&, const Sphere&);
    static Collision collide(const Sphere&, const RectangularCuboid&);
    static Collision collide(const Sphere&, const Cube&);
    static Collision collide(const Cube&, const Sphere&);
    static Collision collide(const Cube&, const Cube&);
    static Collision collide(const Cube&, const RectangularCuboid&);
    static Collision collide(const RectangularCuboid&, const Sphere&);
    static Collision collide(const RectangularCuboid&, const RectangularCuboid&);
    static Collision collide(const RectangularCuboid&, const Cube&);

};

class Sphere: public Collidable {

    double radius;

public:

    Sphere(const glm::dvec3 center, const double radius);
    glm::dvec3 getCenter() const;
    double getRadius() const;
    virtual std::string toString() const;

};

class RectangularCuboid: public Collidable {

    double xl;
    double yl;
    double zl;

public:

    RectangularCuboid(const glm::dvec3 position, const double xl, const double yl, const double zl);
    virtual std::string toString() const;

};

class Cube: public Collidable {

    double length;

public:
    Cube(const glm::dvec3 position, const double length);
    virtual std::string toString() const;
};

#endif