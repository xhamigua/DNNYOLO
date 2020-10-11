#ifndef CONNECTED_LAYER_H
#define CONNECTED_LAYER_H

#include "yolodef.h"

typedef layer connected_layer;

#ifdef __cplusplus
extern "C" {
#endif

size_t get_connected_workspace_size(layer l);
connected_layer make_connected_layer(int batch, int steps, int inputs, int outputs, ACTIVATION activation, int batch_normalize);
void update_connected_layer(connected_layer layer, int batch, float learning_rate, float momentum, float decay);
void forward_connected_layer(connected_layer layer, network_state state);
void backward_connected_layer(connected_layer layer, network_state state);
void denormalize_connected_layer(layer l);
void statistics_connected_layer(layer l);

#ifdef GPU
void pull_connected_layer(connected_layer layer);
void push_connected_layer(connected_layer layer);
void update_connected_layer_gpu(connected_layer layer, int batch, float learning_rate, float momentum, float decay);
void forward_connected_layer_gpu(connected_layer layer, network_state state);
void backward_connected_layer_gpu(connected_layer layer, network_state state);
#endif

#ifdef __cplusplus
}
#endif

#endif
