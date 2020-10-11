#ifndef BOX_H
#define BOX_H

#include "yolodef.h"

#ifdef __cplusplus
extern "C" {
#endif

box float_to_box(float* f);
float box_iou(box a, box b);
float box_rmse(box a, box b);
dxrep dx_box_iou(box a, box b, IOU_LOSS iou_loss);
float box_giou(box a, box b);
dbox diou(box a, box b);
boxabs to_tblr(box a);
void do_nms(box* boxes, float** probs, int total, int classes, float thresh);
void do_nms_sort_v2(box* boxes, float** probs, int total, int classes, float thresh);
box decode_box(box b, box anchor);
box encode_box(box b, box anchor);

LIB_API void do_nms_sort(detection* dets, int total, int classes, float thresh);
LIB_API void do_nms_obj(detection* dets, int total, int classes, float thresh);

#ifdef __cplusplus
}
#endif
#endif
