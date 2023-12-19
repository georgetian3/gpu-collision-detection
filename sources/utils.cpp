#include <utils.hpp>
#include <fstream>
#include <sstream>

std::string readFile(const std::filesystem::path& path) {
    std::ifstream f(path);
    std::stringstream buffer;
    buffer << f.rdbuf();
    return buffer.str();
}

uint64_t expandBits3(double v) {
    uint64_t u = ((unsigned long long)(v * (1 << 63)));
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