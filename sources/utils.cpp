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
    // https://stackoverflow.com/a/18528775
    u = (u | u << 32) & 0x001f00000000ffff;
    u = (u | u << 16) & 0x001f0000ff0000ff;
    u = (u | u <<  8) & 0x100f00f00f00f00f;
    u = (u | u <<  4) & 0x10c30c30c30c30c3;
    u = (u | u <<  2) & 0x1249249249249249;
    return u;
}

std::filesystem::path makeAbsolute(const std::filesystem::path& cwd, std::filesystem::path path) {
    return (path.is_absolute() ? path : (cwd / path)).make_preferred();
}

void printClError(const cl::Error&e, const std::string& prefix) {
    std::cerr << prefix << ' ' << e.err() << ' ' << e.what();
    exit(1);
}