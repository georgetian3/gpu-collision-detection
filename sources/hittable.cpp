#include <hittable.hpp>
#include <utils.hpp>

HitRecord::HitRecord(glm::dvec3 point, glm::dvec3 normal, glm::dvec4 color, double t):
    point(point), normal(normal), color(color), t(t) {}


bool HitRecord::operator<(const HitRecord& other) const {
    return t < other.t;
}

std::string HitRecord::toString() const {
    return std::string("HitRecord");
}

glm::dvec3 Hittable::getPosition() const {
    return position;
}

bool Hittable::hitsAABB(const Hittable& other) const {
    return true;
    // glm::dmat4 modelMat = getModelMat();
    // glm::dvec3 worldMinAABB = applyModelMat(modelMat, minAABB);
    // glm::dvec3 worldMaxAABB = applyModelMat(modelMat, maxAABB);
    // double minT = -std::numeric_limits<double>::infinity();
    // double maxT = std::numeric_limits<double>::infinity();
    // for (int i = 0; i < 3; i++) {
    //     double t1 = (worldMinAABB[i] - rayOrigin[i]) / rayDirection[i];
    //     double t2 = (worldMaxAABB[i] - rayOrigin[i]) / rayDirection[i];
    //     if (t1 > t2) {
    //         double tmp = t2;
    //         t2 = t1;
    //         t1 = tmp;
    //     }
    //     if (t1 > minT) {
    //         minT = t1;
    //     }
    //     if (t2 < maxT) {
    //         maxT = t2;
    //     }
    //     if (minT > maxT) {
    //         return false;
    //     }
    // }
    // return true;
}

void Hittable::updateAABB(const glm::dvec3& vertex) {
    for (int i = 0; i < 3; i++) {
        if (vertex[i] < minAABB[i]) {
            minAABB[i] = vertex[i];
        }
        if (vertex[i] > maxAABB[i]) {
            maxAABB[i] = vertex[i];
        }
    }
}

void Hittable::updateAABB(const Hittable& child) {
    for (int i = 0; i < 3; i++) {
        if (child.minAABB[i] < minAABB[i]) {
            minAABB[i] = child.minAABB[i];
        }
        if (child.maxAABB[i] > maxAABB[i]) {
            maxAABB[i] = child.maxAABB[i];
        }
    }
}

std::vector<HitRecord> Hittable::hits(const Hittable& other) const {
    return std::vector<HitRecord>();
    // if (!hitsAABB(ray)) {
    //     return std::vector<HitRecord>();
    // }
    // return directlyHits(ray);
}

glm::dvec3 Hittable::getMinAABB() const {
    return minAABB;
}

glm::dvec3 Hittable::getMaxAABB() const {
    return maxAABB;
}

double Hittable::getScale() const {
    return scale;
}
void Hittable::setScale(const double scale) {
    this->scale = scale > 0 ? scale : 1;
}