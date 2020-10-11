#ifndef DARKNET_API
#define DARKNET_API

#include "yolodef.h"
#ifdef GPU
    #include <cuda.h>
    #include <cuda_runtime.h>
    #include <curand.h>
    #include <cublas_v2.h>
    #pragma comment(lib, "cuda.lib")
    #ifdef CUDNN
        #include <cudnn.h>
        #ifndef USE_CMAKE_LIBS
            #pragma comment(lib, "cudnn.lib")
        #endif
    #endif
    #define BLOCK 512
    #define FULL_MASK 0xffffffff
    #define WARP_SIZE 32
    #define BLOCK_TRANSPOSE32 256
    #if defined(CUDNN_HALF) && !defined(CUDNN)
        #error "If you set CUDNN_HALF=1 then you must set CUDNN=1"
    #endif
#else

#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef GPU


void check_error(cudaError_t status);
void check_error_extended(cudaError_t status, const char* file, int line, const char* date_time);
#define CHECK_CUDA(X) check_error_extended(X, __FILE__ " : " __FUNCTION__, __LINE__,  __DATE__ " - " __TIME__ );

cublasHandle_t blas_handle();
float* cuda_make_array(float* x, size_t n);
int* cuda_make_int_array(size_t n);
int* cuda_make_int_array_new_api(int* x, size_t n);
void cuda_push_array(float* x_gpu, float* x, size_t n);
LIB_API void cuda_pull_array(float* x_gpu, float* x, size_t n);
LIB_API void cuda_pull_array_async(float* x_gpu, float* x, size_t n);
LIB_API void cuda_set_device(int n);
int cuda_get_device();
LIB_API void* cuda_get_context();
void cuda_free(float* x_gpu);
void cuda_random(float* x_gpu, size_t n);
float cuda_compare(float* x_gpu, float* x, size_t n, char* s);
dim3 cuda_gridsize(size_t n);
cudaStream_t get_cuda_stream();
cudaStream_t get_cuda_memcpy_stream();
int get_number_of_blocks(int array_size, int block_size);
int get_gpu_compute_capability(int i);

#ifdef CUDNN
cudnnHandle_t cudnn_handle();
void cudnn_check_error(cudnnStatus_t status);
void cudnn_check_error_extended(cudnnStatus_t status, const char* file, int line, const char* date_time);
#define CHECK_CUDNN(X) cudnn_check_error_extended(X, __FILE__ " : " __FUNCTION__, __LINE__,  __DATE__ " - " __TIME__ );
#endif










#else

    void cuda_set_device(int n);













#endif

#ifdef __cplusplus
}
#endif
#endif

