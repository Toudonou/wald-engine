//
// Created by Toudonou on 23/03/2025.
//

#ifndef WE_ENTITY_H
#define WE_ENTITY_H

#include "core/we_defines.h"
#include "maths/we_maths.h"

struct transform {
    we_vec2 position;
    we_vec2 scale;
    we_real rotation;
};

typedef struct we_entity {
    we_int8 name[WE_MAX_WE_ENTITY_NAME_LENGTH];
    we_real z_index;
    struct transform transform;
} we_entity;

#endif //WE_ENTITY_H
