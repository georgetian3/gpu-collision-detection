#include <gpu_collision_detector.hpp>
#include <utils.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <stopwatch.hpp>


bool comp(const Collidable& a, const Collidable b) {
    return a.mortonCode < b.mortonCode;
}


void GpuCollisionDetector::updatePhysics(double dt) {
    try {
        // calculate morton codes
        queue.enqueueNDRangeKernel(kernelMortonCode, cl::NullRange, cl::NDRange(collidables.size()));
        queue.finish();
        // sort collidables based on their morton codes
        queue.enqueueReadBuffer(bufferCollidables, CL_TRUE, 0, sizeof(Collidable) * collidables.size(), collidables.data());
        std::sort(collidables.begin(), collidables.end(), comp);
        queue.enqueueWriteBuffer(bufferCollidables, CL_TRUE, 0, sizeof(Collidable) * collidables.size(), collidables.data());
        // construct BVH
        queue.enqueueNDRangeKernel(kernelConstruct, cl::NullRange, cl::NDRange(collidables.size() - 1));
        queue.finish();
        queue.enqueueReadBuffer(bufferNodes, CL_TRUE, 0, sizeof(Node) * nodes.size(), nodes.data());
        // calculate AABBs
        queue.enqueueWriteBuffer(bufferProcessed, CL_TRUE, 0, sizeof(cl_int) * processed_zeros.size(), processed_zeros.data());
        queue.enqueueNDRangeKernel(kernelAABB, cl::NDRange(collidables.size() - 1), cl::NDRange(collidables.size()));
        queue.finish();
        // traverse tree, perform narrow phase collision detection
        queue.enqueueNDRangeKernel(kernelTraverse, cl::NullRange, cl::NDRange(collidables.size()));
        queue.finish();
        // update position and velocity due to gravity
        kernelPhysics.setArg(2, sizeof(double), &dt);
        queue.enqueueNDRangeKernel(kernelPhysics, cl::NullRange, cl::NDRange(collidables.size()));
        queue.finish();
    } catch (const cl::Error& e) {
        printLocation();
        printClError(e);
    }

}

void GpuCollisionDetector::calculateModelMatrices() {
    // calculates the model matrix of each `Collidable` on the GPU
    try {
        queue.enqueueNDRangeKernel(kernelMatrices, cl::NullRange, cl::NDRange(collidables.size()));
        queue.finish();
        queue.enqueueReadBuffer(bufferSphereMatrices, CL_TRUE, 0, sizeof(glm::mat4) * collidables.size(), sphereModelMatrices.data());
        queue.enqueueReadBuffer(bufferCuboidMatrices, CL_TRUE, 0, sizeof(glm::mat4) * collidables.size(), cuboidModelMatrices.data());
    } catch (const cl::Error& e) {
        printLocation();
        printClError(e);
    }
}

std::vector<glm::mat4> GpuCollisionDetector::getSphereModelMatrices() const {
    return sphereModelMatrices;
}
std::vector<glm::mat4> GpuCollisionDetector::getCuboidModelMatrices() const {
    return cuboidModelMatrices;
}