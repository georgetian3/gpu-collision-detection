#ifndef COLLISION_DETECTOR_HPP
#define COLLISION_DETECTOR_HPP

#include <collidable.hpp>


class CollisionDetector {

public:

    virtual std::vector<Collision> detectCollisions() = 0;

};

class NaiveCollisionDetector: public CollisionDetector {


public:

    std::vector<std::shared_ptr<Collidable>> collidables;



    std::vector<Collision> detectCollisions() final {
        std::vector<Collision> collisions;
        for (size_t i = 0; i < collidables.size(); i++) {
            for (size_t j = i + 1; j < collidables.size(); j++) {
                Collision collision = Collidable::collide(*collidables[i], *collidables[j])
                if (!Collision::isCollision(collision)) {
                    collisions.emplace_back(collision);
                }
            }
        }
        return collisions;
    }

};

class GpuCollisionDetector: public CollisionDetector {

public:

    std::vector<Collision> detectCollisions() final {
        std::vector<Collision> collisions;
        return collisions;
    }


};

#endif