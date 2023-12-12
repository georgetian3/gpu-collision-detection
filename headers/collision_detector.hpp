#ifndef COLLISION_DETECTOR_HPP
#define COLLISION_DETECTOR_HPP

#include <collidable.hpp>


class CollisionDetector {

protected:

    std::vector<Collidable> collidables;

public:

    void addCollidable(const Collidable& collidable) {
        collidables.emplace_back(collidable);
    }
    virtual std::vector<Collision> detectCollisions() {
        return std::vector<Collision>();
    }

};

class NaiveCollisionDetector: public CollisionDetector {

public:

    std::vector<Collision> detectCollisions() final {
        std::vector<Collision> collisions;
        for (size_t i = 0; i < collidables.size(); i++) {
            for (size_t j = i + 1; j < collidables.size(); j++) {
                // Collision collision = collidables[i].collides(collidables[j]);
                // if (collision.collided) {
                //     collisions.emplace_back(collision);
                // }
            }
        }
        return collisions;
    }

};

class GpuCollisionDetector: public CollisionDetector {



};

#endif