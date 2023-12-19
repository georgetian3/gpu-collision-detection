#include <gpu_collision_detector.hpp>
#include <stopwatch.hpp>
#include <algorithm>
#include <bitset>
#include <glm/gtx/string_cast.hpp>
#include <utils.hpp>



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