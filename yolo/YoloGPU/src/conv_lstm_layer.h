#ifndef CONV_LSTM_LAYER_H
#define CONV_LSTM_LAYER_H

#include "yolodef.h"
#define USET

#ifdef __cplusplus
extern "C" {
#endif
layer make_conv_lstm_layer(int batch, int h, int w, int c, int output_filters, int groups, int steps, int size, int stride, int dilation, int pad, ACTIVATION activation, int batch_normalize, int peephole, int xnor);
void update_conv_lstm_layer(layer l, int batch, float learning_rate, float momentum, float decay);
void resize_conv_lstm_layer(layer* l, int w, int h);
void free_state_conv_lstm(layer l);
void randomize_state_conv_lstm(layer l);
void remember_state_conv_lstm(layer l);
void restore_state_conv_lstm(layer l);

void forward_conv_lstm_layer(layer l, network_state state);
void backward_conv_lstm_layer(layer l, network_state state);


#ifdef GPU
void pull_conv_lstm_layer(layer l);
void push_conv_lstm_layer(layer l);
void update_conv_lstm_layer_gpu(layer l, int batch, float learning_rate, float momentum, float decay);
void forward_conv_lstm_layer_gpu(layer l, network_state state);
void backward_conv_lstm_layer_gpu(layer l, network_state state);
#endif

#ifdef __cplusplus
}
#endif

#endif  // CONV_LSTM_LAYER_H
