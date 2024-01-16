#include <gpu_collision_detector.hpp>
#include <utils.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>



bool comp(const Collidable& a, const Collidable b) {
    return a.mortonCode < b.mortonCode;
}


void GpuCollisionDetector::updatePhysics(double dt) {

    try {
        queue.enqueueNDRangeKernel(kernelMortonCode, cl::NullRange, cl::NDRange(collidables.size()));
        queue.finish();
        queue.enqueueReadBuffer(bufferCollidables, CL_TRUE, 0, sizeof(Collidable) * collidables.size(), collidables.data());
        std::sort(collidables.begin(), collidables.end(), comp);
        queue.enqueueWriteBuffer(bufferCollidables, CL_TRUE, 0, sizeof(Collidable) * collidables.size(), collidables.data());
        queue.enqueueNDRangeKernel(kernelConstruct, cl::NullRange, cl::NDRange(collidables.size() - 1));
        queue.finish();
        
        queue.enqueueWriteBuffer(bufferProcessed, CL_TRUE, 0, sizeof(cl_int) * processed_zeros.size(), processed_zeros.data());
        queue.enqueueNDRangeKernel(kernelAABB, cl::NDRange(collidables.size() - 1), cl::NDRange(collidables.size()));
        queue.finish();
        queue.enqueueReadBuffer(bufferNodes, CL_TRUE, 0, sizeof(Node) * nodes.size(), nodes.data());
        for (int i = 0; i < nodes.size(); i++) {
            printf("%02d %02d %02d %02d %s %s", i, nodes[i].parent, nodes[i].left, nodes[i].right, glm::to_string(nodes[i].aabb.min).c_str(), glm::to_string(nodes[i].aabb.max).c_str());
            if (i >= collidables.size() - 1) {
                std::cout << ' ' << toBits(collidables[i - collidables.size() + 1].mortonCode) << ' ' << collidables[i - collidables.size() + 1].mortonCode;
            }
            std::cout << "\n";
        }
        std::cout << '\n';
        queue.enqueueNDRangeKernel(kernelTraverse, cl::NullRange, cl::NDRange(collidables.size()));
        queue.finish();
        std::cout << "traversal done\n\n\n";
        kernelPhysics.setArg(1, sizeof(dt), &dt);
        queue.enqueueNDRangeKernel(kernelPhysics, cl::NullRange, cl::NDRange(collidables.size()));
        queue.finish();
    } catch (const cl::Error& e) {
        printLocation();
        printClError(e);
    }

}

std::vector<glm::mat4> GpuCollisionDetector::getModelMatrices() {
    std::vector<glm::mat4> modelMatrices;
    glm::vec3 scale;
    for (const auto& collidable: collidables) {
        switch (collidable.type) {
            case CollidableType::sphere:
            case CollidableType::cube: {
                scale = glm::vec3(collidable.length);
                break;
            }
            case CollidableType::rectangularCuboid: {
                scale = glm::vec3(collidable.xl, collidable.yl, collidable.zl);
                break;
            }
            default: {
                printLocation();
                std::cerr << "Unsupported collidable type\n";
                exit(1);
            }
        }
        modelMatrices.push_back(glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(collidable.position.x, collidable.position.y, collidable.position.z)), scale));
    }
    return modelMatrices;
}