#ifndef UTILS_HPP
#define UTILS_HPP

#include <bitset>
#include <iostream>
#include <filesystem>
#include <random>
#include <sstream>
#include <string>

#define printLocation() std::cout << "########### printLocation: " << __FILE__ << ' ' << __LINE__ << " ###########\n";

template <class T>
T clamp(T value, T min, T max) {
    return value < min ? min : value > max ? max : value;
}

// https://stackoverflow.com/a/35687575
template<typename Numeric, typename Generator = std::mt19937>
Numeric random(Numeric from, Numeric to) {
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

template <class T>
std::string vectorToString(std::vector<T> v) {
    std::stringstream s;
    s << "[";
    for (size_t i = 0; i < v.size() - 1; i++) {
        s << v[i] << ", ";
    }
    s << v.back() << ']';
    return s.str();
}

template <class T>
std::bitset<sizeof(T) * 8> toBits(T v) {
    return std::bitset<sizeof(T) * 8>(v);
}

std::string readFile(const std::filesystem::path& path);

uint64_t expandBits3(double v);

std::filesystem::path makeAbsolute(std::filesystem::path path);

#endif