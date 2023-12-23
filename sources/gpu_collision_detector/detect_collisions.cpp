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

    queue.enqueueNDRangeKernel(kernelMortonCodeAAAB, cl::NullRange, cl::NDRange(collidables.size()), cl::NullRange);
    queue.finish();

    queue.enqueueReadBuffer(bufferCollidables, CL_TRUE, 0, sizeof(Collidable) * collidables.size(), collidables.data());


    std::sort(collidables.begin(), collidables.end(), comp);
    int codes[] = {
        0b00001,
        0b00010,
        0b00100,
        0b00101,
        0b10011,
        0b11000,
        0b11001,
        0b11110
    }
    for (int i = 0; i < 8; i++) {
        collidables[i].mortonCode = codes[i];
    }
    queue.enqueueWriteBuffer(bufferCollidables, CL_TRUE, 0, sizeof(Collidable) * collidables.size(), collidables.data());


    // TODO: morton code + id sort

    try {
        queue.enqueueNDRangeKernel(kernelConstruct, cl::NullRange, cl::NDRange(collidables.size() - 1), cl::NullRange);
        queue.finish();
        queue.enqueueReadBuffer(bufferNodes, CL_TRUE, 0, sizeof(Node) * nodes.size(), nodes.data());
    } catch (const cl::Error& e) {
        printLocation();
        printClError(e);
    }
    for (int i = 0; i < nodes.size(); i++) {
        printf("%02d %02d %02d %02d", i, nodes[i].parent, nodes[i].left, nodes[i].right);
        if (i >= collidables.size() - 1) {
            std::cout << ' ' << toBits(collidables[i - collidables.size() + 1].mortonCode) << ' ' << collidables[i - collidables.size() + 1].mortonCode;
        }
        std::cout << '\n';
    }

 
    return std::vector<Collision>();

}