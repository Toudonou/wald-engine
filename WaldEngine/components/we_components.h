//
// Created by Toudonou on 16/03/2025.
//

#ifndef WE_COMPONENTS_H
#define WE_COMPONENTS_H

#include "core/we_defines.h"
#include "maths/we_maths.h"

typedef struct we_rectangle{
    we_int8 name[WE_MAX_WE_COMPONENT_NAME_LENGTH];
    we_vec2 position;
    we_real width, height;
    we_vec2 offset;
    we_color color;
} we_rectangle;

#endif //WE_COMPONENTS_H
