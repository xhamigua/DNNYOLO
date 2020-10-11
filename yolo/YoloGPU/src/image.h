#ifndef IMAGE_H
#define IMAGE_H

#include "yolodef.h"

#ifdef __cplusplus
extern "C" {
#endif

void rgb_to_hsv(image im);
int compare_by_probs(const void* a_ptr, const void* b_ptr);
float get_color(int c, int x, int max);
void flip_image(image a);
void draw_box(image a, int x1, int y1, int x2, int y2, float r, float g, float b);
void draw_box_width(image a, int x1, int y1, int x2, int y2, int w, float r, float g, float b);
void draw_bbox(image a, box bbox, int w, float r, float g, float b);
void draw_label(image a, int r, int c, image label, const float* rgb);
void draw_detections(image im, int num, float thresh, box* boxes, float** probs, char** names, image** labels, int classes);
void draw_detections_v3(image im, detection* dets, int num, float thresh, char** names, image** alphabet, int classes, int ext_output);
void print_image(image m);
LIB_API image make_image(int w, int h, int c);
image make_empty_image(int w, int h, int c);
image make_random_image(int w, int h, int c);
LIB_API image resize_image(image im, int w, int h);
LIB_API void copy_image_from_bytes(image im, char* pdata);
LIB_API image letterbox_image(image im, int w, int h);
LIB_API void rgbgr_image(image im);
LIB_API image load_image_color(char* filename, int w, int h);
LIB_API void free_image(image m);
image float_to_image(int w, int h, int c, float* data);
image copy_image(image p);
image load_image_stb(char* filename, int channels);
image load_image_buf(unsigned char* BMPDATA, int len);
image** load_alphabet();
float bilinear_interpolate(image im, float x, float y, int c);
image get_image_layer(image m, int l);

detection_with_class* get_actual_detections(detection* dets, int dets_num, float thresh, int* selected_detections_num, char** names);
image grayscale_image(image im);
image threshold_image(image im, float thresh);
image collapse_image_layers(image source, int border);
image collapse_images_horz(image* ims, int n);
image collapse_images_vert(image* ims, int n);
image random_augment_image(image im, float angle, float aspect, int low, int high, int size);
image image_distance(image a, image b);
void scale_image(image m, float s);
image crop_image(image im, int dx, int dy, int w, int h);
image random_crop_image(image im, int w, int h);
void random_distort_image(image im, float hue, float saturation, float exposure);
void fill_image(image m, float s);
void letterbox_image_into(image im, int w, int h, image boxed);
image resize_min(image im, int min);
image resize_max(image im, int max);
void translate_image(image m, float s);
void normalize_image(image p);
void normalize_image2(image p);
image rotate_image(image m, float rad);
void rotate_image_cw(image im, int times);
void embed_image(image source, image dest, int dx, int dy);
void saturate_image(image im, float sat);
void exposure_image(image im, float sat);
void distort_image(image im, float hue, float sat, float val);
void saturate_exposure_image(image im, float sat, float exposure);
void hsv_to_rgb(image im);
void constrain_image(image im);
void composite_3d(char* f1, char* f2, char* out, int delta);
int best_3d_shift_r(image a, image b, int min, int max);

void show_image_normalized(image im, const char* name);
void save_image_png(image im, const char* name);
void save_image(image p, const char* name);
void show_images(image* ims, int n, char* window);
void show_image_layers(image p, char* name);
void show_image_collapsed(image p, char* name);

image load_image(char* filename, int w, int h, int c);
void show_image(image p, const char* name);
void test_resize(char* filename);
int wait_key_cv(int delay);
int wait_until_press_key_cv();
void destroy_all_windows_cv();

#ifdef __cplusplus
}
#endif

#endif
