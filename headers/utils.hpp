#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <filesystem>
#include <random>
#include <string>

#define printLocation() std::cout << "########### printLocation: " << __FILE__ << ' ' << __LINE__ << " ###########\n";

template <class T>
T clamp(T value, T min, T max) {
    return value < min ? min : value > max ? max : value;
}

// https://stackoverflow.com/a/35687575
template<typename Numeric, typename Generator = std::mt19937>
Numeric random(Numeric from, Numeric to);

// std::string readFile(const std::filesystem::path& path);

#endif