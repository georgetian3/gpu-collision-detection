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
    Stopwatch sw;
    try {
        sw.start();
        queue.enqueueNDRangeKernel(kernelMortonCode, cl::NullRange, cl::NDRange(collidables.size()));
        queue.finish();
        // std::cout << sw.reset() << ' ';
        sw.start();
        queue.enqueueReadBuffer(bufferCollidables, CL_TRUE, 0, sizeof(Collidable) * collidables.size(), collidables.data());
        std::sort(collidables.begin(), collidables.end(), comp);
        // std::cout << sw.reset() << ' ';
        sw.start();
        queue.enqueueWriteBuffer(bufferCollidables, CL_TRUE, 0, sizeof(Collidable) * collidables.size(), collidables.data());
        queue.enqueueNDRangeKernel(kernelConstruct, cl::NullRange, cl::NDRange(collidables.size() - 1));
        queue.finish();
        // std::cout << sw.reset() << ' ';
        
        sw.start();
        queue.enqueueWriteBuffer(bufferProcessed, CL_TRUE, 0, sizeof(cl_int) * processed_zeros.size(), processed_zeros.data());
        queue.enqueueNDRangeKernel(kernelAABB, cl::NDRange(collidables.size() - 1), cl::NDRange(collidables.size()));
        queue.finish();
        // std::cout << sw.reset() << ' ';
        sw.start();
        queue.enqueueReadBuffer(bufferNodes, CL_TRUE, 0, sizeof(Node) * nodes.size(), nodes.data());
        // for (int i = 0; i < nodes.size(); i++) {
        //     printf("%02d %02d %02d %02d %s %s", i, nodes[i].parent, nodes[i].left, nodes[i].right, glm::to_string(nodes[i].aabb.min).c_str(), glm::to_string(nodes[i].aabb.max).c_str());
        //     if (i >= collidables.size() - 1) {
        //         // std::cout << ' ' << toBits(collidables[i - collidables.size() + 1].mortonCode) << ' ' << collidables[i - collidables.size() + 1].mortonCode;
        //     }
        //     // std::cout << "\n";
        // }
        // std::cout << '\n';
        queue.enqueueNDRangeKernel(kernelTraverse, cl::NullRange, cl::NDRange(collidables.size()));
        queue.finish();
        // std::cout << sw.reset() << ' ';
        sw.start();
        kernelPhysics.setArg(1, sizeof(dt), &dt);
        queue.enqueueNDRangeKernel(kernelPhysics, cl::NullRange, cl::NDRange(collidables.size()));
        queue.finish();
        // std::cout << sw.reset() << '\n';
    } catch (const cl::Error& e) {
        printLocation();
        printClError(e);
    }

}

std::vector<glm::mat4> GpuCollisionDetector::getModelMatrices() {
    // calculates the model matrix of each `Collidable` on the GPU
    try {
        queue.enqueueNDRangeKernel(kernelMatrices, cl::NullRange, cl::NDRange(collidables.size()));
        queue.finish();
        queue.enqueueReadBuffer(bufferMatrices, CL_TRUE, 0, sizeof(glm::mat4) * collidables.size(), modelMatrices.data());
    } catch (const cl::Error& e) {
        printLocation();
        printClError(e);
    }
    return modelMatrices;
}