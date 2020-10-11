#ifndef TREE_H
#define TREE_H

#include "yolodef.h"

#ifdef __cplusplus
extern "C" {
#endif

void change_leaves(tree* t, char* leaf_list);
float get_hierarchy_probability(float* x, tree* hier, int c);
void hierarchy_predictions(float* predictions, int n, tree* hier, int only_leaves);
int hierarchy_top_prediction(float* predictions, tree* hier, float thresh, int stride);
LIB_API tree* read_tree(char* filename);

#ifdef __cplusplus
}
#endif
#endif
