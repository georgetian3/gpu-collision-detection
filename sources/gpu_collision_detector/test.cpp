#include <gpu_collision_detector.hpp>
#include <utils.hpp>
#include <bitset>


void GpuCollisionDetector::test() {
    
 
    cl::Context context(device);
    cl::Program::Sources sources;
 
    // kernel calculates for each element C=A+B
    std::string kernel_code(
        #include <simple_add.cl>
    );

    std::string mortonCodesSource(
        #include <morton.cl>
    );

    sources.push_back(mortonCodesSource);


 
    cl::Program program(context, sources);
    if (program.build(device) != CL_SUCCESS){
        std::cerr << " Error building: " << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device);
        exit(1);
    }
 

    int nCollidables = 10;


    std::vector<double> ds;

    for (int i = 0; i < nCollidables * 3; i++) {
        ds.push_back(random<double>(0.0, 1.0));
    }
    // // create buffers on the device
    cl::Buffer bufferCollidables(context, CL_MEM_READ_ONLY, sizeof(double) * nCollidables * 3);
    cl::Buffer bufferMortonCodes(context, CL_MEM_WRITE_ONLY, sizeof(unsigned int) * nCollidables);
 
    // create queue to which we will push commands for the device.
    cl::CommandQueue queue(context, device);


 
    queue.enqueueWriteBuffer(bufferCollidables, CL_TRUE, 0, sizeof(double) * nCollidables * 3, ds.data());

 
 
    // // // //run the kernel
    // // cl::KernelFunctor simple_add(cl::Kernel(program,"simple_add"),queue,cl::NullRange,cl::NDRange(10),cl::NullRange);
    // // simple_add(buffer_A,buffer_B,buffer_C);
 
    // //alternative way to run the kernel

    cl::Kernel kernelMortonCodes;
    
    try {
        kernelMortonCodes = cl::Kernel(program, "mortonCodes");
    } catch (std::exception e) {
        std::cerr << "Kernel exception: " << e.what();
        exit(1);
    }

    kernelMortonCodes.setArg(0, bufferCollidables);
    kernelMortonCodes.setArg(1, bufferMortonCodes);

    queue.enqueueNDRangeKernel(kernelMortonCodes, cl::NullRange, cl::NDRange(nCollidables), cl::NullRange);
    queue.finish();
 
    //read result C from the device to array C
    std::vector<unsigned int> mortonCodes(nCollidables);
    queue.enqueueReadBuffer(bufferMortonCodes, CL_TRUE, 0, sizeof(unsigned int) * nCollidables, mortonCodes.data());
 
    for (int i = 0; i < nCollidables; i++) {
        std::cout << std::bitset<sizeof(unsigned int)>(mortonCodes[i]) << '\n';
    }

}