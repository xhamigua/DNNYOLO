#ifndef BATCHNORM_LAYER_H
#define BATCHNORM_LAYER_H

#include "yolodef.h"

#ifdef __cplusplus
extern "C" {
#endif
layer make_batchnorm_layer(int batch, int w, int h, int c);
void backward_scale_cpu(float* x_norm, float* delta, int batch, int n, int size, float* scale_updates);
void mean_delta_cpu(float* delta, float* variance, int batch, int filters, int spatial, float* mean_delta);
void variance_delta_cpu(float* x, float* delta, float* mean, float* variance, int batch, int filters, int spatial, float* variance_delta);
void normalize_delta_cpu(float* x, float* mean, float* variance, float* mean_delta, float* variance_delta, int batch, int filters, int spatial, float* delta);
void forward_batchnorm_layer(layer l, network_state state);
void backward_batchnorm_layer(layer l, network_state state);




#ifdef GPU
void pull_batchnorm_layer(layer l);
void push_batchnorm_layer(layer l);
void forward_batchnorm_layer_gpu(layer l, network_state state);
void backward_batchnorm_layer_gpu(layer l, network_state state);
#endif

#ifdef __cplusplus
}
#endif
#endif
