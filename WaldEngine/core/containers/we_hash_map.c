//
// Created by Toudonou on 13/03/2025.
//

#include "core/containers/we_hash_map.h"

// #define DEFINE_WE_MAP(type, name)                                                                                           \
//     struct we_map_##name {                                                                                                  \
//         we_vector_##name **map;                                                                                             \
//         we_size_t element_count;                                                                                            \
//         we_size_t capacity;                                                                                                 \
//     };                                                                                                                      \
//                                                                                                                             \
//     we_map_##name *new_we_map_##name() {                                                                                    \
//         we_map_##name *map = NULL;                                                                                          \
//         map = (we_map_##name *) malloc(sizeof(we_map_##name));                                                              \
//         if (map == NULL) {                                                                                                  \
//             WE_ERROR("Impossible to allocate memory for we_map_%s", #name);                                                 \
//             return NULL;                                                                                                    \
//         }                                                                                                                   \
//         map->map = NULL;                                                                                                    \
//         map->element_count = 0;                                                                                             \
//         map->capacity = 0;                                                                                                  \
//         return map;                                                                                                         \
//     }                                                                                                                       \
//                                                                                                                             \
//     void delete_we_map_##name(we_map_##name **map) {                                                                        \
//         if (map == NULL || *map == NULL) {                                                                                  \
//             WE_WARN("Trying to delete a NULL we_map_%s", #name);                                                            \
//             return;                                                                                                         \
//         }                                                                                                                   \
//         if ((*map)->map) we_map_##name##_erase(*map);                                                                       \
//         free(*map);                                                                                                         \
//         *map = NULL;                                                                                                        \
//     }                                                                                                                       \
//                                                                                                                             \
//     void we_map_##name##_insert_at(we_map_##name *map, we_size_t key, type element) {                                       \
//         if (map == NULL) {                                                                                                  \
//             WE_WARN("Trying to add some element to a NULL we_map_%s", #name);                                               \
//             return;                                                                                                         \
//         }                                                                                                                   \
//         if (key >= map->capacity) {                                                                                         \
//             we_map_##name##_resize(map, key + 1);                                                                           \
//         }                                                                                                                   \
//         if (map->map[key] == NULL) {                                                                                        \
//             map->map[key] = new_we_vector_##name();                                                                         \
//         }                                                                                                                   \
//         we_vector_##name##_push_back(map->map[key], element);                                                               \
//         map->element_count++;                                                                                               \
//     }                                                                                                                       \
//                                                                                                                             \
//     void we_map_##name##_delete_at(we_map_##name *map, we_size_t key) {                                                     \
//         if (map == NULL) {                                                                                                  \
//             WE_WARN("Trying to delete an element from a NULL we_map_%s", #name);                                            \
//             return;                                                                                                         \
//         }                                                                                                                   \
//         if (key < map->capacity) {                                                                                          \
//             if (map->map[key] != NULL) {                                                                                    \
//                 delete_we_vector_##name(&map->map[key]);                                                                    \
//                 return;                                                                                                     \
//             }                                                                                                               \
//             WE_WARN("There is not element paired with the key %lu int the map; nothing to delete", key);                    \
//         }                                                                                                                   \
//         WE_WARN("The key %lu is out of bounds", key);                                                                       \
//     }                                                                                                                       \
//                                                                                                                             \
//     const we_vector_##name *we_map_##name##_get_element_at(we_map_##name *map, we_size_t key) {                             \
//         if (map == NULL) {                                                                                                  \
//             WE_WARN("Trying to delete an element from a NULL we_map_%s", #name);                                            \
//             return NULL;                                                                                                    \
//         }                                                                                                                   \
//         if (key < map->capacity) {                                                                                          \
//             if (map->map[key] != NULL) {                                                                                    \
//                 return map->map[key];                                                                                       \
//             }                                                                                                               \
//             WE_WARN("There is not element paired with the key %lu int the map; nothing to retrieve", key);                  \
//             return NULL;                                                                                                    \
//         }                                                                                                                   \
//         WE_WARN("The key %lu is out of bounds", key);                                                                       \
//         return NULL;                                                                                                        \
//     }                                                                                                                       \
//                                                                                                                             \
//     void we_map_##name##_resize(we_map_##name *map, we_size_t new_capacity) {                                               \
//         if (map == NULL) {                                                                                                  \
//             WE_WARN("Trying to add some element to a NULL we_map_%s", #name);                                               \
//             return;                                                                                                         \
//         }                                                                                                                   \
//         if (new_capacity <= map->capacity) {                                                                                \
//             WE_WARN("The new capacity must be greater than the actual capacity of the we_map_%s", #name);                   \
//             return;                                                                                                         \
//         }                                                                                                                   \
//         map->capacity = new_capacity;                                                                                       \
//         we_vector_##name **temp_map = (we_vector_##name **) realloc(map->map, map->capacity * sizeof(we_vector_##name *));  \
//         if (temp_map == NULL) {                                                                                             \
//             WE_ERROR("Impossible to re-allocate memory for the we_map_%s", #name);                                          \
//             return;                                                                                                         \
//         }                                                                                                                   \
//         map->map = temp_map;                                                                                                \
//     }                                                                                                                       \
//                                                                                                                             \
//     we_size_t we_map_##name##_get_size(we_map_##name *map) {                                                                \
//         if (map == NULL) {                                                                                                  \
//             WE_WARN("Trying to get the number of element of a NULL we_map_%s", #name);                                      \
//             return 0;                                                                                                       \
//         }                                                                                                                   \
//         return map->element_count;                                                                                          \
//     }                                                                                                                       \
//                                                                                                                             \
//     we_size_t we_map_##name##_get_capacity(we_map_##name *map) {                                                            \
//         if (map == NULL) {                                                                                                  \
//             WE_WARN("Trying to get the capacity of a NULL we_map_%s", #name);                                               \
//             return 0;                                                                                                       \
//         }                                                                                                                   \
//         return map->capacity;                                                                                               \
//     }                                                                                                                       \
//                                                                                                                             \
//     void we_map_##name##_erase(we_map_##name *map) {                                                                        \
//         if (map == NULL || map->map == NULL) {                                                                              \
//             WE_WARN("Trying to erase a NULL map");                                                                          \
//             return;                                                                                                         \
//         }                                                                                                                   \
//         for (int i = 0; i < map->capacity; i++) {                                                                           \
//             if (map->map[i] != NULL) {                                                                                      \
//                 delete_we_vector_##name(&map->map[i]);                                                                      \
//             }                                                                                                               \
//         }                                                                                                                   \
//         map->capacity = 0;                                                                                                  \
//         map->element_count = 0;                                                                                             \
//         free(map->map);                                                                                                     \
//         map->map = NULL;                                                                                                    \
//     }                                                                                                                       \
//                                                                                                                             \
//     we_bool we_map_##name##_is_empty(we_map_##name *map) {                                                                  \
//         if (map == NULL) {                                                                                                  \
//             return WE_TRUE;                                                                                                 \
//         }                                                                                                                   \
//         return (map->element_count == 0) ? WE_TRUE : WE_FALSE;                                                              \
//     }
//
//
// DEFINE_WE_MAP(we_bool, bool)
//
// DEFINE_WE_MAP(we_int8, int8)
//
// DEFINE_WE_MAP(we_uint8, uint8)
//
// DEFINE_WE_MAP(we_int32, int32)
//
// DEFINE_WE_MAP(we_uint32, uint32)
//
// DEFINE_WE_MAP(we_int64, int64)
//
// DEFINE_WE_MAP(we_uint64, uint64)
//
// DEFINE_WE_MAP(we_real, real)
//
// DEFINE_WE_MAP(we_rectangle, rectangle)
//
// DEFINE_WE_MAP(we_vertex, vertex)
//
// DEFINE_WE_MAP(we_entity, entity)