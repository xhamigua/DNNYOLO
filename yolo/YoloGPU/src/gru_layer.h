
#ifndef GRU_LAYER_H
#define GRU_LAYER_H

#include "yolodef.h"

#ifdef __cplusplus
extern "C" {
#endif
layer make_gru_layer(int batch, int inputs, int outputs, int steps, int batch_normalize);
void update_gru_layer(layer l, int batch, float learning_rate, float momentum, float decay);
void forward_gru_layer(layer l, network_state state);
void backward_gru_layer(layer l, network_state state);

#ifdef GPU
void pull_gru_layer(layer l);
void push_gru_layer(layer l);
void update_gru_layer_gpu(layer l, int batch, float learning_rate, float momentum, float decay);
void forward_gru_layer_gpu(layer l, network_state state);
void backward_gru_layer_gpu(layer l, network_state state);
#endif

#ifdef __cplusplus
}
#endif

#endif
