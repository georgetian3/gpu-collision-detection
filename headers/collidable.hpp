#ifndef COLLIDABLE_HPP
#define COLLIDABLE_HPP

#include <vector>
#include <glm/vec3.hpp>

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


};

class Sphere: public Collidable {

public:
    Sphere(const glm::dvec3 center, const double radius) {
        position = center;
        minAABB = glm::dvec3(-radius / 2);
        maxAABB = glm::dvec3(+radius / 2);
    }

};


class RectangularCuboid: public Collidable {

    double xl;
    double yl;
    double zl;

public:
    RectangularCuboid(const glm::dvec3 position, const double xl, const double yl, const double zl):
        xl(xl), yl(yl), zl(zl) {
        
        minAABB = glm::dvec3(0.0);
        maxAABB = glm::dvec3(xl, yl, zl);

    }


}


class Cube: public Collidable {

    double length;

public:
    Cube(const glm::dvec3 position, const double length): length(length) {
        this->position = position;
        minAABB = glm::dvec3(0.0);
        maxAABB = glm::dvec3(length);
    }
}

#endif