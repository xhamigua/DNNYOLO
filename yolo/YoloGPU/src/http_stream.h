#ifndef HTTP_STREAM_H
#define HTTP_STREAM_H
#include "yolodef.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifdef OPENCV
#include "image_opencv.h"
#else
#include "image.h"
#endif
#include <stdint.h>


// http_stream.h
LIB_API void delete_json_sender();
LIB_API void send_json_custom(char const* send_buf, int port, int timeout);

void start_timer();
void stop_timer();
double get_time();
void stop_timer_and_show();
void stop_timer_and_show_name(char* name);
void show_total_time();
double get_time_point();

void send_json(detection* dets, int nboxes, int classes, char** names, long long int frame_id, int port, int timeout);

#ifdef OPENCV
void send_mjpeg(mat_cv* mat, int port, int timeout, int quality);

#endif

#ifdef __cplusplus
}
#endif

#endif // HTTP_STREAM_H
