#ifndef AVGPOOL_LAYER_H
#define AVGPOOL_LAYER_H

#include "yolodef.h"

typedef layer avgpool_layer;

#ifdef __cplusplus
extern "C" {
#endif


avgpool_layer make_avgpool_layer(int batch, int w, int h, int c);
void resize_avgpool_layer(avgpool_layer* l, int w, int h);
void forward_avgpool_layer(const avgpool_layer l, network_state state);
void backward_avgpool_layer(const avgpool_layer l, network_state state);

#ifdef GPU
void forward_avgpool_layer_gpu(avgpool_layer l, network_state state);
void backward_avgpool_layer_gpu(avgpool_layer l, network_state state);
#endif


#ifdef __cplusplus
}
#endif

#endif
