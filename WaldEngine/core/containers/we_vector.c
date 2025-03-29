//
// Created by Toudonou on 11/03/2025.
//

// #include "core/containers/we_vector.h"

// #define DEFINE_WE_VECTOR(type, name)                                                                        \
//                                                                                                             \
//     struct we_vector_##name {                                                                               \
//         type *data;                                                                                         \
//         we_size_t size;                                                                                     \
//         we_size_t capacity;                                                                                 \
//     };                                                                                                      \
//                                                                                                             \
//     we_vector_##name *new_we_vector_##name() {                                                              \
//         we_vector_##name *vector = NULL;                                                                    \
//         vector = (we_vector_##name *) malloc(sizeof(we_vector_##name));                                     \
//         if (vector == NULL) {                                                                               \
//             WE_ERROR("Impossible to allocate memory for the we_vector##_%s", #name);                        \
//             return NULL;                                                                                    \
//         }                                                                                                   \
//         vector->data = NULL;                                                                                \
//         vector->size = 0;                                                                                   \
//         vector->capacity = 0;                                                                               \
//         return vector;                                                                                      \
//     }                                                                                                       \
//                                                                                                             \
//     void delete_we_vector_##name(we_vector_##name **vector) {                                               \
//         if (vector == NULL || *vector == NULL) {                                                            \
//             WE_WARN("Trying to delete a NULL we_vector##_%s", #name);                                       \
//             return;                                                                                         \
//         }                                                                                                   \
//         if ((*vector)->data) free((*vector)->data);                                                         \
//         (*vector)->data = NULL;                                                                             \
//         free(*vector);                                                                                      \
//         *vector = NULL;                                                                                     \
//     }                                                                                                       \
//                                                                                                             \
//     void we_vector_##name##_push_back(we_vector_##name *vector, type element) {                             \
//         static const we_real growth_factor = 1.5f;                                                          \
//                                                                                                             \
//         if (vector == NULL) {                                                                               \
//             WE_WARN("Trying to add some element to a NULL we_vector##_%s", #name);                          \
//             return;                                                                                         \
//         }                                                                                                   \
//                                                                                                             \
//         if (vector->size >= vector->capacity) {                                                             \
//             vector->capacity = (we_size_t) ((we_real) vector->capacity * growth_factor);                    \
//             vector->capacity += vector->capacity == vector->size;                                           \
//             we_vector_##name##_resize(vector, vector->capacity);                                            \
//         }                                                                                                   \
//         vector->data[vector->size++] = element;                                                             \
//     }                                                                                                       \
//                                                                                                             \
//     void we_vector_##name##_insert_at(we_vector_##name *vector, we_size_t index, type element) {            \
//         if (vector == NULL) {                                                                               \
//             WE_WARN("Trying to add some element to a NULL we_vector##_%s", #name);                          \
//             return;                                                                                         \
//         }                                                                                                   \
//                                                                                                             \
//         WE_ASSERT_MSG(index < vector->size, "index is out of bounds");                                      \
//         vector->data[index] = element;                                                                      \
//     }                                                                                                       \
//                                                                                                             \
//     type we_vector_##name##_pop_back(we_vector_##name *vector) {                                            \
//         if (vector == NULL) {                                                                               \
//             WE_WARN("Trying to pop_back a NULL we_vector##_%s", #name);                                     \
//             return (type) {0};                                                                              \
//         }                                                                                                   \
//         return vector->data[--vector->size];                                                                \
//     }                                                                                                       \
//                                                                                                             \
//     type we_vector_##name##_get_element_at(we_vector_##name *vector, we_size_t index) {                     \
//         if (vector == NULL) {                                                                               \
//             WE_WARN("Trying to retrieve some element from a NULL we_vector##_%s", #name);                   \
//             return (type) {0};                                                                              \
//         }                                                                                                   \
//         WE_ASSERT_MSG(index < vector->size, "index is out of bounds");                                      \
//         return vector->data[index];                                                                         \
//     }                                                                                                       \
//                                                                                                             \
//     type we_vector_##name##_front(we_vector_##name *vector) {                                               \
//         return we_vector_##name##_get_element_at(vector, 0);                                                \
//     }                                                                                                       \
//                                                                                                             \
//     type we_vector_##name##_back(we_vector_##name *vector) {                                                \
//         return we_vector_##name##_get_element_at(vector, vector->size - 1);                                 \
//     }                                                                                                       \
//                                                                                                             \
//     const type *we_vector_##name##_get_data(we_vector_##name *vector) {                                     \
//         if (vector == NULL) {                                                                               \
//             WE_WARN("Trying to retrieve the data array from a NULL we_vector##_%s", #name);                 \
//             return NULL;                                                                                    \
//         }                                                                                                   \
//         return vector->data;                                                                                \
//     }                                                                                                       \
//                                                                                                             \
//     void we_vector_##name##_resize(we_vector_##name *vector, we_size_t new_capacity) {                      \
//         if (vector == NULL) {                                                                               \
//             WE_WARN("Trying to resize a NULL we_vector##_%s", #name);                                       \
//             return;                                                                                         \
//         }                                                                                                   \
//         if (new_capacity <= vector->size) {                                                                 \
//             WE_WARN("The new capacity must be greater than the actual size of the we_vector##_%s", #name);  \
//             return;                                                                                         \
//         }                                                                                                   \
//                                                                                                             \
//         vector->capacity = new_capacity;                                                                    \
//         type *temp_data = (type *) realloc(vector->data, vector->capacity * sizeof(type));                  \
//         if (temp_data == NULL) {                                                                            \
//             WE_ERROR("Impossible to re-allocate memory for the we_vector##_%s", #name);                     \
//             return;                                                                                         \
//         }                                                                                                   \
//         vector->data = temp_data;                                                                           \
//     }                                                                                                       \
//                                                                                                             \
//     we_size_t we_vector_##name##_get_size(we_vector_##name *vector) {                                       \
//         if (vector == NULL) {                                                                               \
//             WE_WARN("Trying to get the size of a NULL we_vector##_%s", #name);                              \
//             return 0;                                                                                       \
//         }                                                                                                   \
//         return vector->size;                                                                                \
//     }                                                                                                       \
//                                                                                                             \
//     we_size_t we_vector_##name##_get_capacity(we_vector_##name *vector) {                                   \
//         if (vector == NULL) {                                                                               \
//             WE_WARN("Trying to get the capacity of a NULL we_vector##_%s", #name);                          \
//             return 0;                                                                                       \
//         }                                                                                                   \
//         return vector->capacity;                                                                            \
//     }                                                                                                       \
//                                                                                                             \
//     void we_vector_##name##_erase(we_vector_##name *vector) {                                               \
//         if (vector == NULL) {                                                                               \
//             WE_WARN("Trying to erase a NULL we_vector##_%s", #name);                                        \
//             return;                                                                                         \
//         }                                                                                                   \
//         vector->size = 0;                                                                                   \
//         vector->capacity = 0;                                                                               \
//     }                                                                                                       \
//                                                                                                             \
//     we_bool we_vector_##name##_is_empty(we_vector_##name *vector) {                                         \
//         if (vector == NULL) {                                                                               \
//             WE_WARN("Trying to check if a NULL we_vector##_%s is empty", #name);                            \
//             return WE_TRUE;                                                                                 \
//         }                                                                                                   \
//         return vector->size == 0;                                                                           \
//     }

// DEFINE_WE_VECTOR(we_bool, bool)
//
// DEFINE_WE_VECTOR(we_int8, int8)
//
// DEFINE_WE_VECTOR(we_uint8, uint8)
//
// DEFINE_WE_VECTOR(we_int32, int32)
//
// DEFINE_WE_VECTOR(we_uint32, uint32)
//
// DEFINE_WE_VECTOR(we_int64, int64)
//
// DEFINE_WE_VECTOR(we_uint64, uint64)
//
// DEFINE_WE_VECTOR(we_real, real)
//
// DEFINE_WE_VECTOR(we_rectangle, rectangle)
//
// DEFINE_WE_VECTOR(we_vertex, vertex)
//
// DEFINE_WE_VECTOR_HEADER(we_entity, entity)
