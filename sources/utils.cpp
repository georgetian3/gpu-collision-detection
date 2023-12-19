#include <utils.hpp>
#include <fstream>
#include <sstream>

std::string readFile(const std::filesystem::path& path) {
    std::ifstream f(path);
    std::stringstream buffer;
    buffer << f.rdbuf();
    return buffer.str();
}

uint64_t expandBits3(double v) { // assume v in range [0, 1]
    // scale v so it fits [0, 1] to [0, 2 ^ 63]
    // then take the highest 21 bits (64 - 21 = 43)
    uint64_t u = ((uint64_t)(v * (1ull << 63))) >> 43; 
    std::cout << toBits(u) << '\n';
    //u = u >> (64 - 21);
    //std::cout << toBits(u) << '\n';
    u = (u | (u << 16)) & 0x030000FFull;
    std::cout << toBits(u) << '\n';
    u = (u | (u << 16)) & 0x030000FF;
    std::cout << toBits(u) << '\n';
    u = (u | (u <<  8)) & 0x0300F00F;
    std::cout << toBits(u) << '\n';
    u = (u | (u <<  4)) & 0x030C30C3;
    std::cout << toBits(u) << '\n';
    u = (u | (u <<  2)) & 0x09249249;
    std::cout << toBits(u) << '\n';
    
    return u;
}