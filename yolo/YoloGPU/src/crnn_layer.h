
#ifndef CRNN_LAYER_H
#define CRNN_LAYER_H

#include "yolodef.h"

#ifdef __cplusplus
extern "C" {
#endif
layer make_crnn_layer(int batch, int h, int w, int c, int hidden_filters, int output_filters, int groups, int steps, int size, int stride, int dilation, int pad, ACTIVATION activation, int batch_normalize, int xnor);
void resize_crnn_layer(layer* l, int w, int h);
void free_state_crnn(layer l);
void update_crnn_layer(layer l, int batch, float learning_rate, float momentum, float decay);
void forward_crnn_layer(layer l, network_state state);
void backward_crnn_layer(layer l, network_state state);

#ifdef GPU
void pull_crnn_layer(layer l);
void push_crnn_layer(layer l); 
void update_crnn_layer_gpu(layer l, int batch, float learning_rate, float momentum, float decay);
void forward_crnn_layer_gpu(layer l, network_state state);
void backward_crnn_layer_gpu(layer l, network_state state);
#endif

#ifdef __cplusplus
}
#endif

#endif
