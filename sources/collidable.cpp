#include <collidable.hpp>

unsigned int Collidable::idCount = 0;

void Collidable::setId() {
    id = idCount++;
}

Collidable::Collidable() {
    setId();
}

unsigned int Collidable::getId() const {
    return id;
}
