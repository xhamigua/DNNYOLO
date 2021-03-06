#ifndef DROPOUT_LAYER_H
#define DROPOUT_LAYER_H

#include "yolodef.h"

typedef layer dropout_layer;

#ifdef __cplusplus
extern "C" {
#endif


dropout_layer make_dropout_layer(int batch, int inputs, float probability);
void resize_dropout_layer(dropout_layer* l, int inputs);
void forward_dropout_layer(dropout_layer l, network_state state);
void backward_dropout_layer(dropout_layer l, network_state state);

#ifdef GPU
void forward_dropout_layer_gpu(dropout_layer l, network_state state);
void backward_dropout_layer_gpu(dropout_layer l, network_state state);
#endif


#ifdef __cplusplus
}
#endif
#endif
