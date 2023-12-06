#include <collidable.hpp>

void Collidable::setId() const {
    id = idCount++;
}

Collidable::Collidable() {
    setId();
}


unsigned int Collidable::getId() const {
    return id;
}


void Collidable::addCollidable(const Collidable& collidable) {
    collidableList.emplace_back(collidable);
}