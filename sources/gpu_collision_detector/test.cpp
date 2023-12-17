#include <gpu_collision_detector.hpp>
#include <utils.hpp>
#include <bitset>
#include <stopwatch.hpp>


unsigned int expandBits(unsigned int v) {
    v = (v * 0x00010001u) & 0xFF0000FFu;
    v = (v * 0x00000101u) & 0x0F00F00Fu;
    v = (v * 0x00000011u) & 0xC30C30C3u;
    v = (v * 0x00000005u) & 0x49249249u;
    return v;
}

unsigned int morton3D(double x, double y, double z) {
    unsigned int xx = expandBits((unsigned int)(x * 1024));
    unsigned int yy = expandBits((unsigned int)(y * 1024));
    unsigned int zz = expandBits((unsigned int)(z * 1024));
    return xx * 4 + yy * 2 + zz;
}


void GpuCollisionDetector::test() {
    

    int nCollidables = 1000000;

    std::cout << "sizeof " << sizeof(Collidable) << '\n';


    std::vector<double> ds;
    std::vector<unsigned int> mc(nCollidables);

    for (int i = 0; i < nCollidables * 3; i++) {
        ds.push_back(random<double>(0.0, 1.0));
    }

    // create buffers on the device
    cl::Buffer bufferCollidables(context, CL_MEM_READ_ONLY, sizeof(double) * nCollidables * 3);
    cl::Buffer bufferMortonCodes(context, CL_MEM_WRITE_ONLY, sizeof(unsigned int) * nCollidables);
 
    // create queue to which we will push commands for the device.
    cl::CommandQueue queue(context, device);
    cl::Kernel kernelMortonCodes;

    try {
        kernelMortonCodes = cl::Kernel(program, "mortonCodes");
    } catch (std::exception e) {
        std::cerr << "Kernel exception: " << e.what();
        exit(1);
    }

    kernelMortonCodes.setArg(0, bufferCollidables);
    kernelMortonCodes.setArg(1, bufferMortonCodes);

    Stopwatch sw;
    sw.start();
    
    queue.enqueueWriteBuffer(bufferCollidables, CL_TRUE, 0, sizeof(double) * nCollidables * 3, ds.data());
    queue.enqueueNDRangeKernel(kernelMortonCodes, cl::NullRange, cl::NDRange(nCollidables), cl::NullRange);
    queue.finish();
 
    // std::vector<unsigned int> mortonCodes(nCollidables);
    // queue.enqueueReadBuffer(bufferMortonCodes, CL_TRUE, 0, sizeof(unsigned int) * nCollidables, mortonCodes.data());

    std::cout << sw.stop() << '\n';
 
    // for (int i = 0; i < nCollidables; i++) {
    //     std::cout << std::bitset<sizeof(unsigned int) * 8>(mortonCodes[i]) << '\n';
    // }

}