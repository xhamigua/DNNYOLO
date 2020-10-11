#ifndef IMAGE_OPENCV_DEF_H
#define IMAGE_OPENCV_DEF_H

#ifdef OPENCV

#include <opencv2/opencv.hpp>
#include <opencv2/core/version.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/opencv.hpp>
//#include <opencv2/opencv_modules.hpp>
//
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/video/video.hpp>
//
//// includes for OpenCV >= 3.x
//#ifndef CV_VERSION_EPOCH
//#include <opencv2/core/types.hpp>
//#include <opencv2/videoio/videoio.hpp>
//#include <opencv2/imgcodecs/imgcodecs.hpp>
//#endif

// OpenCV includes for OpenCV 2.x
#ifdef CV_VERSION_EPOCH
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/core/types_c.h>
#include <opencv2/core/version.hpp>
#endif

using std::cerr;
using std::endl;

#ifndef CV_RGB
#define CV_RGB(r, g, b) cvScalar( (b), (g), (r), 0 )
#endif

#ifndef CV_FILLED
#define CV_FILLED cv::FILLED
#endif

#ifndef CV_AA
#define CV_AA cv::LINE_AA
#endif



#endif


#endif
