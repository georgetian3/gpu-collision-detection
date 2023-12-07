#ifndef COLLIDABLE_HPP
#define COLLIDABLE_HPP

#include <vector>
#include <glm/vec3.hpp>

class Collidable {

    static unsigned int idCount;
    unsigned int id;
    void setId();
    glm::dvec3 velocity;
    glm::dvec3 position;

public:

    Collidable();
    unsigned int getId() const;

};


struct Collision {


};

class Collidables {

    std::vector<Collidable> collidableList;

public:

    void addCollidable(const Collidable& collidable);

};

#endif