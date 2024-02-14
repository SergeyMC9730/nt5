/*
    nt5 -- Windows XP simulator.
    Copyright (C) 2023  Sergei Baigerov

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

    Contact Sergei Baigerov -- @dogotrigger in Discord
*/

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
#define RSB_ARRAY_FUNC_MERGE_DEF(type, funname) void RSBMergeElements##funname(RSB_ARRAY_NAME(funname) *source, RSB_ARRAY_NAME(funname) *destination)
#define RSB_ARRAY_FUNC_ADDELEMENTATINDEX_DEF(type, funname) void RSBAddElementAtIndex##funname(RSB_ARRAY_NAME(funname) *array, type object, unsigned int index)
#define RSB_ARRAY_FUNC_POPELEMENTATINDEX_DEF(type, funname) void RSBPopElementAtIndex##funname(RSB_ARRAY_NAME(funname) *array, unsigned int index)

#define RSB_ARRAY_DEF_GEN(type, funname) RSB_ARRAY_STRUCT(type, funname); \
RSB_ARRAY_FUNC_CREATE_DEF(funname);                 \
RSB_ARRAY_FUNC_DESTROY_DEF(funname);                \
                                                    \
RSB_ARRAY_FUNC_ADDELEMENT_DEF(type, funname);       \
RSB_ARRAY_FUNC_POPELEMENT_DEF(funname);             \
RSB_ARRAY_FUNC_MERGE_DEF(type, funname);            \
                                                    \
RSB_ARRAY_FUNC_GETATINDEX_DEF(type, funname);       \
                                                    \
RSB_ARRAY_FUNC_ADDELEMENTATINDEX_DEF(type, funname);\
RSB_ARRAY_FUNC_POPELEMENTATINDEX_DEF(type, funname);

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

#define RSB_ARRAY_FUNC_MERGE_IMPL(type, funname) RSB_ARRAY_FUNC_MERGE_DEF(type, funname) { \
    if (!source || !destination || !source->objects || !destination->objects) return;      \
                                                                                           \
    for (size_t i = 0; i < source->len; i++) {                                             \
        type obj = RSBGetAtIndex##funname(source, i);                                      \
                                                                                           \
        RSBAddElement##funname(destination, obj);                                          \
    }                                                                                      \
                                                                                           \
    return;                                                                                \
}

#define RSB_ARRAY_FUNC_ADDELEMENTATINDEX_IMPL(type, funname) RSB_ARRAY_FUNC_ADDELEMENTATINDEX_DEF(type, funname) {  \
    if (index > array->len || !array) return;                                                                       \
                                                                                                                    \
    rsb_array_##funname *new_arr = RSBCreateArray##funname();                                                       \
                                                                                                                    \
    for (size_t i = 0; i < array->len; i++) {                                                                       \
        if (i == index) {                                                                                           \
            RSBAddElement##funname(new_arr, object);                                                                \
        }                                                                                                           \
                                                                                                                    \
        RSBAddElement##funname(new_arr, RSBGetAtIndex##funname(array, i));                                          \
    }                                                                                                               \
                                                                                                                    \
    while (array->len != 0) {                                                                                       \
        RSBPopElement##funname(array);                                                                              \
    }                                                                                                               \
                                                                                                                    \
    for (size_t i = 0; i < new_arr->len; i++) {                                                                     \
        RSBAddElement##funname(array, RSBGetAtIndex##funname(new_arr, i));                                          \
    }                                                                                                               \
                                                                                                                    \
    RSBDestroy##funname(new_arr);                                                                                   \
}

#define RSB_ARRAY_FUNC_POPELEMENTATINDEX_IMPL(type, funname) RSB_ARRAY_FUNC_POPELEMENTATINDEX_DEF(type, funname) {  \
    if (index > array->len || !array) return;                                                                       \
                                                                                                                    \
    rsb_array_##funname *new_arr = RSBCreateArray##funname();                                                       \
                                                                                                                    \
    for (size_t i = 0; i < array->len; i++) {                                                                       \
        if (i != index) {                                                                                           \
            RSBAddElement##funname(new_arr, RSBGetAtIndex##funname(array, i));                                      \
        }                                                                                                           \
    }                                                                                                               \
                                                                                                                    \
    while (array->len != 0) {                                                                                       \
        RSBPopElement##funname(array);                                                                              \
    }                                                                                                               \
                                                                                                                    \
    for (size_t i = 0; i < new_arr->len; i++) {                                                                     \
        RSBAddElement##funname(array, RSBGetAtIndex##funname(new_arr, i));                                          \
    }                                                                                                               \
                                                                                                                    \
    RSBDestroy##funname(new_arr);                                                                                   \
}

#define RSB_ARRAY_IMPL_GEN(type, funname)            \
RSB_ARRAY_FUNC_CREATE_IMPL(funname);                 \
RSB_ARRAY_FUNC_DESTROY_IMPL(funname);                \
                                                     \
RSB_ARRAY_FUNC_ADDELEMENT_IMPL(type, funname);       \
RSB_ARRAY_FUNC_POPELEMENT_IMPL(type, funname);       \
RSB_ARRAY_FUNC_MERGE_IMPL(type, funname);            \
                                                     \
RSB_ARRAY_FUNC_GETATINDEX_IMPL(type, funname);       \
                                                     \
RSB_ARRAY_FUNC_ADDELEMENTATINDEX_IMPL(type, funname);\
RSB_ARRAY_FUNC_POPELEMENTATINDEX_IMPL(type, funname);

#pragma pack(pop)

#ifdef __cplusplus
}
#endif
