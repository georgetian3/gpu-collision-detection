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

uint64_t expandBits(double v) {
    uint64_t u = (unsigned int)(v * (1 << 21));
    std::cout << toBits(u) << '\n';
    u = (u * 0x00010001u) & 0xFF0000FFu;
    std::cout << toBits(u) << '\n';
    u = (u * 0x00000101u) & 0x0F00F00Fu;
    std::cout << toBits(u) << '\n';
    u = (u * 0x00000011u) & 0xC30C30C3u;
    std::cout << toBits(u) << '\n';
    u = (u * 0x00000005u) & 0x49249249u;
    std::cout << toBits(u) << '\n';
    return u;
}

#endif