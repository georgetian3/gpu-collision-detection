#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <limits>
#include <vector>
#include <string>

struct HitRecord {
    glm::dvec3 point;
    glm::dvec3 normal;
    glm::dvec4 color;
    double t;
    HitRecord(
        glm::dvec3 point = glm::dvec3(0.0),
        glm::dvec3 normal = glm::dvec3(0.0),
        glm::dvec4 color = glm::dvec4(0.0),
        double t = 0
    );
    bool operator<(const HitRecord& other) const;
    std::string toString() const;
};

class Hittable {

    glm::dvec3 minAABB = glm::dvec3(std::numeric_limits<double>::infinity());
    glm::dvec3 maxAABB = glm::dvec3(-std::numeric_limits<double>::infinity());
    bool hitsAABB(const Hittable& other) const;

protected:

    glm::dvec3 position = glm::dvec3(0.0);
    void updateAABB(const glm::dvec3& vertex);
    void updateAABB(const Hittable& child);
    glm::dmat4 getModelMat() const {
        return glm::scale(glm::translate(glm::dmat4(1.0), position), glm::dvec3(scale));
    }

public:

    double scale = 1.0;
    double getScale() const;
    void setScale(const double scale);
    glm::dvec3 getPosition() const;
    virtual void setPosition(const glm::dvec3& position) = 0;
    glm::dvec3 getMinAABB() const;
    glm::dvec3 getMaxAABB() const;
    virtual std::vector<HitRecord> directlyHits(const Hittable& other) const = 0;
    std::vector<HitRecord> hits(const Hittable& other) const;

};

#endif