#include <collision_detector.hpp>
#define CL_HPP_ENABLE_EXCEPTIONS
#define CL_HPP_TARGET_OPENCL_VERSION 300
#include <CL/opencl.hpp>
#include <fstream>
#include <sstream>
#include <json.hpp>
using json = nlohmann::json;

void GpuCollisionDetector::loadConfig(const std::filesystem::path& path) {
    std::ifstream f(path);
    json config;
    try {
        config = json::parse(f);
    } catch (...) {
        std::cerr << "Cannot parse JSON config: " << path;
        exit(1);
    }
    selected_platform_index = config.value("platform", -1);
    selected_device_index = config.value("device", -1);
}


template <class T>
std::string vectorToString(std::vector<T> v) {
    std::stringstream s;
    s << "[";
    for (size_t i = 0; i < v.size() - 1; i++) {
        s << v[i] << ", ";
    }
    s << v.back() << ']';
    return s.str();
}

void printPlatformInfo(const cl::Platform& platform) {
    std::cout << "CL_PLATFORM_PROFILE   : " << platform.getInfo<CL_PLATFORM_PROFILE>() << '\n';
    std::cout << "CL_PLATFORM_VERSION   : " << platform.getInfo<CL_PLATFORM_VERSION>() << '\n';
    std::cout << "CL_PLATFORM_NAME      : " << platform.getInfo<CL_PLATFORM_NAME>() << '\n';
    std::cout << "CL_PLATFORM_VENDOR    : " << platform.getInfo<CL_PLATFORM_VENDOR>() << '\n';
    std::cout << "CL_PLATFORM_EXTENSIONS: " << platform.getInfo<CL_PLATFORM_EXTENSIONS>() << '\n';
}
void printDeviceInfo(const cl::Device& device) {
    std::cout << "CL_DEVICE_TYPE                            : " << device.getInfo<CL_DEVICE_TYPE>() << '\n';
    std::cout << "CL_DEVICE_VENDOR_ID                       : " << device.getInfo<CL_DEVICE_VENDOR_ID>() << '\n';
    std::cout << "CL_DEVICE_MAX_COMPUTE_UNITS               : " << device.getInfo<CL_DEVICE_MAX_COMPUTE_UNITS>() << '\n';
    std::cout << "CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS        : " << device.getInfo<CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS>() << '\n';
    std::cout << "CL_DEVICE_MAX_WORK_GROUP_SIZE             : " << device.getInfo<CL_DEVICE_MAX_WORK_GROUP_SIZE>() << '\n';
    std::cout << "CL_DEVICE_MAX_WORK_ITEM_SIZES             : " << vectorToString(device.getInfo<CL_DEVICE_MAX_WORK_ITEM_SIZES>()) << '\n';
    std::cout << "CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR     : " << device.getInfo<CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR>() << '\n';
    std::cout << "CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT    : " << device.getInfo<CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT>() << '\n';
    std::cout << "CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT      : " << device.getInfo<CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT>() << '\n';
    std::cout << "CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG     : " << device.getInfo<CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG>() << '\n';
    std::cout << "CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT    : " << device.getInfo<CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT>() << '\n';
    std::cout << "CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE   : " << device.getInfo<CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE>() << '\n';
    std::cout << "CL_DEVICE_MAX_CLOCK_FREQUENCY             : " << device.getInfo<CL_DEVICE_MAX_CLOCK_FREQUENCY>() << '\n';
    std::cout << "CL_DEVICE_ADDRESS_BITS                    : " << device.getInfo<CL_DEVICE_ADDRESS_BITS>() << '\n';
    std::cout << "CL_DEVICE_MAX_READ_IMAGE_ARGS             : " << device.getInfo<CL_DEVICE_MAX_READ_IMAGE_ARGS>() << '\n';
    std::cout << "CL_DEVICE_MAX_WRITE_IMAGE_ARGS            : " << device.getInfo<CL_DEVICE_MAX_WRITE_IMAGE_ARGS>() << '\n';
    std::cout << "CL_DEVICE_MAX_MEM_ALLOC_SIZE              : " << device.getInfo<CL_DEVICE_MAX_MEM_ALLOC_SIZE>() << '\n';
    std::cout << "CL_DEVICE_IMAGE2D_MAX_WIDTH               : " << device.getInfo<CL_DEVICE_IMAGE2D_MAX_WIDTH>() << '\n';
    std::cout << "CL_DEVICE_IMAGE2D_MAX_HEIGHT              : " << device.getInfo<CL_DEVICE_IMAGE2D_MAX_HEIGHT>() << '\n';
    std::cout << "CL_DEVICE_IMAGE3D_MAX_WIDTH               : " << device.getInfo<CL_DEVICE_IMAGE3D_MAX_WIDTH>() << '\n';
    std::cout << "CL_DEVICE_IMAGE3D_MAX_HEIGHT              : " << device.getInfo<CL_DEVICE_IMAGE3D_MAX_HEIGHT>() << '\n';
    std::cout << "CL_DEVICE_IMAGE3D_MAX_DEPTH               : " << device.getInfo<CL_DEVICE_IMAGE3D_MAX_DEPTH>() << '\n';
    std::cout << "CL_DEVICE_IMAGE_SUPPORT                   : " << device.getInfo<CL_DEVICE_IMAGE_SUPPORT>() << '\n';
    std::cout << "CL_DEVICE_MAX_PARAMETER_SIZE              : " << device.getInfo<CL_DEVICE_MAX_PARAMETER_SIZE>() << '\n';
    std::cout << "CL_DEVICE_MAX_SAMPLERS                    : " << device.getInfo<CL_DEVICE_MAX_SAMPLERS>() << '\n';
    std::cout << "CL_DEVICE_MEM_BASE_ADDR_ALIGN             : " << device.getInfo<CL_DEVICE_MEM_BASE_ADDR_ALIGN>() << '\n';
    std::cout << "CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE        : " << device.getInfo<CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE>() << '\n';
    std::cout << "CL_DEVICE_SINGLE_FP_CONFIG                : " << device.getInfo<CL_DEVICE_SINGLE_FP_CONFIG>() << '\n';
    std::cout << "CL_DEVICE_DOUBLE_FP_CONFIG                : " << device.getInfo<CL_DEVICE_DOUBLE_FP_CONFIG>() << '\n';
    std::cout << "CL_DEVICE_HALF_FP_CONFIG                  : " << device.getInfo<CL_DEVICE_HALF_FP_CONFIG>() << '\n';
    std::cout << "CL_DEVICE_GLOBAL_MEM_CACHE_TYPE           : " << device.getInfo<CL_DEVICE_GLOBAL_MEM_CACHE_TYPE>() << '\n';
    std::cout << "CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE       : " << device.getInfo<CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE>() << '\n';
    std::cout << "CL_DEVICE_GLOBAL_MEM_CACHE_SIZE           : " << device.getInfo<CL_DEVICE_GLOBAL_MEM_CACHE_SIZE>() << '\n';
    std::cout << "CL_DEVICE_GLOBAL_MEM_SIZE                 : " << device.getInfo<CL_DEVICE_GLOBAL_MEM_SIZE>() << '\n';
    std::cout << "CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE        : " << device.getInfo<CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE>() << '\n';
    std::cout << "CL_DEVICE_MAX_CONSTANT_ARGS               : " << device.getInfo<CL_DEVICE_MAX_CONSTANT_ARGS>() << '\n';
    std::cout << "CL_DEVICE_LOCAL_MEM_TYPE                  : " << device.getInfo<CL_DEVICE_LOCAL_MEM_TYPE>() << '\n';
    std::cout << "CL_DEVICE_LOCAL_MEM_SIZE                  : " << device.getInfo<CL_DEVICE_LOCAL_MEM_SIZE>() << '\n';
    std::cout << "CL_DEVICE_ERROR_CORRECTION_SUPPORT        : " << device.getInfo<CL_DEVICE_ERROR_CORRECTION_SUPPORT>() << '\n';
    std::cout << "CL_DEVICE_PROFILING_TIMER_RESOLUTION      : " << device.getInfo<CL_DEVICE_PROFILING_TIMER_RESOLUTION>() << '\n';
    std::cout << "CL_DEVICE_ENDIAN_LITTLE                   : " << device.getInfo<CL_DEVICE_ENDIAN_LITTLE>() << '\n';
    std::cout << "CL_DEVICE_AVAILABLE                       : " << device.getInfo<CL_DEVICE_AVAILABLE>() << '\n';
    std::cout << "CL_DEVICE_COMPILER_AVAILABLE              : " << device.getInfo<CL_DEVICE_COMPILER_AVAILABLE>() << '\n';
    std::cout << "CL_DEVICE_EXECUTION_CAPABILITIES          : " << device.getInfo<CL_DEVICE_EXECUTION_CAPABILITIES>() << '\n';
    // std::cout << "CL_DEVICE_PLATFORM: " << device.getInfo<CL_DEVICE_PLATFORM>() << '\n';
    std::cout << "CL_DEVICE_NAME                            : " << device.getInfo<CL_DEVICE_NAME>() << '\n';
    std::cout << "CL_DEVICE_VENDOR                          : " << device.getInfo<CL_DEVICE_VENDOR>() << '\n';
    std::cout << "CL_DRIVER_VERSION                         : " << device.getInfo<CL_DRIVER_VERSION>() << '\n';
    std::cout << "CL_DEVICE_PROFILE                         : " << device.getInfo<CL_DEVICE_PROFILE>() << '\n';
    std::cout << "CL_DEVICE_VERSION                         : " << device.getInfo<CL_DEVICE_VERSION>() << '\n';
    std::cout << "CL_DEVICE_EXTENSIONS                      : " << device.getInfo<CL_DEVICE_EXTENSIONS>() << '\n';

}
void printOpenclInfo() {
    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);
    for (size_t i = 0; i < platforms.size(); i++) {
        std::cout << std::string(80, '#') << '\n';
        std::cout << "Platform " << i << ":\n";
        printPlatformInfo(platforms[i]);    
        std::vector<cl::Device> devices;
        platforms[i].getDevices(CL_DEVICE_TYPE_ALL, &devices);
        for (size_t j = 0; j < devices.size(); j++) {
            std::cout << std::string(80, '-') << '\n';
            std::cout << "Device " << j << ":\n";
            printDeviceInfo(devices[i]);
            std::cout << std::string(80, '-') << '\n';
        }
        std::cout << std::string(80, '#') << '\n';
    }
}

GpuCollisionDetector::GpuCollisionDetector() {

    printOpenclInfo();
    loadConfig();

    // select platform
    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);
    if (platforms.empty()) {
        std::cerr << "No platforms found";
        exit(1);
    }
    if (selected_platform_index >= platforms.size() || selected_device_index < 0) {
        std::cout << "Selected platform index " << selected_platform_index << " doesn't exist, defaulting to 0\n";
        selected_platform_index = 0;
    }
    cl::Platform platform = platforms[selected_platform_index];
    std::cout << "Selected platform:\n";
    printPlatformInfo(platform);

    // select device
    std::vector<cl::Device> devices;
    platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);
    if (devices.empty()) {
        std::cerr << "No devices found";
        exit(1);
    }
    if (selected_device_index >= devices.size() || selected_device_index < 0) {
        std::cout << "Selected device index " << selected_device_index << " doesn't exist, defaulting to 0\n";
        selected_device_index = 0;
    }
    cl::Device device = devices[selected_device_index];
    std::cout << "Selected device:\n";
    printDeviceInfo(device);


 
    cl::Context context(device);
 
    cl::Program::Sources sources;
 
    // kernel calculates for each element C=A+B
    std::string kernel_code(
        #include <simple_add.cl>
    );

    sources.push_back({kernel_code.c_str(),kernel_code.length()});


 
    cl::Program program(context,sources);
    if(program.build(device)!=CL_SUCCESS){
        std::cout<<" Error building: "<<program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device)<<"\n";
        exit(1);
    }
 

 
    // // create buffers on the device
    cl::Buffer buffer_A(context,CL_MEM_READ_WRITE,sizeof(int)*10);
    cl::Buffer buffer_B(context,CL_MEM_READ_WRITE,sizeof(int)*10);
    cl::Buffer buffer_C(context,CL_MEM_READ_WRITE,sizeof(int)*10);
 
    int A[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int B[] = {0, 1, 2, 0, 1, 2, 0, 1, 2, 0};
 
    // //create queue to which we will push commands for the device.
    cl::CommandQueue queue(context,device);


 
    // //write arrays A and B to the device
    queue.enqueueWriteBuffer(buffer_A,CL_TRUE,0,sizeof(int)*10,A);
    queue.enqueueWriteBuffer(buffer_B,CL_TRUE,0,sizeof(int)*10,B);
 
 
    // // //run the kernel
    // cl::KernelFunctor simple_add(cl::Kernel(program,"simple_add"),queue,cl::NullRange,cl::NDRange(10),cl::NullRange);
    // simple_add(buffer_A,buffer_B,buffer_C);
 
    //alternative way to run the kernel

    cl::Kernel kernel_add
    
    try {
        kernel_add = cl::Kernel(program,"simple_add");
    } catch (Exception e) {
        std::cerr << "Kernel exception: " << e;
        exit(1);
    }

    kernel_add.setArg(0,buffer_A);
    kernel_add.setArg(1,buffer_B);
    kernel_add.setArg(2,buffer_C);

    queue.enqueueNDRangeKernel(kernel_add,cl::NullRange,cl::NDRange(10),cl::NullRange);
    queue.finish();
 
    int C[10];
    //read result C from the device to array C
    queue.enqueueReadBuffer(buffer_C,CL_TRUE,0,sizeof(int)*10,C);
 
    std::cout<<" result: \n";
    for(int i=0;i<10;i++){
        std::cout<<C[i]<<" ";
    }

}