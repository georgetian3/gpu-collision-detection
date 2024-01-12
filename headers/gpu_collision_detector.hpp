#ifndef GPU_COLLISION_DETECTOR_HPP
#define GPU_COLLISION_DETECTOR_HPP

#define CL_HPP_ENABLE_EXCEPTIONS
#include <CL/opencl.hpp>

#include <collision_detector.hpp>


struct Node {
    int parent = -1;
    int left = -1;
    int right = -1;
    AABB aabb;
};

class GpuCollisionDetector: public CollisionDetector {

    int selected_platform_index = -1;
    int selected_device_index = -1;

    void loadConfig(const std::filesystem::path& path = "D:/gpu-collision-detection/resources/config.json");

    std::vector<Collidable> collidables;
    std::vector<Node> nodes;
    std::vector<cl_bool> processed_zeros;

    cl::Context context;
    cl::CommandQueue queue;
    cl::Buffer bufferCollidables;
    cl::Buffer bufferNodes;
    cl::Buffer bufferProcessed;
    
    cl::Kernel kernelMortonCode;
    cl::Kernel kernelConstruct;
    cl::Kernel kernelAABB;


public:

    GpuCollisionDetector();

    void setCollidables(const std::vector<Collidable>& collidables);

    std::vector<Collision> detectCollisions();


};

#endif