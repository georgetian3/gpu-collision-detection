#include <gpu_collision_detector.hpp>
#include <utils.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


void GpuCollisionDetector::updatePhysics(double dt) {

    detectCollisions();

    try {
        kernelPhysics.setArg(1, sizeof(dt), &dt);
        printLocation();
        queue.enqueueNDRangeKernel(kernelPhysics, cl::NullRange, cl::NDRange(collidables.size()));
        printLocation();
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
            default: {
                printLocation();
                std::cerr << "Unsupported collidable type\n";
                exit(1);
            }
        }
        modelMatrices.push_back(glm::translate(glm::scale(glm::mat4(1.0f), scale), glm::vec3(collidable.position.x, collidable.position.y, collidable.position.z)));
    }
    return modelMatrices;
}