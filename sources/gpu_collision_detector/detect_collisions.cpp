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

    for (const auto& collidable: collidables) {
        std::cout << collidable.toString() << '\n';
    }

    std::vector<uint64_t> want;
    for (const auto& collidable: collidables) {
        want.push_back(morton3D(collidable.position.x, collidable.position.y, collidable.position.z));
    }

    Stopwatch sw;
    sw.start();
    std::cout << "running kernel\n";
    queue.enqueueNDRangeKernel(kernelMortonCodeAAAB, cl::NullRange, cl::NDRange(collidables.size()), cl::NullRange);
    queue.finish();

    queue.enqueueReadBuffer(bufferCollidables, CL_TRUE, 0, sizeof(Collidable) * collidables.size(), collidables.data());
    std::cout << sw.stop() << '\n';

    for (int i = 0; i < collidables.size(); i++) {
        if (want[i] != collidables[i].mortonCode) {
            std::cout << i << ' ' << toBits(want[i]) << ' ' << toBits(collidables[i].mortonCode) << '\n';
            break;
        }
    }

    std::sort(collidables.begin(), collidables.end(), comp);

    for (const auto& collidable: collidables) {
        // std::cout << collidable.toString() << '\n';
        std::cout << toBits(collidable.mortonCode) << '\n';
    }

    try {
        queue.enqueueNDRangeKernel(kernelConstruct, cl::NullRange, cl::NDRange(collidables.size() - 2), cl::NullRange);
        queue.finish();
        queue.enqueueReadBuffer(bufferNodes, CL_TRUE, 0, sizeof(Node) * nodes.size(), nodes.data());
    } catch (std::exception e) {
        std::cerr << "kernelConstruct exception: " << e;
        exit(1);
    }
    for (const auto& node: nodes) {
        std::cout << node.parent << ' ' << node.left << ' ' << node.right << '\n';
    }
 
    return std::vector<Collision>();

}