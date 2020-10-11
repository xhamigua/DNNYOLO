#ifndef LIST_H
#define LIST_H

typedef struct node
{
    void* val;
    struct node* next;
    struct node* prev;
} node;

typedef struct list
{
    int size;
    node* front;
    node* back;
} list;

typedef struct
{
    char* key;
    char* val;
    int used;
} kvp;

#ifdef __cplusplus
extern "C" {
#endif

list* make_list();
void transfer_node(list* s, list* d, node* n);
void* list_pop(list* l);
void list_insert(list*, void*);
void** list_to_array(list* l);
void free_node(node* n);
void free_list(list* l);
void free_list_contents(list* l);
void free_list_contents_kvp(list* l);

#ifdef __cplusplus
}
#endif
#endif
