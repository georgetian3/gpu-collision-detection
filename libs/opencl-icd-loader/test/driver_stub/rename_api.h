#ifndef _RENAME_API_H_
#define _RENAME_API_H_

#define clGetPlatformIDs                         ___clGetPlatformIDs
#define clGetPlatformInfo                        ___clGetPlatformInfo
#define clGetDeviceIDs                           ___clGetDeviceIDs
#define clGetDeviceInfo                          ___clGetDeviceInfo
#define clCreateSubDevices                       ___clCreateSubDevices
#define clRetainDevice                           ___clRetainDevice
#define clReleaseDevice                          ___clReleaseDevice
#define clCreateContext                          ___clCreateContext
#define clCreateContextFromType                  ___clCreateContextFromType
#define clRetainContext                          ___clRetainContext
#define clReleaseContext                         ___clReleaseContext
#define clGetContextInfo                         ___clGetContextInfo
#define clCreateCommandQueue                     ___clCreateCommandQueue
#define clSetCommandQueueProperty                ___clSetCommandQueueProperty
#define clRetainCommandQueue                     ___clRetainCommandQueue
#define clReleaseCommandQueue                    ___clReleaseCommandQueue
#define clGetCommandQueueInfo                    ___clGetCommandQueueInfo
#define clCreateBuffer                           ___clCreateBuffer
#define clCreateSubBuffer                        ___clCreateSubBuffer
#define clCreateImage                            ___clCreateImage
#define clCreateImage2D                          ___clCreateImage2D
#define clCreateImage3D                          ___clCreateImage3D
#define clRetainMemObject                        ___clRetainMemObject
#define clReleaseMemObject                       ___clReleaseMemObject
#define clGetSupportedImageFormats               ___clGetSupportedImageFormats
#define clGetMemObjectInfo                       ___clGetMemObjectInfo
#define clGetImageInfo                           ___clGetImageInfo
#define clSetMemObjectDestructorCallback         ___clSetMemObjectDestructorCallback
#define clCreateSampler                          ___clCreateSampler
#define clRetainSampler                          ___clRetainSampler
#define clReleaseSampler                         ___clReleaseSampler
#define clGetSamplerInfo                         ___clGetSamplerInfo
#define clCreateProgramWithSource                ___clCreateProgramWithSource
#define clCreateProgramWithBinary                ___clCreateProgramWithBinary
#define clCreateProgramWithBuiltInKernels        ___clCreateProgramWithBuiltInKernels
#define clRetainProgram                          ___clRetainProgram
#define clReleaseProgram                         ___clReleaseProgram
#define clBuildProgram                           ___clBuildProgram
#define clUnloadCompiler                         ___clUnloadCompiler
#define clCompileProgram                         ___clCompileProgram
#define clLinkProgram                            ___clLinkProgram
#define clUnloadPlatformCompiler                 ___clUnloadPlatformCompiler
#define clGetProgramInfo                         ___clGetProgramInfo
#define clGetProgramBuildInfo                    ___clGetProgramBuildInfo
#define clCreateKernel                           ___clCreateKernel
#define clCreateKernelsInProgram                 ___clCreateKernelsInProgram
#define clRetainKernel                           ___clRetainKernel
#define clReleaseKernel                          ___clReleaseKernel
#define clSetKernelArg                           ___clSetKernelArg
#define clGetKernelInfo                          ___clGetKernelInfo
#define clGetKernelArgInfo                       ___clGetKernelArgInfo
#define clGetKernelWorkGroupInfo                 ___clGetKernelWorkGroupInfo
#define clWaitForEvents                          ___clWaitForEvents
#define clGetEventInfo                           ___clGetEventInfo
#define clCreateUserEvent                        ___clCreateUserEvent
#define clRetainEvent                            ___clRetainEvent
#define clReleaseEvent                           ___clReleaseEvent
#define clSetUserEventStatus                     ___clSetUserEventStatus
#define clSetEventCallback                       ___clSetEventCallback
#define clGetEventProfilingInfo                  ___clGetEventProfilingInfo
#define clFlush                                  ___clFlush
#define clFinish                                 ___clFinish
#define clEnqueueReadBuffer                      ___clEnqueueReadBuffer
#define clEnqueueReadBufferRect                  ___clEnqueueReadBufferRect
#define clEnqueueWriteBuffer                     ___clEnqueueWriteBuffer
#define clEnqueueWriteBufferRect                 ___clEnqueueWriteBufferRect
#define clEnqueueCopyBuffer                      ___clEnqueueCopyBuffer
#define clEnqueueCopyBufferRect                  ___clEnqueueCopyBufferRect
#define clEnqueueFillBuffer                      ___clEnqueueFillBuffer
#define clEnqueueFillImage                       ___clEnqueueFillImage
#define clEnqueueReadImage                       ___clEnqueueReadImage
#define clEnqueueWriteImage                      ___clEnqueueWriteImage
#define clEnqueueCopyImage                       ___clEnqueueCopyImage
#define clEnqueueCopyImageToBuffer               ___clEnqueueCopyImageToBuffer
#define clEnqueueCopyBufferToImage               ___clEnqueueCopyBufferToImage
#define clEnqueueMapBuffer                       ___clEnqueueMapBuffer
#define clEnqueueMapImage                        ___clEnqueueMapImage
#define clEnqueueUnmapMemObject                  ___clEnqueueUnmapMemObject
#define clEnqueueMigrateMemObjects               ___clEnqueueMigrateMemObjects
#define clEnqueueNDRangeKernel                   ___clEnqueueNDRangeKernel
#define clEnqueueTask                            ___clEnqueueTask
#define clEnqueueNativeKernel                    ___clEnqueueNativeKernel
#define clGetExtensionFunctionAddressForPlatform ___clGetExtensionFunctionAddressForPlatform
#define clEnqueueMarkerWithWaitList              ___clEnqueueMarkerWithWaitList
#define clEnqueueBarrierWithWaitList             ___clEnqueueBarrierWithWaitList
#define clSetPrintfCallback                      ___clSetPrintfCallback
#define clEnqueueMarker                          ___clEnqueueMarker
#define clEnqueueWaitForEvents                   ___clEnqueueWaitForEvents
#define clEnqueueBarrier                         ___clEnqueueBarrier

#define clCreateFromGLBuffer                     ___clCreateFromGLBuffer
#define clCreateFromGLTexture                    ___clCreateFromGLTexture
#define clCreateFromGLTexture2D                  ___clCreateFromGLTexture2D
#define clCreateFromGLTexture3D                  ___clCreateFromGLTexture3D
#define clCreateFromGLRenderbuffer               ___clCreateFromGLRenderbuffer
#define clGetGLObjectInfo                        ___clGetGLObjectInfo
#define clGetGLTextureInfo                       ___clGetGLTextureInfo
#define clEnqueueAcquireGLObjects                ___clEnqueueAcquireGLObjects
#define clEnqueueReleaseGLObjects                ___clEnqueueReleaseGLObjects
#define clGetGLContextInfoKHR                    ___clGetGLContextInfoKHR
#define clCreateEventFromGLsyncKHR               ___clCreateEventFromGLsyncKHR
#define clCreateBufferWithProperties             ___clCreateBufferWithProperties
#define clCreateImageWithProperties              ___clCreateImageWithProperties
#define clSetContextDestructorCallback           ___clSetContextDestructorCallback

#endif /* __RENAME_API_H__ */
