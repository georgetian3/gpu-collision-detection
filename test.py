
device_info = [
    'CL_DEVICE_TYPE',
    'CL_DEVICE_VENDOR_ID',
    'CL_DEVICE_MAX_COMPUTE_UNITS',
    'CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS',
    'CL_DEVICE_MAX_WORK_GROUP_SIZE',
    'CL_DEVICE_MAX_WORK_ITEM_SIZES',
    'CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR',
    'CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT',
    'CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT',
    'CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG',
    'CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT',
    'CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE',
    'CL_DEVICE_MAX_CLOCK_FREQUENCY',
    'CL_DEVICE_ADDRESS_BITS',
    'CL_DEVICE_MAX_READ_IMAGE_ARGS',
    'CL_DEVICE_MAX_WRITE_IMAGE_ARGS',
    'CL_DEVICE_MAX_MEM_ALLOC_SIZE',
    'CL_DEVICE_IMAGE2D_MAX_WIDTH',
    'CL_DEVICE_IMAGE2D_MAX_HEIGHT',
    'CL_DEVICE_IMAGE3D_MAX_WIDTH',
    'CL_DEVICE_IMAGE3D_MAX_HEIGHT',
    'CL_DEVICE_IMAGE3D_MAX_DEPTH',
    'CL_DEVICE_IMAGE_SUPPORT',
    'CL_DEVICE_MAX_PARAMETER_SIZE',
    'CL_DEVICE_MAX_SAMPLERS',
    'CL_DEVICE_MEM_BASE_ADDR_ALIGN',
    'CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE',
    'CL_DEVICE_SINGLE_FP_CONFIG',
    'CL_DEVICE_DOUBLE_FP_CONFIG',
    'CL_DEVICE_HALF_FP_CONFIG',
    'CL_DEVICE_GLOBAL_MEM_CACHE_TYPE',
    'CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE',
    'CL_DEVICE_GLOBAL_MEM_CACHE_SIZE',
    'CL_DEVICE_GLOBAL_MEM_SIZE',
    'CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE',
    'CL_DEVICE_MAX_CONSTANT_ARGS',
    'CL_DEVICE_LOCAL_MEM_TYPE',
    'CL_DEVICE_LOCAL_MEM_SIZE',
    'CL_DEVICE_ERROR_CORRECTION_SUPPORT',
    'CL_DEVICE_PROFILING_TIMER_RESOLUTION',
    'CL_DEVICE_ENDIAN_LITTLE',
    'CL_DEVICE_AVAILABLE',
    'CL_DEVICE_COMPILER_AVAILABLE',
    'CL_DEVICE_EXECUTION_CAPABILITIES',
    'CL_DEVICE_PLATFORM',
    'CL_DEVICE_NAME',
    'CL_DEVICE_VENDOR',
    'CL_DRIVER_VERSION',
    'CL_DEVICE_PROFILE',
    'CL_DEVICE_VERSION',
    'CL_DEVICE_EXTENSIONS',
]

def print_opencl_device_info():
    lines = []

    for x in device_info:
        lines.append(f'std::cout << "        {x}: " << devices[i].getInfo<{x}>() << \'\\n\';')

    for line in lines:
        print(line)

if __name__ == '__main__':
    print_opencl_device_info()