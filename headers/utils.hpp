#ifndef UTILS_HPP
#define UTILS_HPP

#include <filesystem>
#include <iostream>
#include <sstream>
#include <glm/glm.hpp>

#define printLocation() std::cout << "########### printLocation: " << __FILE__ << ' ' << __LINE__ << " ###########\n";

template <class T>
inline T clamp(T value, T min, T max) {
    return value < min ? min : value > max ? max : value;
}

inline std::string vec3ToString(glm::dvec3 vec) {
    std::ostringstream stream;
    stream << '(' << vec[0] << ',' << vec[1] << ',' << vec[2] << ')';
    return stream.str();
}

inline glm::dvec3 applyModelMat(glm::dmat4 modelMat, glm::dvec3 point) {
    return glm::dvec3(modelMat * glm::dvec4(point, 1.0));
}


#endif