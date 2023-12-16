#ifndef UTILS_HPP
#define UTILS_HPP

#include <filesystem>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
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

// https://stackoverflow.com/a/35687575
template<typename Numeric, typename Generator = std::mt19937>
Numeric random(Numeric from, Numeric to)
{
    thread_local static Generator gen(std::random_device{}());

    using dist_type = typename std::conditional
    <
        std::is_integral<Numeric>::value
        , std::uniform_int_distribution<Numeric>
        , std::uniform_real_distribution<Numeric>
    >::type;

    thread_local static dist_type dist;

    return dist(gen, typename dist_type::param_type{from, to});
}

std::string readFile(const std::filesystem::path& path) {
    std::ifstream f(path);
    std::string content(
        ((std::istreambuf_iterator<char>(f))),
        ((std::istreambuf_iterator<char>()))
    );
    return content;
}

#endif