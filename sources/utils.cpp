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
    u = (u * 0x00000101u) & 0x0F00F00Fu;
    std::cout << toBits(u) << '\n';
    u = (u * 0x00000011u) & 0xC30C30C3u;
    std::cout << toBits(u) << '\n';
    u = (u * 0x00000005u) & 0x49249249u;
    std::cout << toBits(u) << '\n';
    return u;
}