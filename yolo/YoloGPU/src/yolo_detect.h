#ifndef __YOLO_DETECT_H__
#define __YOLO_DETECT_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifdef DARKNET_YOLOV3_EXPORTS
#define YOLODLL_API __declspec(dllexport)
#else
#define YOLODLL_API __declspec(dllimport)
#endif

#define YOLO_MAX_OBJ_NUM    64

typedef struct
{
    int class_id;
    float score;
} yolo_class;

typedef struct
{
    int x;
    int y;
    int w;
    int h;
    int class_id;
    float score;
} yolo_rect;

typedef struct
{
    int num;
    int class_id;
    yolo_rect obj_rect[YOLO_MAX_OBJ_NUM];
} yolo_object;

#define INVALID_YOLO_HANDLE     (-1)

typedef int YOLO_Handle;

YOLODLL_API YOLO_Handle yolo_initialize(const char* cfgfile, const char* weightfile, float thresh);

YOLODLL_API void yolo_detect(YOLO_Handle handle, unsigned char* data, int w, int s, int h, int c, float thresh, yolo_object* objs);

YOLODLL_API void yolo_release(YOLO_Handle handle);

#ifdef __cplusplus
}
#endif

#endif
