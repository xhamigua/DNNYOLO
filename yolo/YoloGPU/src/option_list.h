#ifndef OPTION_LIST_H
#define OPTION_LIST_H
#include "yolodef.h"
#include "list.h"

#ifdef __cplusplus
extern "C" {
#endif

list* read_data_cfg(char* filename);
int read_option(char* s, list* options);
void option_insert(list* l, char* key, char* val);
char* option_find(list* l, char* key);
char* option_find_str(list* l, char* key, char* def);
char* option_find_str_quiet(list* l, char* key, char* def);
int option_find_int(list* l, char* key, int def);
int option_find_int_quiet(list* l, char* key, int def);
float option_find_float(list* l, char* key, float def);
float option_find_float_quiet(list* l, char* key, float def);
void option_unused(list* l);
LIB_API metadata get_metadata(char* file);



#ifdef __cplusplus
}
#endif
#endif
