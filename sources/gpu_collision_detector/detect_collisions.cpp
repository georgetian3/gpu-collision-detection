#include <gpu_collision_detector.hpp>
#include <stopwatch.hpp>
#include <algorithm>

unsigned int expandBits(unsigned int v) {
    v = (v * 0x00010001u) & 0xFF0000FFu;
    v = (v * 0x00000101u) & 0x0F00F00Fu;
    v = (v * 0x00000011u) & 0xC30C30C3u;
    v = (v * 0x00000005u) & 0x49249249u;
    return v;
}

unsigned int morton3D(double x, double y, double z) {
    unsigned int xx = expandBits((unsigned int)(x * 1024));
    unsigned int yy = expandBits((unsigned int)(y * 1024));
    unsigned int zz = expandBits((unsigned int)(z * 1024));
    return xx * 4 + yy * 2 + zz;
}

std::vector<Collision> GpuCollisionDetector::detectCollisions() {

    // Stopwatch sw;
    // sw.start();
    
    queue.enqueueNDRangeKernel(kernelMortonCodeAAAB, cl::NullRange, cl::NDRange(collidables.size()), cl::NullRange);
    queue.finish();

    std::sort(
    // double elapsed = sw.stop();
    // std::cout << sw.stop() << '\n';
 
    return std::vector<Collision>();

}