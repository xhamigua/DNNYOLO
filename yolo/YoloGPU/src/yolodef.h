#ifndef YOLODEF_H
#define YOLODEF_H
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#ifdef GPU
#include <cuda.h>
#include <cuda_runtime.h>
#include <curand.h>
#include <cublas_v2.h>
#ifdef CUDNN
#include <cudnn.h>
enum { cudnn_fastest, cudnn_smallest };
#endif
#endif
#if defined(_MSC_VER) && defined(_DEBUG)
#include <crtdbg.h>
#endif

#if defined(_MSC_VER) && _MSC_VER < 1900
    #define inline __inline
#endif
#if defined(DEBUG) && !defined(_CRTDBG_MAP_ALLOC)
    #define _CRTDBG_MAP_ALLOC
#endif

#ifndef __COMPAR_FN_T
#define __COMPAR_FN_T
typedef int(*__compar_fn_t)(const void*, const void*);
#ifdef __USE_GNU
typedef __compar_fn_t comparison_fn_t;
#endif
#endif

#ifndef LIB_API
    #define LIB_API __declspec(dllexport)
#endif

//noooo
#define SECRET_NUM -1234

extern int gpu_index;

//image======================================================
typedef enum
{
    PNG, BMP, TGA, JPG
} IMTYPE;

typedef struct image
{
    int w;
    int h;
    int c;
    float* data;
} image;

//box========================================================
typedef enum
{
    IOU, GIOU, MSE
} IOU_LOSS;

typedef struct box
{
    float x, y, w, h;
} box;

typedef struct boxabs
{
    float left, right, top, bot;
} boxabs;

typedef struct dxrep
{
    float dt, db, dl, dr;
} dxrep;

typedef struct ious
{
    float iou, giou;
    dxrep dx_iou;
    dxrep dx_giou;
} ious;

typedef struct detection
{
    box bbox;
    int classes;
    float* prob;
    float* mask;
    float objectness;
    int sort_class;
} detection;

typedef struct
{
    float dx, dy, dw, dh;
} dbox;

typedef struct detection_with_class
{
    detection det;
    // The most probable class id: the best class index in this->prob.
    // Is filled temporary when processing results, otherwise not initialized
    int best_class;
} detection_with_class;

//activations===============================================
typedef enum
{
    LOGISTIC, RELU, RELIE, LINEAR, RAMP, TANH, PLSE, LEAKY, ELU, LOGGY, STAIR, HARDTAN, LHTAN, SELU
} ACTIVATION;

typedef enum
{
    MULT, ADD, SUB, DIV
} BINARY_ACTIVATION;

//matrix====================================================
typedef struct matrix
{
    int rows, cols;
    float** vals;
} matrix;

typedef struct
{
    int* assignments;
    matrix centers;
} model;

//tree======================================================
typedef struct tree
{
    int* leaf;
    int n;
    int* parent;
    int* child;
    int* group;
    char** name;

    int groups;
    int* group_size;
    int* group_offset;
} tree;

//data======================================================
typedef struct data
{
    int w, h;
    matrix X;
    matrix y;
    int shallow;
    int* num_boxes;
    box** boxes;
} data;

typedef enum
{
    CLASSIFICATION_DATA, DETECTION_DATA, CAPTCHA_DATA, REGION_DATA, IMAGE_DATA, COMPARE_DATA, WRITING_DATA, SWAG_DATA, TAG_DATA, OLD_CLASSIFICATION_DATA, STUDY_DATA, DET_DATA, SUPER_DATA, LETTERBOX_DATA, REGRESSION_DATA, SEGMENTATION_DATA, INSTANCE_DATA, ISEG_DATA
} data_type;

typedef struct load_args
{
    int threads;
    char** paths;
    char* path;
    int n;
    int m;
    char** labels;
    int h;
    int w;
    int c; // color depth
    int out_w;
    int out_h;
    int nh;
    int nw;
    int num_boxes;
    int min, max, size;
    int classes;
    int background;
    int scale;
    int center;
    int coords;
    int mini_batch;
    int track;
    int augment_speed;
    int show_imgs;
    float jitter;
    int flip;
    int blur;
    int mixup;
    float angle;
    float aspect;
    float saturation;
    float exposure;
    float hue;
    data* d;
    image* im;
    image* resized;
    data_type type;
    tree* hierarchy;
} load_args;

typedef struct box_label
{
    int id;
    float x, y, w, h;
    float left, right, top, bottom;
} box_label;

//option_list===============================================
typedef struct
{
    int classes;
    char** names;
} metadata;

//parser====================================================


//layer=====================================================
typedef enum
{
    CONVOLUTIONAL,
    DECONVOLUTIONAL,
    CONNECTED,
    MAXPOOL,
    SOFTMAX,
    DETECTION,
    DROPOUT,
    CROP,
    ROUTE,
    COST,
    NORMALIZATION,
    AVGPOOL,
    LOCAL,
    SHORTCUT,
    ACTIVE,
    RNN,
    GRU,
    LSTM,
    CONV_LSTM,
    CRNN,
    BATCHNORM,
    NETWORK,
    XNOR,
    REGION,
    YOLO,
    ISEG,
    REORG,
    REORG_OLD,
    UPSAMPLE,
    LOGXENT,
    L2NORM,
    BLANK
} LAYER_TYPE;

typedef enum
{
    SSE, MASKED, L1, SEG, SMOOTH, WGAN
} COST_TYPE;

typedef struct update_args
{
    int batch;
    float learning_rate;
    float momentum;
    float decay;
    int adam;
    float B1;
    float B2;
    float eps;
    int t;
} update_args;

typedef struct _layer
{
    LAYER_TYPE type;
    ACTIVATION activation;
    COST_TYPE cost_type;
    void(*forward)      (struct _layer, struct network_state);
    void(*backward)     (struct _layer, struct network_state);
    void(*update)       (struct _layer, int, float, float, float);
    void(*forward_gpu)   (struct _layer, struct network_state);
    void(*backward_gpu)  (struct _layer, struct network_state);
    void(*update_gpu)    (struct _layer, int, float, float, float);
    struct _layer* share_layer;
    int batch_normalize;
    int shortcut;
    int batch;
    int forced;
    int flipped;
    int inputs;
    int outputs;
    int nweights;
    int nbiases;
    int extra;
    int truths;
    int h, w, c;
    int out_h, out_w, out_c;
    int n;
    int max_boxes;
    int groups;
    int size;
    int side;
    int stride;
    int dilation;
    int reverse;
    int flatten;
    int spatial;
    int pad;
    int sqrt;
    int flip;
    int index;
    int binary;
    int xnor;
    int peephole;
    int use_bin_output;
    int steps;
    int state_constrain;
    int hidden;
    int truth;
    float smooth;
    float dot;
    float angle;
    float jitter;
    float saturation;
    float exposure;
    float shift;
    float ratio;
    float learning_rate_scale;
    float clip;
    int focal_loss;
    int noloss;
    int softmax;
    int classes;
    int coords;
    int background;
    int rescore;
    int objectness;
    int does_cost;
    int joint;
    int noadjust;
    int reorg;
    int log;
    int tanh;
    int* mask;
    int total;
    float bflops;

    int adam;
    float B1;
    float B2;
    float eps;

    int t;

    float alpha;
    float beta;
    float kappa;

    float coord_scale;
    float object_scale;
    float noobject_scale;
    float mask_scale;
    float class_scale;
    int bias_match;
    int random;
    float ignore_thresh;
    float truth_thresh;
    float thresh;
    float focus;
    int classfix;
    int absolute;

    int onlyforward;
    int stopbackward;
    int dontload;
    int dontsave;
    int dontloadscales;
    int numload;

    float temperature;
    float probability;
    float scale;

    char*   cweights;
    int*    indexes;
    int*    input_layers;
    int*    input_sizes;
    int*    map;
    int*    counts;
    float** sums;
    float* rand;
    float* cost;
    float* state;
    float* prev_state;
    float* forgot_state;
    float* forgot_delta;
    float* state_delta;
    float* combine_cpu;
    float* combine_delta_cpu;

    float* concat;
    float* concat_delta;

    float* binary_weights;

    float* biases;
    float* bias_updates;

    float* scales;
    float* scale_updates;

    float* weights;
    float* weight_updates;

    float scale_x_y;
    float iou_normalizer;
    float cls_normalizer;
    IOU_LOSS iou_loss;

    char* align_bit_weights_gpu;
    float* mean_arr_gpu;
    float* align_workspace_gpu;
    float* transposed_align_workspace_gpu;
    int align_workspace_size;

    char* align_bit_weights;
    float* mean_arr;
    int align_bit_weights_size;
    int lda_align;
    int new_lda;
    int bit_align;

    float* col_image;
    float* delta;
    float* output;
    int delta_pinned;
    int output_pinned;
    float* loss;
    float* squared;
    float* norms;

    float* spatial_mean;
    float* mean;
    float* variance;

    float* mean_delta;
    float* variance_delta;

    float* rolling_mean;
    float* rolling_variance;

    float* x;
    float* x_norm;

    float* m;
    float* v;

    float* bias_m;
    float* bias_v;
    float* scale_m;
    float* scale_v;

    float* z_cpu;
    float* r_cpu;
    float* h_cpu;
    float* stored_h_cpu;
    float* prev_state_cpu;

    float* temp_cpu;
    float* temp2_cpu;
    float* temp3_cpu;

    float* dh_cpu;
    float* hh_cpu;
    float* prev_cell_cpu;
    float* cell_cpu;
    float* f_cpu;
    float* i_cpu;
    float* g_cpu;
    float* o_cpu;
    float* c_cpu;
    float* stored_c_cpu;
    float* dc_cpu;

    float* binary_input;
    uint32_t* bin_re_packed_input;
    char* t_bit_input;

    struct _layer* input_layer, * self_layer, * output_layer;

    struct _layer* reset_layer, * update_layer, * state_layer;

    struct _layer* input_gate_layer;
    struct _layer* state_gate_layer;
    struct _layer* input_save_layer;
    struct _layer* state_save_layer;
    struct _layer* input_state_layer;
    struct _layer* state_state_layer;

    struct _layer* input_z_layer;
    struct _layer* state_z_layer;

    struct _layer* input_r_layer;
    struct _layer* state_r_layer;

    struct _layer* input_h_layer;
    struct _layer* state_h_layer;

    struct _layer* wz, *uz, *wr, *ur, *wh, *uh, *uo, *wo, *vo, *uf, *wf, *vf, *ui, *wi, *vi, *ug, *wg;

    tree* softmax_tree;

    size_t workspace_size;

#ifdef GPU
    int* indexes_gpu;

    float* z_gpu;
    float* r_gpu;
    float* h_gpu;
    float* stored_h_gpu;

    float* temp_gpu;
    float* temp2_gpu;
    float* temp3_gpu;

    float* dh_gpu;
    float* hh_gpu;
    float* prev_cell_gpu;
    float* prev_state_gpu;
    float* last_prev_state_gpu;
    float* last_prev_cell_gpu;
    float* cell_gpu;
    float* f_gpu;
    float* i_gpu;
    float* g_gpu;
    float* o_gpu;
    float* c_gpu;
    float* stored_c_gpu;
    float* dc_gpu;

    // adam
    float* m_gpu;
    float* v_gpu;
    float* bias_m_gpu;
    float* scale_m_gpu;
    float* bias_v_gpu;
    float* scale_v_gpu;

    float* combine_gpu;
    float* combine_delta_gpu;

    float* forgot_state_gpu;
    float* forgot_delta_gpu;
    float* state_gpu;
    float* state_delta_gpu;
    float* gate_gpu;
    float* gate_delta_gpu;
    float* save_gpu;
    float* save_delta_gpu;
    float* concat_gpu;
    float* concat_delta_gpu;

    float* binary_input_gpu;
    float* binary_weights_gpu;
    float* bin_conv_shortcut_in_gpu;
    float* bin_conv_shortcut_out_gpu;

    float* mean_gpu;
    float* variance_gpu;

    float* rolling_mean_gpu;
    float* rolling_variance_gpu;

    float* variance_delta_gpu;
    float* mean_delta_gpu;

    float* col_image_gpu;

    float* x_gpu;
    float* x_norm_gpu;
    float* weights_gpu;
    float* weight_updates_gpu;
    float* weight_change_gpu;

    float* weights_gpu16;
    float* weight_updates_gpu16;

    float* biases_gpu;
    float* bias_updates_gpu;
    float* bias_change_gpu;

    float* scales_gpu;
    float* scale_updates_gpu;
    float* scale_change_gpu;

    float* output_gpu;
    float* loss_gpu;
    float* delta_gpu;
    float* rand_gpu;
    float* squared_gpu;
    float* norms_gpu;
#ifdef CUDNN
    cudnnTensorDescriptor_t srcTensorDesc, dstTensorDesc;
    cudnnTensorDescriptor_t srcTensorDesc16, dstTensorDesc16;
    cudnnTensorDescriptor_t dsrcTensorDesc, ddstTensorDesc;
    cudnnTensorDescriptor_t dsrcTensorDesc16, ddstTensorDesc16;
    cudnnTensorDescriptor_t normTensorDesc, normDstTensorDesc, normDstTensorDescF16;
    cudnnFilterDescriptor_t weightDesc, weightDesc16;
    cudnnFilterDescriptor_t dweightDesc, dweightDesc16;
    cudnnConvolutionDescriptor_t convDesc;
    cudnnConvolutionFwdAlgo_t fw_algo, fw_algo16;
    cudnnConvolutionBwdDataAlgo_t bd_algo, bd_algo16;
    cudnnConvolutionBwdFilterAlgo_t bf_algo, bf_algo16;
    cudnnPoolingDescriptor_t poolingDesc;
#endif  // CUDNN
#endif  // GPU
} layer;

//network===================================================
typedef enum
{
    CONSTANT, STEP, EXP, POLY, STEPS, SIG, RANDOM, SGDR
} learning_rate_policy;

typedef struct network
{
    int n;
    int batch;
    uint64_t* seen;
    int* t;
    float epoch;
    int subdivisions;
    layer* layers;
    float* output;
    learning_rate_policy policy;

    float learning_rate;
    float learning_rate_min;
    float learning_rate_max;
    int batches_per_cycle;
    int batches_cycle_mult;
    float momentum;
    float decay;
    float gamma;
    float scale;
    float power;
    int time_steps;
    int step;
    int max_batches;
    float* seq_scales;
    float* scales;
    int*   steps;
    int num_steps;
    int burn_in;
    int cudnn_half;

    int adam;
    float B1;
    float B2;
    float eps;

    int inputs;
    int outputs;
    int truths;
    int notruth;
    int h, w, c;
    int max_crop;
    int min_crop;
    float max_ratio;
    float min_ratio;
    int center;
    int flip; // horizontal flip 50% probability augmentaiont for classifier training (default = 1)
    int blur;
    int mixup;
    float angle;
    float aspect;
    float exposure;
    float saturation;
    float hue;
    int random;
    int track;
    int augment_speed;
    int sequential_subdivisions;
    int init_sequential_subdivisions;
    int current_subdivision;
    int try_fix_nan;

    int gpu_index;
    tree* hierarchy;

    float* input;
    float* truth;
    float* delta;
    float* workspace;
    int train;
    int index;
    float* cost;
    float clip;

#ifdef GPU
    //float *input_gpu;
    //float *truth_gpu;
    float* delta_gpu;
    float* output_gpu;

    float* input_state_gpu;
    float* input_pinned_cpu;
    int input_pinned_cpu_flag;

    float** input_gpu;
    float** truth_gpu;
    float** input16_gpu;
    float** output16_gpu;
    size_t* max_input16_size;
    size_t* max_output16_size;
    int wait_stream;
#endif
} network;

typedef struct network_state
{
    float* truth;
    float* input;
    float* delta;
    float* workspace;
    int train;
    int index;
    network net;
} network_state;





#endif
