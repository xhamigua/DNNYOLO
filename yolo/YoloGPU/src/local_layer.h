#ifndef LOCAL_LAYER_H
#define LOCAL_LAYER_H

#include "yolodef.h"

typedef layer local_layer;

#ifdef __cplusplus
extern "C" {
#endif

local_layer make_local_layer(int batch, int h, int w, int c, int n, int size, int stride, int pad, ACTIVATION activation);
void forward_local_layer(const local_layer layer, network_state state);
void backward_local_layer(local_layer layer, network_state state);
void update_local_layer(local_layer layer, int batch, float learning_rate, float momentum, float decay);

#ifdef GPU
void forward_local_layer_gpu(local_layer layer, network_state state);
void backward_local_layer_gpu(local_layer layer, network_state state);
void update_local_layer_gpu(local_layer layer, int batch, float learning_rate, float momentum, float decay);
void pull_local_layer(local_layer layer);
void push_local_layer(local_layer layer);
#endif


#ifdef __cplusplus
}
#endif

#endif
