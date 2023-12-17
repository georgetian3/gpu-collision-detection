#ifndef GPU_COLLISION_DETECTOR_HPP
#define GPU_COLLISION_DETECTOR_HPP

#define CL_HPP_ENABLE_EXCEPTIONS
#define CL_HPP_TARGET_OPENCL_VERSION 300
#include <CL/opencl.hpp>

#include <collision_detector.hpp>

class GpuCollisionDetector: public CollisionDetector {

    int selected_platform_index = -1;
    int selected_device_index = -1;

    void loadConfig(const std::filesystem::path& path = "D:/gpu-collision-detection/resources/config.json");


    std::vector<Collidable> collidables;

    cl::Device device;
    cl::Context context;
    cl::Program::Sources sources;
    cl::Program program;
    cl::CommandQueue queue;
    cl::Buffer bufferCollidables;

public:

    GpuCollisionDetector();


    void test();

    void setCollidables(const std::vector<Collidable>& collidables);

    std::vector<Collision> detectCollisions() final {
        std::vector<Collision> collisions;
        return collisions;
    }


};

#endif