#ifndef BASE_LAYER_H
#define BASE_LAYER_H

#include "yolodef.h"
#include "stddef.h"

#ifdef __cplusplus
extern "C" {
#endif


void free_sublayer(layer* l);
void free_layer(layer l);

#ifdef __cplusplus
}

#endif
#endif
