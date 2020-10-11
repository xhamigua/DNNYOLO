#ifndef CONVOLUTIONAL_LAYER_H
#define CONVOLUTIONAL_LAYER_H

#include "yolodef.h"

typedef layer convolutional_layer;

#ifdef __cplusplus
extern "C" {
#endif


void swap_binary(convolutional_layer* l);
void binarize_weights(float* weights, int n, int size, float* binary);
void binarize_cpu(float* input, int n, float* binary);
void binarize_input(float* input, int n, int size, float* binary);
int convolutional_out_height(convolutional_layer layer);
int convolutional_out_width(convolutional_layer layer);
image get_convolutional_image(convolutional_layer layer);
image get_convolutional_delta(convolutional_layer layer);
size_t get_workspace_size32(layer l);
size_t get_workspace_size16(layer l);
size_t get_convolutional_workspace_size(layer l);
convolutional_layer make_convolutional_layer(int batch, int steps, int h, int w, int c, int n, int groups, int size, int stride, int dilation, int padding, ACTIVATION activation, int batch_normalize, int binary, int xnor, int adam, int use_bin_output, int index, convolutional_layer* share_layer);
void denormalize_convolutional_layer(convolutional_layer l);
void test_convolutional_layer();
void resize_convolutional_layer(convolutional_layer* layer, int w, int h);
void add_bias(float* output, float* biases, int batch, int n, int size);
void scale_bias(float* output, float* scales, int batch, int n, int size);
void backward_bias(float* bias_updates, float* delta, int batch, int n, int size);
void gemm_nn_custom(int M, int N, int K, float ALPHA, float* A, int lda, float* B, int ldb, float* C, int ldc);
void get_mean_array(float* src, size_t size, size_t filters, float* mean_arr);
void bit_to_float(unsigned char* src, float* dst, size_t size, size_t filters, float* mean_arr);
void binary_align_weights(convolutional_layer* l);
size_t binary_transpose_align_input(int k, int n, float* b, char** t_bit_input, size_t ldb_align, int bit_align);
void forward_convolutional_layer(const convolutional_layer layer, network_state state);
void backward_convolutional_layer(convolutional_layer layer, network_state state);
void update_convolutional_layer(convolutional_layer layer, int batch, float learning_rate, float momentum, float decay);
image get_convolutional_weight(convolutional_layer layer, int i);
void rgbgr_weights(convolutional_layer l);
void rescale_weights(convolutional_layer l, float scale, float trans);
image* get_weights(convolutional_layer l);
image* visualize_convolutional_layer(convolutional_layer layer, char* window, image* prev_weights);




#ifdef GPU
void forward_convolutional_layer_gpu(convolutional_layer layer, network_state state);
void backward_convolutional_layer_gpu(convolutional_layer layer, network_state state);
void update_convolutional_layer_gpu(convolutional_layer layer, int batch, float learning_rate, float momentum, float decay);

void push_convolutional_layer(convolutional_layer layer);
void pull_convolutional_layer(convolutional_layer layer);

void add_bias_gpu(float* output, float* biases, int batch, int n, int size);
void backward_bias_gpu(float* bias_updates, float* delta, int batch, int n, int size);
#ifdef CUDNN
void cudnn_convolutional_setup(layer* l, int cudnn_preference);
void create_convolutional_cudnn_tensors(layer* l);
void cuda_convert_f32_to_f16(float* input_f32, size_t size, float* output_f16);
#endif
#endif









#ifdef __cplusplus
}
#endif

#endif
