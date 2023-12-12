#ifndef COLLISION_DETECTOR_HPP
#define COLLISION_DETECTOR_HPP

#include <collidable.hpp>

struct Collision {
    unsigned int id1;
    unsigned int id2;
    glm::dvec3 point;

};

class CollisionDetector {

public:

    void addCollidable(const Collidable& collidable);
    std::vector<Collision> detectCollisions();

};

class NaiveCollisionDetector: public CollisionDetector {


}

class GpuCollisionDetector: public CollisionDetector {



}

#endif