#include <gpu_collision_detector.hpp>
#include <stopwatch.hpp>
#include <algorithm>
#include <bitset>
#include <glm/gtx/string_cast.hpp>
#include <utils.hpp>

uint64_t expandBits(double v) {
    uint64_t u = (unsigned int)(v * (1 << 21));
    std::cout << toBits(u);
    u = (u * 0x00010001u) & 0xFF0000FFu;
    std::cout << toBits(u);
    u = (u * 0x00000101u) & 0x0F00F00Fu;
    std::cout << toBits(u);
    u = (u * 0x00000011u) & 0xC30C30C3u;
    std::cout << toBits(u);
    u = (u * 0x00000005u) & 0x49249249u;
    std::cout << toBits(u);
    return u;
}

uint64_t morton3D(double x, double y, double z) {
    return (expandBits(x) << 2) | (expandBits(y) << 1) | expandBits(z);
}

std::vector<Collision> GpuCollisionDetector::detectCollisions() {

    std::vector<uint64_t> want;
    for (const auto& collidable: collidables) {
        std::cout << collidable.toString() << '\n';
        want.push_back(morton3D(collidable.position.x, collidable.position.y, collidable.position.z));
    }

    Stopwatch sw;
    sw.start();
    
    queue.enqueueNDRangeKernel(kernelMortonCodeAAAB, cl::NullRange, cl::NDRange(collidables.size()), cl::NullRange);
    queue.finish();

    queue.enqueueReadBuffer(bufferCollidables, CL_TRUE, 0, sizeof(Collidable) * collidables.size(), collidables.data());
    std::cout << sw.stop() << '\n';

    for (int i = 0; i < collidables.size(); i++) {
        std::cout << toBits(want[i]) << ' ' << toBits(collidables[i].mortonCode) << ' ' << (want[i] == collidables[i].mortonCode) << '\n';
    }
 
    return std::vector<Collision>();

}