#ifndef GPU_COLLISION_DETECTOR_HPP
#define GPU_COLLISION_DETECTOR_HPP

#define CL_HPP_ENABLE_EXCEPTIONS
#define CL_HPP_TARGET_OPENCL_VERSION 200
#define CL_HPP_MINIMUM_OPENCL_VERSION 200
#include <CL/opencl.hpp>

#include <collidable.hpp>

struct Node {
    AABB aabb;
    int parent = -1;
    int left = -1;
    int right = -1;
};

class GpuCollisionDetector {

    int selected_platform_index = -1;
    int selected_device_index = -1;

    void loadConfig(const std::filesystem::path& path = "D:/gpu-collision-detection/resources/config.json");

    std::vector<Collidable> collidables;
    std::vector<Node> nodes;
    std::vector<int> processed_zeros;
    std::vector<glm::mat4> sphereModelMatrices;
    std::vector<glm::mat4> cuboidModelMatrices;

    cl::Context context;
    cl::CommandQueue queue;
    
    cl::Buffer bufferCollidables;
    cl::Buffer bufferNodes;
    cl::Buffer bufferProcessed;
    cl::Buffer bufferSphereMatrices;
    cl::Buffer bufferCuboidMatrices;
    
    cl::Kernel kernelMortonCode;
    cl::Kernel kernelConstruct;
    cl::Kernel kernelAABB;
    cl::Kernel kernelTraverse;
    cl::Kernel kernelPhysics;
    cl::Kernel kernelMatrices;

public:

    GpuCollisionDetector();

    void updatePhysics(double dt);
    void setCollidables(const std::vector<Collidable>& collidables);
    void calculateModelMatrices();
    std::vector<glm::mat4> getSphereModelMatrices() const;
    std::vector<glm::mat4> getCuboidModelMatrices() const;

};

#endif