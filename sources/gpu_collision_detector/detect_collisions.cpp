#include <gpu_collision_detector.hpp>
#include <stopwatch.hpp>
#include <algorithm>
#include <bitset>
#include <glm/gtx/string_cast.hpp>
#include <utils.hpp>

uint64_t morton3D(double x, double y, double z) {
    return (expandBits3(x) << 2) | (expandBits3(y) << 1) | expandBits3(z);
}

bool comp(const Collidable& a, const Collidable b) {
    return a.mortonCode < b.mortonCode;
}

std::vector<Collision> GpuCollisionDetector::detectCollisions() {


    try {
        queue.enqueueNDRangeKernel(kernelMortonCode, cl::NullRange, cl::NDRange(collidables.size()));
        queue.finish();
        queue.enqueueReadBuffer(bufferCollidables, CL_TRUE, 0, sizeof(Collidable) * collidables.size(), collidables.data());
        std::sort(collidables.begin(), collidables.end(), comp);
        queue.enqueueNDRangeKernel(kernelConstruct, cl::NullRange, cl::NDRange(collidables.size() - 1));
        queue.finish();
        queue.enqueueNDRangeKernel(kernelAABB, cl::NDRange(collidables.size() - 1), cl::NDRange(collidables.size()));
        queue.finish();
        queue.enqueueReadBuffer(bufferNodes, CL_TRUE, 0, sizeof(Node) * nodes.size(), nodes.data());
    } catch (const cl::Error& e) {
        printLocation();
        printClError(e);
    }
    // for (int i = 0; i < nodes.size(); i++) {
    //     printf("%02d %02d %02d %02d %s %s", i, nodes[i].parent, nodes[i].left, nodes[i].right, glm::to_string(nodes[i].aabb.min).c_str(), glm::to_string(nodes[i].aabb.max).c_str());
    //     if (i >= collidables.size() - 1) {
    //         std::cout << ' ' << toBits(collidables[i - collidables.size() + 1].mortonCode) << ' ' << collidables[i - collidables.size() + 1].mortonCode;
    //     }
    //     std::cout << '\n';
    // }

 
    return std::vector<Collision>();

}