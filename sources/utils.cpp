#include <utils.hpp>
#include <fstream>
#include <sstream>

std::string readFile(const std::filesystem::path& path) {
    std::ifstream f(path);
    std::stringstream buffer;
    buffer << f.rdbuf();
    return buffer.str();
}