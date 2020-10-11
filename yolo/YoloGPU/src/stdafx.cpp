

#include "stdafx.h"

//Á´½Ópthread
#pragma comment(lib, "pthread_static.lib")
#ifdef OPENCV
    //Á´½Óopencv
    #pragma comment(lib, "opencv_mpeg.lib")
    //#pragma comment(lib, "opencv_world.lib")
    //#pragma comment(lib, "ffmpeg_static.lib")
    //#pragma comment(lib, "opencv_gpu.lib")
    #pragma comment(lib, "opengl32.lib")
    #pragma comment(lib, "vfw32.lib")
    #pragma comment(lib, "comctl32.lib")
#endif

#ifdef GPU
    #pragma comment(lib, "cublas.lib")
    #pragma comment(lib, "curand.lib")
    #pragma comment(lib, "cudart.lib")
#endif
