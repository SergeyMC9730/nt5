#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(push, 1)

#include <assert.h>

#define RSB_ARRAY_NAME(funname) rsb_array_##funname

#define RSB_ARRAY_STRUCT(type, funname) typedef struct RSB_ARRAY_NAME(funname) { \
    unsigned int len;           \
    unsigned int current_index; \
    unsigned int added_elements;\
    type *objects;              \
} RSB_ARRAY_NAME(funname)

#define RSB_ARRAY_FUNC_CREATE_DEF(funname) RSB_ARRAY_NAME(funname) *RSBCreateArray##funname()
#define RSB_ARRAY_FUNC_ADDELEMENT_DEF(type, funname) void RSBAddElement##funname(RSB_ARRAY_NAME(funname) *array, type object)
#define RSB_ARRAY_FUNC_POPELEMENT_DEF(funname) void RSBPopElement##funname(RSB_ARRAY_NAME(funname) *array)
#define RSB_ARRAY_FUNC_DESTROY_DEF(funname) void RSBDestroy##funname(RSB_ARRAY_NAME(funname) *array)
#define RSB_ARRAY_FUNC_GETATINDEX_DEF(type, funname) type RSBGetAtIndex##funname(RSB_ARRAY_NAME(funname) *array, unsigned int index)

#define RSB_ARRAY_DEF_GEN(type, funname) RSB_ARRAY_STRUCT(type, funname); \
RSB_ARRAY_FUNC_CREATE_DEF(funname);             \
RSB_ARRAY_FUNC_DESTROY_DEF(funname);      \
                                                \
RSB_ARRAY_FUNC_ADDELEMENT_DEF(type, funname);   \
RSB_ARRAY_FUNC_POPELEMENT_DEF(funname);         \
                                                \
RSB_ARRAY_FUNC_GETATINDEX_DEF(type, funname);

#include <stdlib.h>

#define RSB_ARRAY_FUNC_CREATE_IMPL(funname) RSB_ARRAY_FUNC_CREATE_DEF(funname) {                            \
    RSB_ARRAY_NAME(funname) *array = (RSB_ARRAY_NAME(funname) *)calloc(1, sizeof(RSB_ARRAY_NAME(funname))); \
                                                                                                            \
    array->len = 0;                                                                                         \
    array->current_index = 0;                                                                               \
    array->added_elements = 0;                                                                              \
    array->objects = NULL;                                                                                  \
                                                                                                            \
    return array;                                                                                           \
}

#define RSB_ARRAY_FUNC_ADDELEMENT_IMPL(type, funname) RSB_ARRAY_FUNC_ADDELEMENT_DEF(type, funname) {                        \
    if (!array) return;                                                                                                     \
                                                                                                                            \
    if (!array->objects) {                                                                                                  \
        array->objects = (type *)calloc(1, sizeof(type));                                                                   \
        array->len = 1;                                                                                                     \
        array->current_index = 0;                                                                                           \
        array->added_elements = 0;                                                                                          \
    }                                                                                                                       \
                                                                                                                            \
    if ((array->added_elements + 1) > array->len) {                                                                         \
        array->objects = (type *)realloc(array->objects, sizeof(type) * (array->len + 1));                                  \
        array->len++;                                                                                                       \
    }                                                                                                                       \
                                                                                                                            \
    array->objects[array->current_index] = object;                                                                          \
    array->added_elements++;                                                                                                \
    array->current_index++;                                                                                                 \
                                                                                                                            \
    return;                                                                                                                 \
}

#define RSB_ARRAY_FUNC_POPELEMENT_IMPL(type, funname) RSB_ARRAY_FUNC_POPELEMENT_DEF(funname) {                          \
    if (!array || !array->objects || array->added_elements == 0 || array->len == 0) return;                             \
    if ((array->len - 1) == 0) {                                                                                        \
        free(array->objects);                                                                                           \
        array->objects = NULL;                                                                                          \
                                                                                                                        \
        array->len--;                                                                                                   \
        array->added_elements--;                                                                                        \
                                                                                                                        \
        return;                                                                                                         \
    }                                                                                                                   \
                                                                                                                        \
    array->objects = (type *)realloc(array->objects, sizeof(type) * (array->len - 1));                                  \
                                                                                                                        \
    array->len--;                                                                                                       \
    array->added_elements--;                                                                                            \
                                                                                                                        \
    if (array->current_index > array->len) {                                                                            \
        if (array->current_index != 0) array->current_index--;                                                          \
    }                                                                                                                   \
                                                                                                                        \
    return;                                                                                                             \
}

#define RSB_ARRAY_FUNC_DESTROY_IMPL(funname) RSB_ARRAY_FUNC_DESTROY_DEF(funname) {    \
    if (!array || !array->objects) return;                                            \
                                                                                      \
    free(array->objects);                                                             \
    free(array);                                                                      \
                                                                                      \
    return;                                                                           \
}

#define RSB_ARRAY_FUNC_GETATINDEX_IMPL(type, funname) RSB_ARRAY_FUNC_GETATINDEX_DEF(type, funname) {  \
    assert(!(!array || !array->objects || array->len < index));                                       \
                                                                                                      \
    return array->objects[index];                                                                     \
}

#define RSB_ARRAY_IMPL_GEN(type, funname)        \
RSB_ARRAY_FUNC_CREATE_IMPL(funname);       \
RSB_ARRAY_FUNC_DESTROY_IMPL(funname);      \
                                        \
RSB_ARRAY_FUNC_ADDELEMENT_IMPL(type, funname);   \
RSB_ARRAY_FUNC_POPELEMENT_IMPL(type, funname);   \
                                        \
RSB_ARRAY_FUNC_GETATINDEX_IMPL(type, funname);

#pragma pack(pop)

#ifdef __cplusplus
}
#endif
