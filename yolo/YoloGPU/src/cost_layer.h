#ifndef COST_LAYER_H
#define COST_LAYER_H

#include "yolodef.h"

typedef layer cost_layer;

#ifdef __cplusplus
extern "C" {
#endif
COST_TYPE get_cost_type(char* s);
char* get_cost_string(COST_TYPE a);
cost_layer make_cost_layer(int batch, int inputs, COST_TYPE type, float scale);
void resize_cost_layer(cost_layer* l, int inputs);
void forward_cost_layer(const cost_layer l, network_state state);
void backward_cost_layer(const cost_layer l, network_state state);

#ifdef GPU
void pull_cost_layer(cost_layer l);
void push_cost_layer(cost_layer l);
int float_abs_compare(const void* a, const void* b);
void forward_cost_layer_gpu(cost_layer l, network_state state);
void backward_cost_layer_gpu(const cost_layer l, network_state state);
#endif

#ifdef __cplusplus
}
#endif
#endif
