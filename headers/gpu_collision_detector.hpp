#ifndef GPU_COLLISION_DETECTOR_HPP
#define GPU_COLLISION_DETECTOR_HPP

#define CL_HPP_TARGET_OPENCL_VERSION 120
#define CL_HPP_MINIMUM_OPENCL_VERSION 120
#include <CL/opencl.hpp>

#include <collision_detector.hpp>


class Node {
    int parent;
    int left;
    int right;
}

class GpuCollisionDetector: public CollisionDetector {

    int selected_platform_index = -1;
    int selected_device_index = -1;

    void loadConfig(const std::filesystem::path& path = "D:/gpu-collision-detection/resources/config.json");


    std::vector<Collidable> collidables;
    std::vector<Node> nodes;


    cl::Device device;
    cl::Context context;
    cl::Program::Sources sources;
    cl::Program program;
    cl::CommandQueue queue;
    cl::Buffer bufferCollidables;
    cl::Buffer bufferNodes;

    cl::Kernel kernelMortonCodeAAAB;


public:

    GpuCollisionDetector();

    void setCollidables(const std::vector<Collidable>& collidables);

    std::vector<Collision> detectCollisions();


};

#endif