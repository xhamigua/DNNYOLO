#ifndef PARSER_H
#define PARSER_H
#include "yolodef.h"

#ifdef __cplusplus
extern "C" {
#endif

LIB_API network* load_network(char* cfg, char* weights, int clear);
LIB_API network* load_network_custom(char* cfg, char* weights, int clear, int batch);
LIB_API network* load_network(char* cfg, char* weights, int clear);
network parse_network_cfg(char* filename);
network parse_network_cfg_custom(char* filename, int batch, int time_steps);
void save_network(network net, char* filename);
void save_weights(network net, char* filename);
void save_weights_upto(network net, char* filename, int cutoff);
void save_weights_double(network net, char* filename);
void load_weights(network* net, char* filename);
void load_weights_upto(network* net, char* filename, int cutoff);

#ifdef __cplusplus
}
#endif
#endif
