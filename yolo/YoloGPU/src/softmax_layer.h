#ifndef SOFTMAX_LAYER_H
#define SOFTMAX_LAYER_H

#include "yolodef.h"

typedef layer softmax_layer;

#ifdef __cplusplus
extern "C" {
#endif
void softmax_array(float* input, int n, float temp, float* output);
softmax_layer make_softmax_layer(int batch, int inputs, int groups);
void forward_softmax_layer(const softmax_layer l, network_state state);
void backward_softmax_layer(const softmax_layer l, network_state state);

#ifdef GPU
void pull_softmax_layer_output(const softmax_layer l);
void forward_softmax_layer_gpu(const softmax_layer l, network_state state);
void backward_softmax_layer_gpu(const softmax_layer l, network_state state);
#endif

#ifdef __cplusplus
}
#endif
#endif
